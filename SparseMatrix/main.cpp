//
//  main.cpp
//  SparseMatrix
//
//  Created by Gabriele Carrettoni on 02/02/15.
//  Copyright (c) 2015 Gabriele Carrettoni. All rights reserved.
//


#include "SparseMatrix.h"

void test_add_simple() {
    std::cout << "ADD: ";
    
    SparseMatrix<float> m(10, 10, 0);
    m.add(0, 1, 1.2);
    m.add(9, 9, 0);
    m.add(3, 2, 5.3);
    
    float t[4] = { 1.2, 5.3, 0 };
    
    int i = 0;
    for (SparseMatrix<float>::const_iterator itr=m.begin(); itr != m.end(); itr++) {
        assert(itr->elem == t[i++]);
    }
    
    std::cout << "PASSED" << std::endl;
}

void test_overwrite_simple() {
    std::cout << "OVERWRITE: ";
    
    SparseMatrix<float> m(10, 10, 0);
    m.add(0, 1, 1.2);
    m.add(9, 9, 0);
    m.add(3, 2, 5.3);
    m.add(9, 9, 1.3);

    float t[4] = { 1.2, 5.3, 1.3 };
    
    int i = 0;
    for (SparseMatrix<float>::const_iterator itr=m.begin(); itr != m.end(); itr++) {
        assert(itr->elem == t[i++]);
    }
    
    std::cout << "PASSED" << std::endl;
}

void test_get_simple() {
    std::cout << "GET: ";
    
    SparseMatrix<float> m(10, 10, 0);
    m.add(0, 1, 1.2);
    m.add(9, 9, 0);
    m.add(3, 2, 5.3);
    m.add(9, 9, 1.3);
    
    assert(m(9, 9) == (float)1.3);
    assert(m(3, 5) == (float)m.get_def());

    std::cout << "PASSED" << std::endl;
}

bool p(float x) {
    return x > 1;
}

void test_evaluate_simple() {
    std::cout << "EVALUATE: ";
    
    SparseMatrix<float> m(10, 10, 0);
    m.add(0, 1, 1.2);
    m.add(9, 9, 0);
    m.add(3, 2, 5.3);
    m.add(9, 9, 1.3);
    
    int sum = evaluate(m, p);
    
    assert(sum == 3);
    
    std::cout << "PASSED" << std::endl;
}

void test_add_complex() {
    std::cout << "ADD: ";
    
    SparseMatrix<std::string> m(10, 10, "");
    m.add(0, 1, "ciao");
    m.add(9, 9, "come");
    m.add(3, 2, "va");
    
    std::string t[4] = { "ciao", "va", "come" };
    
    int i = 0;
    for (SparseMatrix<std::string>::const_iterator itr=m.begin(); itr != m.end(); itr++) {
        assert(itr->elem == t[i++]);
    }
    
    std::cout << "PASSED" << std::endl;
}

void test_overwrite_complex() {
    std::cout << "OVERWRITE: ";
    
    SparseMatrix<std::string> m(10, 10, "");
    m.add(0, 1, "ciao");
    m.add(9, 9, "come");
    m.add(3, 2, "va");
    m.add(9, 9, "test");

    std::string t[4] = { "ciao", "va", "test" };
    
    int i = 0;
    for (SparseMatrix<std::string>::const_iterator itr=m.begin(); itr != m.end(); itr++) {
        assert(itr->elem == t[i++]);
    }
    
    std::cout << "PASSED" << std::endl;
}

void test_get_complex() {
    std::cout << "GET: ";
    
    SparseMatrix<std::string> m(10, 10, "");
    m.add(0, 1, "ciao");
    m.add(9, 9, "come");
    m.add(3, 2, "va");
    m.add(9, 9, "test");
    m.add(3, 5, "");
    
    assert(m(9, 9) == "test");
    assert(m(3, 5) == m.get_def());
    
    std::cout << "PASSED" << std::endl;
}

bool p_complex(const std::string& x) {
    return x == "ciao";
}

void test_evaluate_complex() {
    std::cout << "EVALUATE: ";
    
    SparseMatrix<std::string> m(10, 10, "");
    m.add(0, 1, "ciao");
    m.add(9, 9, "come");
    m.add(3, 2, "va");
    m.add(9, 9, "test");
    m.add(3, 5, "");
    
    int sum = evaluate(m, p_complex);
    
    assert(sum == 1);
    
    std::cout << "PASSED" << std::endl;
}

void test_pretty_print() {
    SparseMatrix<int> m(3, 3, 0);
    m.add(0, 0, 3);
    m.add(0, 1, 2);
    m.add(0, 2, 5);
    
    m.add(1, 0, 6);
    m.add(1, 2, 10);
    
    m.add(2, 0, 32);
    m.add(2, 1, 47);
    m.add(2, 2, 50);
    
    std::cout << m << std::endl;;
}

int main(int argc, const char * argv[]) {
    std::cout << "=== TESTING PRIMITE TYPE: ===\n";
    test_add_simple();
    test_overwrite_simple();
    test_get_simple();
    test_evaluate_simple();
    
    std::cout << "\n=== TESTING COMPLEX TYPE: ===\n";
    test_add_complex();
    test_overwrite_complex();
    test_get_complex();
    test_evaluate_complex();
    
    std::cout << "\n=== TESTING PRETTY PRINTING: ===\n";
    test_pretty_print();
    
    return 0;
}
