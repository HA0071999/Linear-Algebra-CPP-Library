#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <cmath>
using namespace std;

class Matrix{
    public:
    int rows; int columns;
    vector<vector<double>> matrix; 

     Matrix(int row, int col){
        rows=row;
        columns=col;
        matrix.resize(rows, vector<double>(columns));
    }

    string size_matrix(){
        string msize = to_string(rows) + "x" + to_string(columns);
        return msize;
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

    //to create an identity matrix
    void identity(){
        for (int i = 0; i < rows; i++)
            matrix[i][i] = 1;
    }

    //cout and cin for output and input of matrices 
    friend ostream& operator<<(ostream& os, const Matrix& m1);
    friend istream& operator>>(istream& is, Matrix& m1);

    //used to access elemnts of a matrix
    vector<double>& operator[](int row) {
        return matrix[row];
    }
    const vector<double>& operator[](int row) const {
        return matrix[row];
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
        if (check_if_squareMatrix()!=true){ throw logic_error("Cannot compute detrminant of a non-square matrix. "); }
            switch (rows){
                case 1:
                //if (1x1) matrix, det is just the entry itself
                return matrix[rows][columns]; break;
                case 2:
                //if (2x2) matrix, ad - bc
                return matrix[0][0]*matrix[1][1] - matrix[1][0]*matrix[0][1]; break;

                default: 
                        //Pivitosiation
                int sign=1;
                for(int i=0; i<rows; i++){
                    int pivot=i;
                    for(int j=i+1; j<rows; j++){
                        if ( fabs(matrix[j][i])>fabs(matrix[pivot][i]) ){

                            pivot=j; 

                            if(pivot != i){sign *= -1;}
                            for(int k=0; k<rows; k++){
                                double temp = matrix[i][k];
                                matrix[i][k]= matrix[j][k];
                                matrix[j][k]=temp;
                            }

                        }
                    }

                }
                
                for (int i=0; i<rows; i++){
                    for (int k=i+1; k<rows; k++){
                        if (matrix[i][i]<1e-12){return 0;}
                        double t= matrix[k][i]/matrix[i][i];
                        for (int j=i; j<columns; j++){
                            matrix[k][j]=matrix[k][j]-t*matrix[i][j];
                        } 
                    }
                }
                
                
                //find the determinant
                double det=sign;
                for(int i=0;i<rows; i++)
                        det *= matrix[i][i];
                        return det;
                    }
    
        
        
    }
 
    //finding the determinant as it's own seperate function + AND DISPLAYS STEPS
    double detN(){
        Matrix m1 = *this;
        //Pivitosiation  //if any elements in the row beloware greater than the row above, swap
        int sign=1;
        for(int i=0; i<m1.rows; i++){
            int pivot=i;
            for(int j=i+1; j<m1.rows; j++){
                if ( fabs(m1.matrix[j][i])>fabs(m1.matrix[pivot][i]) ){
                    pivot=j; 
        
                    if(pivot != i){sign *= -1;}
                    for(int k=0; k<m1.rows; k++){
                        
                        double temp = m1.matrix[i][k];
                        m1.matrix[i][k]= m1.matrix[j][k];
                        m1.matrix[j][k]=temp;
                        
                    }
                    cout<<"Swapped R"<<i+1<<" and R"<<j+1<<endl<<m1<<endl;
                }
            }
        }
    
        /* Gaussian Eiminataion
        i: pivot row
        k: rows below the pivot
        j: columns in the row being updated*/
        //make the elements below the pivot elements equal 0 or eliminate the variables
        
        for (int i=0; i<m1.rows; i++){
            for (int k=i+1; k<m1.rows; k++){
                if (m1.matrix[i][i]<1e-12){return 0;}
                double t= m1.matrix[k][i]/m1.matrix[i][i];
                for (int j=i; j<m1.columns; j++){
                    m1.matrix[k][j]=m1.matrix[k][j]-t*m1.matrix[i][j];
                    cout<<"R"<<k+1<<" = R"<<k+1<<" - "<<t<<"*R"<<i+1<<endl<<m1<<endl;
                } 
            }
        }
        
        //find the determinant
        double det=sign;
        for(int i=0;i<m1.rows; i++)
            det *= m1.matrix[i][i];
        cout<<"det="<<det;
        return det;
    }

    //computing the inverse matrix + DISPLAYING STEPS
    Matrix inverse(){
        if (check_if_squareMatrix()==false) {
            throw logic_error("Inverse only exists when matrix is a square matrix. ");
        }
        Matrix m1 = *this;
        Matrix I(m1.rows, m1.columns); I.identity();

        //partial pivotisation
        for (int i=0; i< m1.rows; i++){
            int pivot=i;
            for (int j = i + 1; j < rows; j++) {
                if (fabs(m1.matrix[j][i]) > fabs(m1.matrix[pivot][i]))
                    pivot = j;
            }

            if (fabs(m1.matrix[pivot][i]) < 1e-12) {
                throw logic_error("Determinant of matrix is 0. No inverse exists. "); }

            if (pivot != i) {
                swap(m1.matrix[i], m1.matrix[pivot]);
                swap(I.matrix[i], I.matrix[pivot]);
                
            }
            //normalize pivot row
            double pivotValue = m1.matrix[i][i];

            for (int j = 0; j < m1.columns; j++) {
                m1.matrix[i][j] /= pivotValue;
                I.matrix[i][j] /= pivotValue;
            }

            //eliminate every other row
            for (int k = 0; k < rows; k++) {

                if (k == i) {continue;}
                double t = m1.matrix[k][i];
                for (int j = 0; j < columns; j++) {
                    m1.matrix[k][j] -= t * m1.matrix[i][j];
                    I.matrix[k][j] -= t * I.matrix[i][j];
                    cout<<"R"<<k+1<<" = R"<<k+1<<" - "<<t<<"*R"<<i+1<<endl<<m1<<" "<<I<<endl;
                }

            }
        }
        cout<<I<<endl;
        return I;
    
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
    //matrix subtraction
    friend Matrix operator-(const Matrix& m1, const Matrix& m2);
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
//matrix subraction
Matrix operator-(const Matrix& m1, const Matrix& m2){
       Matrix result(m1.rows, m1.columns); //will have same size as m1
        for (int i = 0; i < m1.rows; i++) {
            for (int j = 0; j < m1.columns; j++) {
                result.matrix[i][j] =
                    m1.matrix[i][j] -
                    m2.matrix[i][j];
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
