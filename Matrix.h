#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <string>

class LinearSystem;

class Matrix {
private:
    int rows;
    int columns;
    std::vector<std::vector<double>> matrix;

    //checks if matrix a square matrix (nxn)
    bool isSquare() const;

    //checks if matrix is a square matrix
    bool isIdentity() const;

    //check if matrix is symmetric
    bool isSymmetric() const;

public:
    Matrix(int row, int col);

    //getters and setters
    int getRows() const;
    int getColumns() const;

    std::string size_matrix() const;

    //functions for inputting and outputting matrix - has been replaced with operator<< and operator>> overloading
    void inputMatrix();
    void displayMatrix() const;

    //to create an identity matrix
    void identity();

    //to create a zero matrix
    void zero_matrix();

    //cout and cin for output and input of matrices
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m1);
    friend std::istream& operator>>(std::istream& in, Matrix& m1);

    //used to access elemnts of a matrix
    std::vector<double>& operator[](int row);
    const std::vector<double>& operator[](int row) const;

    double determinant() const;

    //finding the determinant as it's own seperate function + AND DISPLAYS STEPS
    double detN() const;

    //computing the inverse matrix + DISPLAYING STEPS
    Matrix inverse() const;

    //to find the trace (sum of all entries along main diagonal
    double tr() const;

    //returns the transpose matrix
    Matrix transpose() const;

    //returns rank of matrix by converting it into row echelon form and counts the non-zero rows
    int Rank() const;

    //checks if two matrices are equal
    friend bool operator==(const Matrix& m1, const Matrix& m2);

    //checks if two matrices commute (product of two matrices is independent of the order in which they are multiplied)
    bool commute(const Matrix& m1, const Matrix& m2) const;

    //matrix addition, better to keep as non member friend func for symmetry
    friend Matrix operator+(const Matrix& o1, const Matrix& o2);

    //matrix subtraction
    friend Matrix operator-(const Matrix& m1, const Matrix& m2);

    //matrix multipliction of two matrices only
    friend Matrix operator*(const Matrix& m1, const Matrix& m2);

    //scalar multiplicatin- matrix*double
    friend Matrix operator*(const Matrix& m1, const double scalar);

    //scalar multiplicatin- double*matrix
    friend Matrix operator*(const double scalar, const Matrix& m1);

    friend class LinearSystem;
};

#endif
