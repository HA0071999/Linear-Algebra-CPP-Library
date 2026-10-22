#include <iostream>
#include "LinearSystem.h"
#include "Matrix.h"
using namespace std;
int main() {
   
    LinearSystem l(2,3);
    l.input_linear_system();
    l.print();
    l.solve_using_gaus();
    
}