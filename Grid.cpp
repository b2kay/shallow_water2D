#include<iostream>
#include "Grid.h"

Grid::Grid(double m_x, double m_y, double m_dx, double m_dy, bool m_flat) : x_length(m_x), y_length(m_y), dx(m_dx), dy(m_dy), isflat(m_flat){} 
//void Grid::set(double m_x, double m_y, double m_dx, double m_dy ){
//  x = m_x;
//  y = m_x;
//  dx = m_dx;
//  dy = m_dy;
//  std::cout<<"x : " << x << std::endl;
//  std::cout<<"y : " << y << std::endl;
//  std::cout<<"dx : " << dx << std::endl;
//  std::cout<<"dy : " << dy << std::endl;
//}
void Grid::setDepth(double m_h){
  int Nx = x_length/dx+2;
  int Ny = y_length/dy+2;
  h = new double*[Nx];
  if(isflat){
    for(int i = 0; i < Nx; i++){
      h[i] = new double[Ny];
    }
    for(int i = 0; i < Nx; i++){
      for(int j = 0; j < Ny; j++){
        h[i][j] = m_h;
        std::cout << i << " : " << j << " = " << h[i][j]<< std::endl;
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
void Grid::show(){
  std::cout << x_length/dx << std::endl;
}
void Grid::maxDepth(){
}
void Grid::minDepth(){
}

