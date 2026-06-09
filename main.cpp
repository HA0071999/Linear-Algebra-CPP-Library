#include <iostream>
#include <vector>
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

    void inputMatrix(){
        for (int i =0 ; i< rows; i++) {
            for (int j=0; j<columns; j++){
                cout<<"Enter a["<<i+1<<"]["<<j+1<<"]. "<<endl;
                cin>>matrix[i][j];
            }
        }
        displayMatrix();
    }
    void displayMatrix(){
        //simply showing how the matrix looks
        for (int i =0 ; i<rows; i++) {
            for (int j=0; j<columns; j++){
                
                cout<<matrix[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    
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
        
    }
    //matrix addition
    Matrix operator+(const Matrix& other){
        Matrix result(rows,columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                result.matrix[i][j] =
                    matrix[i][j] +
                    other.matrix[i][j];
            }
        }
        return result;
        //PROBLEM! WILL RETURN 0 IF NOT SQR MATRIX--> needs exception handelling
    }
};

int main() {
    Matrix m1(3,3);
    m1.inputMatrix();
   
    cout<<m1.determinant();
    Matrix m2(3,3), m3(3,3);
    m2.inputMatrix();
    
    m3 = m1+m2;
    m3.displayMatrix();
    
    return 0;
}
