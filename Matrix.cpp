#include "Matrix.h"

#include <cmath>
#include <iomanip>
#include <stdexcept>


//constructor
Matrix::Matrix(int row, int col) {
    if (row < 0 || col < 0) {
        throw std::invalid_argument("Matrix dimensions cannot be negative.");
    }

    rows = row;
    columns = col;
    matrix.resize(rows, std::vector<double>(columns, 0.0));
}

//getters and setters
int Matrix::getRows() const {
    return rows;
}

int Matrix::getColumns() const {
    return columns;
}

//checks if matrix a square matrix (nxn)
bool Matrix::isSquare() const {
    return rows == columns;
}

//checks if matrix is a square matrix
bool Matrix::isIdentity() const {
    if (!isSquare()) {
        return false;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (i == j && matrix[i][j] != 1) {
                return false;
            }
            if (i != j && matrix[i][j] != 0) {
                return false;
            }
        }
    }

    return true;
}

//check if matrix is symmetric
bool Matrix::isSymmetric() const {
    if (!isSquare()) {
        return false;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = i + 1; j < columns; j++) {
            if (matrix[i][j] != matrix[j][i]) {
                return false;
            }
        }
    }

    return true;
}

std::string Matrix::size_matrix() const {
    return std::to_string(rows) + "x" + std::to_string(columns);
}

//functions for inputting and outputting matrix - has been replaced with operator<< and operator>> overloading
void Matrix::inputMatrix() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << "Enter a[" << i + 1 << "][" << j + 1 << "]. " << std::endl;
            std::cin >> matrix[i][j];
        }
    }
}

void Matrix::displayMatrix() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

//to create an identity matrix
void Matrix::identity() {
    if (!isSquare()) {
        throw std::logic_error("Identity matrix must be square.");
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
}

//to create a zero matrix
void Matrix::zero_matrix() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = 0.0;
        }
    }
}

//cout and cin for output and input of matrices
std::ostream& operator<<(std::ostream& os, const Matrix& m1) {
    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m1.columns; j++) {
            os << std::setw(5) << m1.matrix[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}

std::istream& operator>>(std::istream& in, Matrix& m1) {
    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m1.columns; j++) {
            std::cout << "Enter a[" << i + 1 << "][" << j + 1 << "]. " << std::endl;
            in >> m1.matrix[i][j];
        }
        std::cout << "\n";
    }
    return in;
}

//used to access elemnts of a matrix
std::vector<double>& Matrix::operator[](int row) {
    return matrix.at(row);
}

const std::vector<double>& Matrix::operator[](int row) const {
    return matrix.at(row);
}

//returns true if two matrices are equal. Otherwise returns false
bool operator==(const Matrix& m1, const Matrix& m2) {
    if (m1.rows != m2.rows || m1.columns != m2.columns) {
        return false;
    }

    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m1.columns; j++) {
            if (m1.matrix[i][j] != m2.matrix[i][j]) {
                return false;
            }
        }
    }
    return true;
}

//checks if two matrices commute (product of two matrices is independent of the order in which they are multiplied)
bool Matrix::commute(const Matrix& m1, const Matrix& m2) const {
    return (m1 * m2) == (m2 * m1);
}

//matrix addition
Matrix operator+(const Matrix& o1, const Matrix& o2) {
    if (o1.rows != o2.rows || o1.columns != o2.columns) {
        throw std::invalid_argument("Matrix addition requires matrices with the same dimensions.");
    }

    Matrix result(o1.rows, o1.columns); //will have same size as o1
    for (int i = 0; i < o1.rows; i++) {
        for (int j = 0; j < o1.columns; j++) {
            result.matrix[i][j] = o2.matrix[i][j] + o1.matrix[i][j];
        }
    }
    return result;
}

//matrix subraction
Matrix operator-(const Matrix& m1, const Matrix& m2) {
    if (m1.rows != m2.rows || m1.columns != m2.columns) {
        throw std::invalid_argument("Matrix subtraction requires matrices with the same dimensions.");
    }

    Matrix result(m1.rows, m1.columns); //will have same size as m1
    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m1.columns; j++) {
            result.matrix[i][j] = m1.matrix[i][j] - m2.matrix[i][j];
        }
    }
    return result;
}

