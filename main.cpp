#include <iostream>
#include <vector>
using namespace std;

class Matrix{
    public:
    int rows; int columns;
    vector<vector<double>> matrix; 
    Matrix(){
        cout << "Enter number of rows: ";
        cin >> rows;

        cout << "Enter number of columns: ";
        cin >> columns;

        matrix.resize(rows, vector<double>(columns));
    }
    void inputMatrix(){
        for (int i =0 ; i< rows; i++) {
            for (int j=0; j<columns; j++){
                cout<<"Enter a["<<i+1<<"]["<<j+1<<"]. "<<endl;
                cin>>matrix[i][j];
            }
        }
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

};

int main() {
    Matrix m1;
    m1.inputMatrix();
    m1.displayMatrix();
    cout<<m1.determinant();
    return 0;
}
