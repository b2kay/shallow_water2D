#include<iostream>
#include "Grid.h"
#include <cmath>
using namespace std;
const double gravity = 9.81;

int solve(Grid myGrid, float dt,float time, float eta){
    // Test stability criteria
    double min_spacing = myGrid.get_dx();
    if (min_spacing > myGrid.get_dy())
        min_spacing = myGrid.get_dy();
    if(dt > (min_spacing / (sqrt(2*gravity*10)) )){
        cout << " time spacing is too large." << endl;
    }
  
    //allocate velocity components and water height 
    double** u;
    double** v;
    double** zeta;
    int xdim =  myGrid.get_grid_dimx();
    int ydim =  myGrid.get_grid_dimy();
    std::cout << xdim<< std::endl;
    u = new double*[xdim];
    v = new double*[xdim];
    zeta = new double*[xdim];
    for(int i = 0; i < xdim ; i++){
      u[i] = new double[ydim];
      v[i] = new double[ydim];
      zeta[i] = new double[ydim];
    }
    for(int i = 0; i < xdim; i++){
      for(int j = 0; j < ydim; j++){
         if(i == xdim/2 && j == ydim/2){
            u[i][j] = 0.0;
            v[i][j] = 0.0;
            zeta[i][j] = 1.0;
         }else{
            u[i][j] = 0.0;
            v[i][j] = 0.0;
            zeta[i][j] = 0.0;
         }
         std::cout << i << " : " << j << " = " << zeta[i][j]<< std::endl;
      }
    }

    return 0;
}

int main(){
  Grid a(50,50,10,10,true);
  a.setDepth(10);
  double k;
//  k = a.get_grid_dimx();
//  std::cout << k<< std::endl;
  a.show();
  solve(a, 0.1, 1, 1);
  return 0;
}
