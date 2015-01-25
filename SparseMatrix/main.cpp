//
//  main.cpp
//  SparseMatrix
//
//  Created by Gabriele Carrettoni on 02/02/15.
//  Copyright (c) 2015 Gabriele Carrettoni. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <exception>
#include <stdexcept>


template <typename T>
class SparseMatrix {

public:
    struct Element {
        const int j, k;
        T elem;
        
        Element(int r, int c, const T e): j(r), k(c), elem(e) {}
    };
    
    class const_iterator;
    
    class iterator {
        //
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef Element                   value_type;
        typedef ptrdiff_t                 difference_type;
        typedef value_type*               pointer;
        typedef value_type*&              reference;
        
        /**
         Copy constructor
         @param other reference to the iterator to copy.
         */
        iterator(const iterator &other) {
            data = other.data;
        }
        
        /**
         Assignment
         @param other reference to the iterator to copy.
         */
        iterator& operator=(const iterator &other) {
            data = other.data;
            return *this;
        }
        
        /**
         Dereference pointer
         */
        reference operator*() const {
            return *data;
        }
        
        /**
         Return pointer
         @returns pointer to the current element.
         */
        pointer operator->() const {
            return *data;
        }
        
        /**
         Post-increment operator;
         @returns iterator not incremented;
         */
        iterator operator++(int) {
            return iterator(data++);
        }
        
        /**
         Pre-increment operator;
         @returns iterator incremented;
         */
        iterator& operator++() {
            ++data;
            return *this;
        }
        
        /**
         Equality operator, check if the two iterators point to the same element
         @param other reference to the other iterator
         */
        bool operator==(const iterator &other) const {
            return data == other.data;
        }
        
        /**
         Inequality operator, check iif the two iterators
         don't point to the same element
         @param other reference to the other iterator
         */
        bool operator!=(const iterator &other) const {
            return data != other.data;
        }
        
        friend class const_iterator;
        
        /**
         Equality operator, check if the two iterators point to the same element.
         @param other reference to the other const_iterator
          */
        bool operator==(const const_iterator &other) const {
            return data == other.data;
        }
        
        /**
         Inequality operator, check if the two iterators
         don't point to the same element.
         @param other reference to the other const_iterator
         */
        bool operator!=(const const_iterator &other) const {
            return data != other.data;
        }

        
    private:
        Element** data;
        
        friend class SparseMatrix;
        
        explicit iterator(Element** data_): data(data_) {}
    };
    
    class const_iterator {
        //
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef const Element             value_type;
        typedef ptrdiff_t                 difference_type;
        typedef value_type*               pointer;
        typedef value_type&               reference;
        
        /**
         Copy constructor
         @param other reference to the iterator to copy.
         */
        const_iterator(const iterator &other) {
            data = other.data;
        }
        
        /**
         Assignment
         @param other reference to the iterator to copy.
         */
        const_iterator& operator=(const iterator &other) {
            data = other.data;
            return *this;
        }
        
        /**
         Dereference pointer
         */
        reference operator*() const {
            return **data;
        }
        
        /**
         Return pointer
         @returns pointer to the current element.
         */
        pointer operator->() const {
            return *data;
        }
        
        /**
         Post-increment operator;
         @returns iterator not incremented;
         */
        const_iterator operator++(int) {
            return iterator(data++);
        }
        
        /**
         Pre-increment operator;
         @returns iterator incremented;
         */
        const_iterator& operator++() {
            ++data;
            return *this;
        }
        
        /**
         Equality operator, check if the two iterators point to the same element
         @param other reference to the other iterator
         */
        bool operator==(const const_iterator &other) const {
            return data == other.data;
        }
        
        /**
         Inequality operator, check iif the two iterators
         don't point to the same element
         @param other reference to the other iterator
         */
        bool operator!=(const const_iterator &other) const {
            return data != other.data;
        }
        
