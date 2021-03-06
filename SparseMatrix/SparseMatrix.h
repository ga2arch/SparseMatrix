//
//  SparseMatrix.h
//  SparseMatrix
//
//  Created by Gabriele Carrettoni on 17/02/15.
//  Copyright (c) 2015 Gabriele Carrettoni. All rights reserved.
//

#ifndef SparseMatrix_SparseMatrix_h
#define SparseMatrix_SparseMatrix_h

#include <iostream>
#include <cstdio>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <cstddef>
/**
 SparseMatrix
 Implementation of a SparseMatrix
 @param T the type to store in the matrix.
 */
template <typename T>
class SparseMatrix {
    
public:
    /**
     Struct to hold the elements with their respective coordinates.
     @param j the row coordinate
     @param k the coloumn cooridnate
     @param elem the element stored
     */
    struct element {
        const int j, k;
        T elem;
        
        element(int r, int c, const T e): j(r), k(c), elem(e) {}
    };
    
    class const_iterator;
    
    class iterator {
        //
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef element                   value_type;
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
        element** data;
        
        friend class SparseMatrix;
        
        explicit iterator(element** data_): data(data_) {}
    };
    
    class const_iterator {
        //
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef const element             value_type;
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
        
    private:
        element** data;
        
        friend class SparseMatrix;
        
        const_iterator(element** data_): data(data_) {}
    };
    
    /**
     Constructor of empty matrix
     */
    SparseMatrix(): rows(0), cols(0), size(0), m(NULL) {};
    
    /**
     Constructor
     @param r the number of rows
     @param c the number of coloumns
     @param d the default element to return when the user tries to retrieve an
     element not existent in the matrix.
     */
    SparseMatrix(int r, int c, T d): rows(r), cols(c), def(d), size(0), m(NULL) {}
    
    /**
     Copy constructor
     @param sm the matrix to copy from
     */
    SparseMatrix(const SparseMatrix& sm) {
        rows = sm.rows;
        cols = sm.cols;
        
        def  = sm.def;
        size = sm.size;
        
        m = new element*[size]();
        
        for (int i=0; i < size; i++) {
            m[i] = new element(sm.m[i]->j, sm.m[i]->k, sm.m[i]->elem);
        }
    }
    
    /**
     Copy constructor from Matrix with different type trying to cast the type.
     @param sm the other matrix
     */
    template <typename Q>
    SparseMatrix(const SparseMatrix<Q>& sm) {
        rows = sm.get_rows();
        cols = sm.get_cols();
        
        def  = sm.get_def();
        size = sm.get_size();
        
        m = new element*[size]();
        
        typename SparseMatrix<Q>::element* const* sm_m = sm.get_m();
        
        for (int i=0; i < size; i++) {
            m[i] = new element(sm_m[i]->j,
                               sm_m[i]->k,
                               sm_m[i]->elem);
        }
    }
    
    /**
     Copy constructor
     */
    SparseMatrix operator=(const SparseMatrix& sm) {
        rows = sm.rows;
        cols = sm.cols;
        
        def  = sm.def;
        size = sm.size;
        
        m = new element*[size]();
        
        for (int i=0; i < size; i++) {
            m[i] = new element(sm.m[i]->j, sm.m[i]->k, sm.m[i]->elem);
        }
        
        return *this;
    }
    
    /**
     Destructor
     */
    ~SparseMatrix() {
        for (int i=0; i < size; i++)
            delete m[i];
        
        delete[] m;
        m = NULL;
    }
    
    
    /**
     Return the const_iterator, pointing at the first element
     @returns the const_iterator
     */
    iterator begin() {
        return iterator(m);
    }
    
    /**
     Return the iterator, pointing at the last element
     @returns the iterator
     */
    iterator end() {
        return iterator(m+size);
    }
    
    
    /**
     Return the iterator, pointing at the first element
     @returns the const_iterator
     */
    const_iterator begin() const {
        return iterator(m);
    }
    
    /**
     Return the const_iterator, pointing at the last element
     @returns the const_iterator
     */
    const_iterator end() const {
        return iterator(m+size);
    }
    
    /**
     Add an element of type T to the matrix.
     @param j the nth-row
     @param k the nth-col
     @param elem the element to add to the matrix
     */
    void add(int j, int k, const T elem) {
        if (j >= rows || k >= cols) {
            throw std::out_of_range("Element j/k are out of range");
        }
        
        element** temp = new element*[++size]();
        
        if (m) {
            for (int i=0; i < size; i++) {
                if (i == size-1) {
                    temp[i] = new element(j, k, elem);
                    break;
                }
                
                if ((j < m[i]->j) || (j == m[i]->j && k < m[i]->k)) {
                    temp[i] = new element(j, k, elem);
                    
                    for (int x=i+1; x < size; x++) {
                        temp[x] = new element(m[i]->j, m[i]->k, m[i]->elem);
                        i++;
                    }
                    
                    break;
                }
                
                if (j == m[i]->j && k == m[i]->k) {
                    m[i]->elem = elem;
                    
                    for (int i=0; i < size; i++)
                        delete temp[i];
                    
                    delete[] temp;
                    temp = NULL;
                    
                    --size;
                    break;
                }
                
                temp[i] = new element(m[i]->j, m[i]->k, m[i]->elem);
            }
            
        }
        else
            temp[0] = new element(j, k, elem);
        
        if (temp) {
            
            for (int i=0; i < size-1; i++)
                delete m[i];
            
            delete[] m;
            
            m = temp;
        }
    }
    
    /**
     Query operator, useful to retrieve elements aded to the matrix, returns
     the default element passed at class intialization if queried for an element
     not in the matrix.
     @param j the nth-row
     @param k the nth-col
     @returns the element
     */
    T operator()(int j, int k) const {
        for (int i=0; i < size; i++) {
            if (m[i]->j == j && m[i]->k == k)
                return m[i]->elem;
        }
        
        return def;
    }
    
    /**
     Returns the default parameter passed at class instantiation
     @returns default value
     */
    const T get_def() const {
        return def;
    }
    
    /**
     Returns the number of rows.
     @returns number of rows
     */
    const int get_rows() const {
        return rows;
    }
    
    /**
     Returns the number of cols
     @returns number of cols
     */
    const int get_cols() const {
        return cols;
    }
    
    const size_t get_size() const {
        return size;
    }
    
    element* const* get_m() const {
        return m;
    }
    
private:
    /**
     Comodity function to easily display the content of a SparseMatrix.
     @param os stream to write on
     @param sm reference of the matrix to write
     @return output stream
     */
    friend std::ostream& operator<<(std::ostream &os, const SparseMatrix &sm) {
        for (int j=0; j < sm.get_rows(); j++) {
            for (int k=0; k < sm.get_cols(); k++) {
                os << sm(j, k);
                
                if (k == sm.get_cols()-1)
                    os << "\n";
                else
                    os << " ";
            }
        }
        
        return os;
    }
    
    int rows;
    int cols;
    T def;
    
    element** m;
    size_t size;
};

/**
 Takes a sparsematrix and a function p and return the number of elements that
 satisfie the function p.
 @param sm the SparseMatrix
 @param p  the predicated
 @returns the number of elements
 */
template <typename T, typename P>
int evaluate(SparseMatrix<T>& sm, P p) {
    int sum = 0;
    
    for (typename SparseMatrix<T>::const_iterator itr=sm.begin(); itr != sm.end(); itr++) {
        if (p(itr->elem)) sum++;
    }
    
    if (p(sm.get_def())) sum++;
    
    return sum;
}

#endif
