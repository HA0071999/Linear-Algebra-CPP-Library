I loved my Linear Algebra course, so I made this small project.



How to use:

operator<< (ostream): Used for displaying the matrix via cout.

operator>> (istream): Used for inputting matrix entries via cin.

operator[]: Allows direct access to rows (e.g., m1[0][0] accesses the top-left element).

operator+: Performs matrix addition.

operator-: Performs matrix subtraction.

operator*: Performs matrix-matrix multiplication and scalar-matrix multiplication.

operator==: Checks if two matrices are identical.



Matrix(int row, int col): Initializes a matrix of size row x col with all zeros.

size_matrix(): string, Returns a string representation of the matrix dimensions (e.g., "2x2").

identity(): void, Transforms the current matrix into an identity matrix.

fill(double d); Matrix, fills every entry in the matrix with the double d.

isSquare(): bool, Returns true if the number of rows equals the number of columns.

isIdentity(): bool, Returns true if the matrix is an identity matrix, otherwise returns false.

isSymmetric(): bool, Returns true if the matrix is symmetric (matrix and it's transpose are equal matrices)/

swap_rows(int rows 1, int row 2): void, Swaps row 1 and row 2.

gaussian_elimination(): void, performs gaussian elimination on a matrix. Reduces it to REF.

rref(): void, Converts matrix to reduced row echelon form.

determinant(): double, Calculates and returns the determinant of a square matrix.

detN(): double, Calculates the determinant and prints step-by-step Gaussian elimination stages to the console.

inverse(): Matrix, Computes the inverse of the matrix; throws a logic_error if singular or non-square.

commute(m1, m2): bool, Returns true if the provided matrices satisfy the commutative property ($A \times B = B \times A$).

tr(): double, Returns the trace of the matrix, throws logic_error if not square.

transpose(): Matrix, Returns the transpose matrix

Rank(): int, Returns rank of a matrix, (number of linearly independent rows and columns). 


LinearSystem(n, e): Sets up a system with n variables and e equations.

input(): void, Prompts the user to populate the Coefficient and Constant matrices.

print(): void, Prints the linear system.

solve_using_inverse(): Matrix, Solves the system using $x = A^{-1}B$; requires a square coefficient matrix. Will throw error if matrix if coefficient matrix is not square.

solve_using_gaus(): Matrix, Solves the sytem using gaussian elimination.