        friend class const_iterator;
 
    private:
        Element** data;
        
        friend class SparseMatrix;
        
        const_iterator(Element** data_): data(data_) {}
    };

    explicit SparseMatrix(int r, int c, T d): rows(r), cols(c), def(d), size(0), m(NULL) {}
    
    SparseMatrix(const SparseMatrix& sm) {
        rows = sm.rows;
        cols = sm.cols;
        
        def  = sm.def;
        size = sm.size;
        
        m = new Element*[size]();
        
        for (int i=0; i < size; i++) {
            m[i] = new Element(sm.m[i]->j, sm.m[i]->k, sm.m[i]->elem);
        }
    }
    
    template <typename Q>
    SparseMatrix(const SparseMatrix<Q>& sm) {
        rows = sm.get_rows();
        cols = sm.get_cols();
        
        def  = sm.get_def();
        size = sm.get_size();
        
        m = new Element*[size]();
        
        for (int i=0; i < size; i++) {
            m[i] = new Element(sm.get_m()[i]->j,
                               sm.get_m()[i]->k,
                               sm.get_m()[i]->elem);
        }
    }
    
    ~SparseMatrix() {
        for (int i=0; i < size; i++)
            delete m[i];
        
        delete[] m;
        m = NULL;
    }
    
    iterator begin() {
        return iterator(m);
    }
    
    iterator end() {
        return iterator(m+size);
    }
    
    const_iterator begin() const {
        return iterator(m);
    }
    
    const_iterator end() const {
        return iterator(m+size);
    }
    
    void add(int j, int k, const T elem) {
        //assert(j < rows && k < cols);
        
        Element** temp = new Element*[++size]();
        
        if (m) {
            for (int i=0; i < size; i++) {
                if (i == size-1) {
                    temp[i] = new Element(j, k, elem);
                    break;
                }
                
                if ((j < m[i]->j) || (j == m[i]->j && k < m[i]->k)) {
                    temp[i] = new Element(j, k, elem);
                    
                    for (int x=i+1; x < size; x++) {
                        temp[x] = m[i++];
                    }
                    
                    break;
                }
                
                if (j == m[i]->j && k == m[i]->k) {
                    m[i] = new Element(j, k, elem);
                    size--;
                    
                    delete[] temp;
                    temp = NULL;
                    
                    break;
                }
                
                temp[i] = m[i];
            }
            
        }
        else
            temp[0] = new Element(j, k, elem);
        
        if (temp) m = temp;
    }
    
    T operator()(int j, int k) {
        for (int i=0; i < size; i++) {
            if (m[i]->j == j && m[i]->k == k)
                return m[i]->elem;
        }
        
        return def;
    }
    
    const T get_def() const {
        return def;
    }
    
    const int get_rows() const {
        return rows;
    }
    
    const int get_cols() const {
        return cols;
    }
    
    const size_t get_size() const {
        return size;
    }
    
    Element** get_m() const  {
        return m;
    }
    
private:
    int rows;
    int cols;
    T def;
    
    Element** m;
    size_t size;
};

template <typename T, typename P>
int evaluate(SparseMatrix<T>& sm, P p) {
    int sum = 0;
    for (const typename SparseMatrix<T>::Element* e: sm) {
        if (p(e->elem)) sum++;
    }
    
    if (p(sm.get_def())) sum++;
    
    return sum;
}

bool t(int m) { return m > 1; }

int main(int argc, const char * argv[]) {
    SparseMatrix<float> m(10, 10, 0);
    m.add(0, 1, 1.2);
    m.add(9, 9, 0);
    m.add(3, 2, 9);
    m.add(3, 2, 5.3);
    
    SparseMatrix<int> m2(m);
    
    for (auto itr=m.begin(); itr != m.end(); itr++) {
        std::cout << itr->elem << std::endl;
    }
    
    std::cout << evaluate(m, t);
    
    return 0;
}
