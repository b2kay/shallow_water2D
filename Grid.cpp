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
  grid_dimx= x_length/dx+2;
  grid_dimy = y_length/dy+2;
  h = new double*[grid_dimx];
  //initialize h
  if(isflat){
    for(int i = 0; i < grid_dimx; i++){
      h[i] = new double[grid_dimy];
    }
    for(int i = 1; i < grid_dimx-1; i++){
      for(int j = 1; j < grid_dimy-1; j++){
        h[i][j] = m_h;

//        std::cout << i << " : " << j << " = " << h[i][j]<< std::endl;
      }
    for(int i = 1; i < grid_dimx-1; i++){
        h[i][0] = 0;
        h[0][i] = 0;
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

