#include<iostream>
#include "Grid.h"
#include <cmath>
using namespace std;
const double gravity = 9.81;

int solve(Grid myGrid, float dt,float time, float epsilon){
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
    double** zeta_star;
    int xdim =  myGrid.get_grid_dimx();
    int ydim =  myGrid.get_grid_dimy();
    std::cout << xdim<< std::endl;
    u = new double*[xdim];
    v = new double*[xdim];
    zeta = new double*[xdim];
    zeta_star = new double*[xdim];
    for(int i = 0; i < xdim ; i++){
      u[i] = new double[ydim];
      v[i] = new double[ydim];
      zeta[i] = new double[ydim];
      zeta_star[i] = new double[ydim];
    }
    for(int i = 0; i < xdim; i++){
      for(int j = 0; j < ydim; j++){
//         if(i == xdim/2 && j == ydim/2){
//            u[i][j] = 0.0;
//            v[i][j] = 0.0;
//            zeta[i][j] = 1.0;
//            zeta_star[i][j] = 1.0;
//         }else{
            u[i][j] = 0.0;
            v[i][j] = 0.0;
            zeta[i][j] = 0.0;
            zeta_star[i][j] = 0.0;
//         }
//         std::cout << i << " : " << j << " = " << zeta[i][j]<< std::endl;
      }
    }
    zeta[xdim/2][ydim/2] = 1.0;
    zeta_star[xdim/2][ydim/2] = 1.0;
    std::cout <<  zeta[xdim/2][ydim/2] << std::endl;
    double x = myGrid.get_x();
    double y = myGrid.get_y();
    double dx = myGrid.get_dx();
    double dy = myGrid.get_dy();
    double** h = myGrid.get_h();
    double he,hw,hn,hs;
    for(int t=0;t<time/dt;t++){
            for(int j=1;j<y/dy+1;j++){
                    for(int k=1;k<x/dx+1;k++){
                            u[j][k]=u[j][k]-dt*gravity*(zeta[j][k+1]-zeta[j][k])/dx;
                            v[j][k]=v[j][k]-dt*gravity*(zeta[j+1][k]-zeta[j][k])/dy;
                    }
            }
            for(int j=1;j<y/dy+1;j++)
                    for(int k=1;k<x/dx+1;k++){
                            if(u[j][k]>0)
                                    he=h[j][k];
                            else if(u[j][k]<0)
                                    he=h[j][k+1];
                            if(u[j][k-1]>0)
                                    hw=h[j][k-1];
                            else if(u[j][k-1]<0)
                                    hw=h[j][k];
                            if(v[j][k]>0)
                                    hn=h[j][k];
                            else if(v[j][k]<0)
                                    hn=h[j+1][k];
                            if(v[j-1][k]>0)
                                    hs=h[j-1][k];
                            else if(v[j-1][k]<0)
                                    hs=h[j][k];
                            zeta_star[j][k]=zeta[j][k]-dt*(u[j][k]*he-u[j][k-1]*hw)/dx-dt*(v[j][k]*hn-v[j-1][k]*hs)/dy;
                    }
            for(int j=1;j<y/dy+1;j++)
                    for(int k=1;k<x/dx+1;k++)
                    zeta[j][k]=(1-epsilon)*zeta_star[j][k]+0.25*epsilon*(zeta_star[j][k-1]+zeta_star[j][k+1]+zeta_star[j-1][k]+zeta_star[j+1][k])/dy;

            if(t%5==0){
                    //std::cout <<  zeta[xdim/2][ydim/2] << std::endl;
                    std::cout <<  t << " : " << zeta[xdim/2][ydim/2]<< std::endl;
                    //add.put_data(zeta,u,v);
            }

    }

    return 0;
}

int main(){
  Grid a(500,500,10,10,true);
  a.setDepth(10);
  double k;
//  k = a.get_grid_dimx();
//  std::cout << k<< std::endl;
  a.show();
  solve(a, 0.1, 100, 0.1);
  return 0;
}