//matrix multiplication
Matrix operator*(const Matrix& m1, const Matrix& m2) {
    if (m1.columns != m2.rows) {
        throw std::invalid_argument("Matrix multiplication requires columns of the first matrix to equal rows of the second.");
    }

    Matrix result(m1.rows, m2.columns);
    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m2.columns; j++) {
            result.matrix[i][j] = 0.0;

            for (int k = 0; k < m1.columns; k++) {
                result.matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
            }
        }
    }
    return result;
}

//scalar multiplication
Matrix operator*(const Matrix& m1, const double scalar) {
    Matrix result(m1.rows, m1.columns);

    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m1.columns; j++) {
            result.matrix[i][j] = m1.matrix[i][j] * scalar;
        }
    }

    return result;
}

Matrix operator*(const double scalar, const Matrix& m1) {
    return m1 * scalar;
}

double Matrix::determinant() const {
    //cannot find determinant if not square matrix
    if (!isSquare()) {
        throw std::logic_error("Cannot compute detrminant of a non-square matrix. ");
    }

    if (rows == 0) {
        return 1.0;
    }
    if (rows == 1) {
        //if (1x1) matrix, det is just the entry itself
        return matrix[0][0];
    }
    if (rows == 2) {
        //if (2x2) matrix, ad - bc
        return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
    }

    //Pivitosiation
    Matrix temp = *this;
    int sign = 1;

    for (int i = 0; i < rows; i++) {
        int pivot = i;
        for (int j = i + 1; j < rows; j++) {
            if (std::fabs(temp.matrix[j][i]) > std::fabs(temp.matrix[pivot][i])) {
                pivot = j;
            }
        }

        if (std::fabs(temp.matrix[pivot][i]) < 1e-12) {
            return 0.0;
        }

        if (pivot != i) {
            std::swap(temp.matrix[i], temp.matrix[pivot]);
            sign *= -1;
        }

        for (int k = i + 1; k < rows; k++) {
            double t = temp.matrix[k][i] / temp.matrix[i][i];
            for (int j = i; j < columns; j++) {
                temp.matrix[k][j] -= t * temp.matrix[i][j];
            }
        }
    }

    //find the determinant
    double det = sign;
    for (int i = 0; i < rows; i++) {
        det *= temp.matrix[i][i];
    }
    return det;
}

//finding the determinant as it's own seperate function + AND DISPLAYS STEPS
double Matrix::detN() const {
    if (isSquare() == false) {
        throw std::logic_error("Determinant only exists when matrix is a square matrix. ");
    }

    Matrix m1 = *this;
    //Pivitosiation  //if any elements in the row beloware greater than the row above, swap
    int sign = 1;
    for (int i = 0; i < m1.rows; i++) {
        int pivot = i;
        for (int j = i + 1; j < m1.rows; j++) {
            if (std::fabs(m1.matrix[j][i]) > std::fabs(m1.matrix[pivot][i])) {
                pivot = j;
            }
        }

        if (std::fabs(m1.matrix[pivot][i]) < 1e-12) {
            std::cout << "det=0";
            return 0.0;
        }

        if (pivot != i) {
            std::swap(m1.matrix[i], m1.matrix[pivot]);
            sign *= -1;
            std::cout << "Swapped R" << i + 1 << " and R" << pivot + 1 << std::endl << m1 << std::endl;
        }
    }

    /* Gaussian Eiminataion
    i: pivot row
    k: rows below the pivot
    j: columns in the row being updated*/
    //make the elements below the pivot elements equal 0 or eliminate the variables
    for (int i = 0; i < m1.rows; i++) {
        for (int k = i + 1; k < m1.rows; k++) {
            if (std::fabs(m1.matrix[i][i]) < 1e-12) {
                std::cout << "det=0";
                return 0.0;
            }

            double t = m1.matrix[k][i] / m1.matrix[i][i];
            for (int j = i; j < m1.columns; j++) {
                m1.matrix[k][j] = m1.matrix[k][j] - t * m1.matrix[i][j];
            }
            std::cout << "R" << k + 1 << " = R" << k + 1 << " - " << t << "*R" << i + 1 << std::endl << m1 << std::endl;
        }
    }

    //find the determinant
    double det = sign;
    for (int i = 0; i < m1.rows; i++) {
        det *= m1.matrix[i][i];
    }
    std::cout << "det=" << det;
    return det;
}

