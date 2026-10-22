#include "LinearSystem.h"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>

//variables = n,  equations = e
LinearSystem::LinearSystem(int n, int e)
    : variables(n), equations(e), coefficients(e, n), constants(e, 1) {
    if (n <= 0 || e <= 0) {
        throw std::invalid_argument("A linear system must have at least one variable and one equation.");
    }
}

void LinearSystem::input() {
    std::cout << "Enter the coefficients:\n";
    std::cin >> coefficients;
    std::cout << "Enter the constants:\n";
    std::cin >> constants;
   
}
void LinearSystem::print(){
    int count=0;
    Matrix aug(coefficients.rows, coefficients.columns + 1);
    for (int i = 0; i < aug.rows; i++) {
        for (int j = 0; j < coefficients.columns; j++) {
            aug[i][j] = coefficients[i][j];
            std::cout<<aug[i][j]<<"x["<<count<<"] + ";
            count++;
        }
        aug[i][aug.columns - 1] = constants[i][0];
        std::cout<<" = "<<aug[i][aug.columns - 1]<<'\n';
        count=0;
    }
}

Matrix LinearSystem::solve_using_inverse() {
    if (variables != equations) {
        throw std::logic_error("Must be square matrix. Use solve with Gaussian eliminations ");
    }

    return coefficients.inverse() * constants;
}

Matrix LinearSystem::solve_using_gaus() {
    //creating the augmented matrix
    Matrix aug(coefficients.rows, coefficients.columns + 1);

    for (int i = 0; i < aug.rows; i++) {
        for (int j = 0; j < coefficients.columns; j++) {
            aug[i][j] = coefficients[i][j];
        }
        aug[i][aug.columns - 1] = constants[i][0];
    }

    // Gaussian elimination
    int pivotRow = 0;
    std::vector<int> pivotColumns;

    for (int col = 0; col < variables && pivotRow < equations; col++) {
        // Partial pivoting
        int pivot = pivotRow;
        for (int j = pivotRow + 1; j < aug.rows; j++) {
            if (std::fabs(aug[j][col]) > std::fabs(aug[pivot][col])) {
                pivot = j;
            }
        }

        if (std::fabs(aug[pivot][col]) < 1e-12) {
            continue;
        }

        if (pivot != pivotRow) {
            std::swap(aug.matrix[pivotRow], aug.matrix[pivot]);
        }

        // Eliminate rows below
        for (int k = pivotRow + 1; k < aug.rows; k++) {
            double factor = aug[k][col] / aug[pivotRow][col];
            for (int j = col; j < aug.columns; j++) {
                aug[k][j] -= factor * aug[pivotRow][j];
            }
        }

        pivotColumns.push_back(col);
        pivotRow++;
    }

    // Check for inconsistent rows (all coefficients zero but constant nonzero)
    for (int i = 0; i < aug.rows; i++) {
        bool allZero = true;
        for (int j = 0; j < variables; j++) {
            if (std::fabs(aug[i][j]) >= 1e-12) {
                allZero = false;
                break;
            }
        }

        if (allZero && std::fabs(aug[i][variables]) >= 1e-12) {
            throw std::logic_error("System has no solution.");
        }
    }

    if (static_cast<int>(pivotColumns.size()) < variables) {
        throw std::logic_error("System does not have a unique solution.");
    }

    // Back substitution
    Matrix solution(variables, 1);
    for (int i = static_cast<int>(pivotColumns.size()) - 1; i >= 0; i--) {
        int col = pivotColumns[i];
        double sum = aug[i][variables];

        for (int j = col + 1; j < variables; j++) {
            sum -= aug[i][j] * solution[j][0];
        }

        solution[col][0] = sum / aug[i][col];
    }

    return solution;
}
