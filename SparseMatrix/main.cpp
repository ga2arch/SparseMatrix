//
//  main.cpp
//  SparseMatrix
//
//  Created by Gabriele Carrettoni on 02/02/15.
//  Copyright (c) 2015 Gabriele Carrettoni. All rights reserved.
//

#include "SparseMatrix.h"

void test_add_primitive() {
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

void test_overwrite_primitive() {
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

void test_get_primitive() {
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

bool p_primitive(float x) {
    return x > 1;
}

void test_evaluate_primitive() {
    std::cout << "EVALUATE PRIMITIVE: ";
    
    SparseMatrix<float> m(10, 10, 0);
    m.add(0, 1, 1.2);
    m.add(9, 9, 0);
    m.add(3, 2, 5.3);
    m.add(9, 9, 1.3);
    
    int sum = evaluate(m, p_primitive);
    
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
    std::cout << "EVALUATE COMPLEX: ";
    
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

void test_pretty_print_primitive() {
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

void test_pretty_print_complex() {
    SparseMatrix<std::string> m(3, 3, "-");
    m.add(0, 0, "+");
    m.add(0, 1, "*");
    m.add(0, 2, "ù");
    
    m.add(1, 0, "=");
    m.add(1, 2, "^");
    
    m.add(2, 0, "?");
    m.add(2, 1, "'");
    m.add(2, 2, ";");
    
    std::cout << m << std::endl;;
}

void test_conversion_primite_to_primitve() {
    std::cout << "INT -> FLOAT: ";
    
    SparseMatrix<float> m(1, 2, 1.3);
    m.add(0, 0, 3.2);
    m.add(0, 1, 2.4);

    SparseMatrix<int> m1(m);

    assert(m1(0, 0) == (int)3);
    assert(m1(0, 1) == (int)2);
    
    std::cout << "PASSED" << std::endl;
}

void test_conversion_primite_to_complex() {
    std::cout << "CHAR -> STRING: ";
    
    SparseMatrix<char*> m(1, 2, "ciao");
    m.add(0, 0, "hello");
    m.add(0, 1, "come");
    
    SparseMatrix<std::string> m1(m);
    
    assert(m1(0, 0) == std::string("hello"));
    assert(m1(0, 1) == std::string("come"));
    
    std::cout << "PASSED" << std::endl;
}

int main(int argc, const char * argv[]) {
    std::cout << "=== TESTING PRIMITE TYPE: ===\n";
    test_add_primitive();
    test_overwrite_primitive();
    test_get_primitive();
    
    std::cout << "\n=== TESTING COMPLEX TYPE: ===\n";
    test_add_complex();
    test_overwrite_complex();
    test_get_complex();
    
    std::cout << "\n=== TESTING EVALUATE: ===\n";
    test_evaluate_primitive();
    test_evaluate_complex();

    std::cout << "\n=== TESTING CONVERSION: ===\n";
    test_conversion_primite_to_primitve();
    test_conversion_primite_to_complex();
    
    std::cout << "\n=== TESTING PRETTY PRINTING: ===\n";
    test_pretty_print_primitive();
    test_pretty_print_complex();
    
    return 0;
}