//computing the inverse matrix + DISPLAYING STEPS
Matrix Matrix::inverse() const {
    if (isSquare() == false) {
        throw std::logic_error("Inverse only exists when matrix is a square matrix. ");
    }

    Matrix m1 = *this;
    Matrix I(m1.rows, m1.columns);
    I.identity();

    //partial pivotisation
    for (int i = 0; i < m1.rows; i++) {
        int pivot = i;
        for (int j = i + 1; j < m1.rows; j++) {
            if (std::fabs(m1.matrix[j][i]) > std::fabs(m1.matrix[pivot][i])) {
                pivot = j;
            }
        }

        if (std::fabs(m1.matrix[pivot][i]) < 1e-12) {
            throw std::logic_error("Determinant of matrix is 0. No inverse exists. ");
        }

        if (pivot != i) {
            std::swap(m1.matrix[i], m1.matrix[pivot]);
            std::swap(I.matrix[i], I.matrix[pivot]);
        }

        //normalize pivot row
        double pivotValue = m1.matrix[i][i];

        for (int j = 0; j < m1.columns; j++) {
            m1.matrix[i][j] /= pivotValue;
            I.matrix[i][j] /= pivotValue;
        }

        //eliminate every other row
        for (int k = 0; k < m1.rows; k++) {
            if (k == i) {
                continue;
            }

            double t = m1.matrix[k][i];
            for (int j = 0; j < m1.columns; j++) {
                m1.matrix[k][j] -= t * m1.matrix[i][j];
                I.matrix[k][j] -= t * I.matrix[i][j];
            }
            std::cout << "R" << k + 1 << " = R" << k + 1 << " - " << t << "*R" << i + 1 << std::endl << m1 << " " << I << std::endl;
        }
    }

    std::cout << I << std::endl;
    return I;
}

//to find the trace (sum of all entries along main diagonal
double Matrix::tr() const {
    if (isSquare() == false) {
        throw std::logic_error("Trace only exists when matrix is a square matrix. ");
    }

    double trace = 0;
    for (int i = 0; i < rows; i++) {
        trace += matrix[i][i];
    }
    return trace;
}

//returns the transpose matrix
Matrix Matrix::transpose() const {
    Matrix result(columns, rows);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result.matrix[j][i] = matrix[i][j];
        }
    }

    return result;
}

//returns rank of matrix by converting it into row echelon form and counts the non-zero rows
int Matrix::Rank() const {
    Matrix temp = *this;
    int pivotRow = 0;

    for (int col = 0; col < temp.columns && pivotRow < temp.rows; col++) {
        int pivot = pivotRow;
        for (int j = pivotRow + 1; j < temp.rows; j++) {
            if (std::fabs(temp.matrix[j][col]) > std::fabs(temp.matrix[pivot][col])) {
                pivot = j;
            }
        }

        if (std::fabs(temp.matrix[pivot][col]) < 1e-12) {
            continue;
        }

        if (pivot != pivotRow) {
            std::swap(temp.matrix[pivotRow], temp.matrix[pivot]);
        }

        for (int k = pivotRow + 1; k < temp.rows; k++) {
            double t = temp.matrix[k][col] / temp.matrix[pivotRow][col];
            for (int j = col; j < temp.columns; j++) {
                temp.matrix[k][j] -= t * temp.matrix[pivotRow][j];
            }
        }

        pivotRow++;
    }

    // Count non-zero rows
    int rank = 0;
    for (int i = 0; i < temp.rows; i++) {
        for (int j = 0; j < temp.columns; j++) {
            if (std::fabs(temp.matrix[i][j]) > 1e-12) {
                rank++;
                break;
            }
        }
    }

    return rank;
}
