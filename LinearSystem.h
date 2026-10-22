#ifndef LINEARSYSTEM_H
#define LINEARSYSTEM_H

#include "Matrix.h"

class LinearSystem {
public:
    int variables;
    int equations;

    Matrix coefficients;         //coefficient matrix
    Matrix constants;                  //constants matrix
    //variables = n,  equations = e
    LinearSystem(int n, int e);

    void input();
    void print();

    Matrix solve_using_inverse();

    Matrix solve_using_gaus();
};

#endif
