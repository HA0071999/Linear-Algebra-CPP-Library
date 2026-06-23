#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>
using namespace std;

class Matrix{
    public:
    int rows; int columns;
    vector<vector<double>> matrix; 

     Matrix(int row, int col){
        rows=row;
        columns=col;
        cout<<rows<<"x"<<columns<<" matrix"<<endl;
        matrix.resize(rows, vector<double>(columns));
    }
    //functions for inputting and outputting matrix - has been replaced with operator<< and operator>> overloading
    void inputMatrix(){
        for (int i =0 ; i< rows; i++) {
            for (int j=0; j<columns; j++){
                cout<<"Enter a["<<i+1<<"]["<<j+1<<"]. "<<endl;
                cin>>matrix[i][j];
            }
        }
    }
    void displayMatrix(){
        for (int i =0 ; i<rows; i++) {
            for (int j=0; j<columns; j++){
                cout<<matrix[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    //cout and cin for output and input of matrices 
    friend ostream& operator<<(ostream& os, const Matrix& m1);
    friend istream& operator>>(istream& is, Matrix& m1);

    bool check_if_squareMatrix(){
        //checking if its a square matrix (nxn)
        if (rows==columns){
            return true;
        }
        else { return false; }
    }
    double determinant(){
        //cannot find determinant if not square matrix
        if (check_if_squareMatrix()==true){
            cout<<"det= ";
            switch (rows){
                case 1:
                //if (1x1) matrix, det is just the entry itself
                return matrix[rows][columns]; break;
                case 2:
                //if (2x2) matrix, ad - bc
                return matrix[0][0]*matrix[1][1] - matrix[1][0]*matrix[0][1];
            }
    
        }
        return 0;
        //PROBLEM! WILL RETURN 0 IF NOT SQR MATRIX--> needs exception handelling
    }

    //checks if two matrices are equal
    friend bool operator==(const Matrix& m1, const Matrix& m2);

    //checks if two matrices commute (product of two matrices is independent of the order in which they are multiplied)
    bool commute(const Matrix& m1, const Matrix& m2){
        if (m1*m2==m2*m1){
            return true;
        }
        else {return false; }
    }

    //matrix addition, better to keep as non member friend func for symmetry
    friend Matrix  operator+(const Matrix& o1, const Matrix& o2);
    
    //matrix multipliction of two matrices only
    friend Matrix operator*(const Matrix& m1, const Matrix& m2);

    //scalar multiplicatin- matrix*double
    friend Matrix operator*(Matrix& m1, const double scalar);
    //scalar multiplicatin- double*matrix
    friend Matrix operator*(const double scalar, Matrix& m1);

};

//returns true if two matrices are equal. Otherwise returns false
bool operator==(const Matrix& m1, const Matrix& m2){
    for (int i =0 ; i<m1.rows; i++) {
            for (int j=0; j<m1.columns; j++){
                if (m1.matrix[i][j]!=m2.matrix[i][j]){
                    return false;
                }
            }
        }
    return true;
}

//displaying the matrix using operator<< overloading
ostream& operator<<(ostream& os, const Matrix& m1){
    
    for (int i =0 ; i<m1.rows; i++) {
            for (int j=0; j<m1.columns; j++){
                
                 os <<setw(5) << m1.matrix[i][j] << " ";
            }
            os<<"\n";
        }
    return os;
}
//inputting the matrix using operator>> overloading
istream& operator>>(istream& in, Matrix& m1){
    for (int i =0 ; i< m1.rows; i++) {
            for (int j=0; j<m1.columns; j++){
                cout<<"Enter a["<<i+1<<"]["<<j+1<<"]. "<<endl;
                in>>m1.matrix[i][j];
            }
        cout<<"\n";
        }
    return in;
}

//matrix addition
Matrix operator+(const Matrix& o1, const Matrix& o2){
        Matrix result(o1.rows, o1.columns); //will have same size as o1
        for (int i = 0; i < o1.rows; i++) {
            for (int j = 0; j < o1.columns; j++) {
                result.matrix[i][j] =
                    o2.matrix[i][j] +
                    o1.matrix[i][j];
            }
        }
        return result;
        
    }

//matrix multiplication
Matrix operator*(const Matrix& m1, const Matrix& m2){
    Matrix result(m1.rows, m2.columns); 
        for (int i = 0; i < m1.rows; i++) {
            for (int j = 0; j < m2.columns; j++) {
                result.matrix[i][j] = 0;

                for (int k = 0; k < m1.columns; k++) {
                    result.matrix[i][j] +=
                        m1.matrix[i][k] *
                        m2.matrix[k][j];
                }
            }
        }
        return result;
}

//scalar multiplication
Matrix operator*(Matrix& m1, const double scalar){
    for (int i =0; i<m1.rows; i++){
        for (int j=0; j< m1.columns; j++){
            m1.matrix[i][j]*=scalar;
        }
    }
    return m1;
}
Matrix operator*(const double scalar, Matrix& m1){
    for (int i =0; i<m1.rows; i++){
        for (int j=0; j< m1.columns; j++){
            m1.matrix[i][j]*=scalar;
        }
    }
    return m1;
}
int main() {
   
    
    return 0;
}
