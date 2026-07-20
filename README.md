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

zero_maatrix(); void, Transforms the current matrix into a zero matrix.

check_if_squareMatrix(): bool, Returns true if the number of rows equals the number of columns.

determinant(): double, Calculates and returns the determinant of a square matrix.

detN(): double, Calculates the determinant and prints step-by-step Gaussian elimination stages to the console.

inverse(): Matrix, Computes the inverse of the matrix; throws a logic_error if singular or non-square.

commute(m1, m2), bool, Returns true if the provided matrices satisfy the commutative property ($A \times B = B \times A$).



LinearSystem(n, e): Sets up a system with n variables and e equations.

input(): void, Prompts the user to populate the Coefficient and Constant matrices.

solve_using_inverse(): Matrix, Solves the system using $x = A^{-1}B$; requires a square coefficient matrix.


