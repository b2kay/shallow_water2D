#include<iostream>
#include <cmath>
#include "Grid.h"

template <class T>
T** array2d(int m, int n){
  T** A = new T*[m];
  for(int i=0; i<m; i++){
    A[i] = new T[n];
  }
  return A;
}

Grid::Grid(double m_x, double m_y, double m_dx, double m_dy, bool m_flat) : x_length(m_x), y_length(m_y), dx(m_dx), dy(m_dy), isflat(m_flat){} 
void Grid::setDepth(double m_h){
  grid_dimx= x_length/dx+2;
  grid_dimy = y_length/dy+2;
  h0 = new double*[grid_dimx];
  //initialize h
  if(isflat){
    for(int i = 0; i < grid_dimx; i++){
      h0[i] = new double[grid_dimy];
    }
    for(int i = 1; i < grid_dimx-1; i++){
      for(int j = 1; j < grid_dimy-1; j++){
        h0[i][j] = m_h;

//        std::cout << i << " : " << j << " = " << h[i][j]<< std::endl;
      }
    for(int i = 0; i < grid_dimx; i++){
        h0[i][0] = 0;
        h0[i][grid_dimy-1] = 0;
    }
    for(int i = 0; i < grid_dimy; i++){
        h0[0][i] = 0;
        h0[grid_dimx-1][i] = 0;
    }
    }
    
  }else{
    //to implement
  }
}
double Grid::get_x(){
  return x_length;
}
double Grid::get_y(){
  return y_length;
}
double Grid::get_dx(){
  return dx;
}
double Grid::get_dy(){
  return dy;
}
double** Grid::get_h(){
  return h;
}
int Grid::get_grid_dimx(){
  return grid_dimx;
}
int Grid::get_grid_dimy(){
  return grid_dimy;
}
void Grid::show(){
  std::cout << "Grid resolution : " << x_length/dx+2 << "x" << y_length/dy+2  << std::endl;
  std::cout << "Max Depth : "  << std::endl;
  std::cout << "Min Depth : "  << std::endl;
}
void Grid::maxDepth(){
}
void Grid::minDepth(){
}
void Grid::initialize(int mode=1){
  h = array2d<double>(grid_dimx,grid_dimy);
  u = array2d<double>(grid_dimx,grid_dimy);
  v = array2d<double>(grid_dimx,grid_dimy);
  zeta = array2d<double>(grid_dimx,grid_dimy);
  zeta_star = array2d<double>(grid_dimx,grid_dimy);
  if(mode==1){
    for(int k=0; k<grid_dimx;k++){
      for(int j=0; j<grid_dimy;j++){
        zeta[k][j] = 0.0;
        zeta_star[k][j] = 0.0;
        h[k][j] = h0[k][j]+zeta[k][j];
        u[k][j] = 0.0;
        v[k][j] = 0.0;
      }
    }
    zeta[grid_dimx/2][grid_dimy/2] = 1.0;
  }
  initialized = 1;
}

void Grid::solve(Grid myGrid, float dt,float time, float epsilon){
    if(!initialized){
        std::cout << "parameters is not initialized"  << std::endl;
    }else{
    // Test stability criteria
    double min_spacing = myGrid.get_dx();
    if (min_spacing > myGrid.get_dy())
        min_spacing = myGrid.get_dy();
    if(dt > (min_spacing / (sqrt(2*gravity*10)) )){
        std::cout << "Error! Stability Criteria is not satisfied." << std::endl;
    }
    double x = myGrid.get_x();
    double y = myGrid.get_y();
    double he,hw,hn,hs;
    NcFile ofile("output.nc", NcFile::Replace);
    // add dimensions
    NcDim *dim_x = ofile.add_dim("x", grid_dimx);
    NcDim *dim_y = ofile.add_dim("y", grid_dimy);
    NcDim *dim_t = ofile.add_dim("time");

   // create variables
    NcVar *var_z = ofile.add_var("zeta", ncFloat, dim_t, dim_y, dim_x);
    var_z->add_att("units", "meter");
    var_z->add_att("long_name", "free surface height");

    std::cout << h[grid_dimx/2][grid_dimy/2] << std::endl;
    // simulation loop
    for(int t=0;t<=time/dt;t++){
       for(int j=1;j<grid_dimy-1;j++){
         for(int k=1;k<grid_dimx-1;k++){
           u[j][k]=u[j][k]-dt*gravity*(zeta[j][k+1]-zeta[j][k])/dx;
           v[j][k]=v[j][k]-dt*gravity*(zeta[j+1][k]-zeta[j][k])/dy;
         }
        }
       for(int j=1;j<grid_dimy-1;j++){
         for(int k=1;k<grid_dimx-1;k++){
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
           // shapiro filter
           zeta[j][k]=(1-epsilon)*zeta_star[j][k]+0.25*epsilon*(zeta_star[j][k-1]+zeta_star[j][k+1]+zeta_star[j-1][k]+zeta_star[j+1][k]);
         }
       }
       for(int j=1;j<grid_dimy-1;j++){
         for(int k=1;k<grid_dimx-1;k++){
           h[j][k] = h0[j][k] + zeta[j][k];
         }
       }
       if(t%5==0){
         std::cout <<  zeta[grid_dimx/2][grid_dimy/2] << std::endl;
         std::cout <<  t/5 << std::endl;
         var_z->put_rec(&zeta[0][0],t/5);
       }
//
    }
    ofile.close();
//
  }
}

