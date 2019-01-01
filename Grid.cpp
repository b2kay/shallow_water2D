#include<iostream>
#include <cmath>
#include<cstdlib>
#include <algorithm>
#include<iomanip>
#include<fstream>
#include "Grid.h"
// templte function for 2d array creation
template <class T>
T** array2d(int m, int n){ //(dimx,dimy)
  // allocate contiguous 2d array in memory A[y][x]
  T** A = new T*[n];
  T* B = new T[m*n];
  for(int i=0; i<n; i++){
    A[i] = &(B[i*m]);
  }
  return A;
}

// save function for octave data
void save(double** data, int timestep,int dimx, int dimy)
{
  std::ofstream myfile;
  char filename[11];
  sprintf(filename,"./eta/eta%05d.dat", timestep);
  myfile.open(filename);
  for (int j = 0; j < dimy; j++){
    for (int i=0;i<dimx;i++){
      myfile << data[j][i] << " ";
    }
    myfile << "\n";
  }
  myfile.close();
}

Grid::Grid(double m_x, double m_y, double m_dx, double m_dy, bathy m_slope) : x_length(m_x), y_length(m_y), dx(m_dx), dy(m_dy), slope(m_slope){} 

void Grid::setDepth(double m_h){
  grid_dimx = x_length/dx+2;
  grid_dimy = y_length/dy+2;
  h0 = new double*[grid_dimy];
  for(int i = 0; i < grid_dimy; i++){
    h0[i] = new double[grid_dimx];
  }
  //initialize h0
  if(slope == flat){ // flat
    std::cout << "Flat case"<< std::endl;
    for(int j = 1; j < grid_dimy-1; j++){
      for(int i = 1; i < grid_dimx-1; i++){
        h0[j][i] = m_h;
      }
    }
    
  }else if(slope == xslope){ // x slope
    std::cout << "X-slope"<< std::endl;
    float x_step, cum_x_step;
    x_step = m_h/(grid_dimx-3);
    cum_x_step = 0;
    for(int i = 1; i < grid_dimx-1; i++){
      for(int j = 1; j < grid_dimy-1; j++){
        h0[j][i] = cum_x_step;
      }
      cum_x_step += x_step;
    }
  }
  else if(slope == yslope){ // y slope
    std::cout << "Y-slope"<< std::endl;
    float y_step, cum_y_step;
    y_step = m_h/(grid_dimy-3);
    cum_y_step = 0;
    for(int i = 0; i < grid_dimy; i++){
      for(int j = 0; j < grid_dimx; j++){
        h0[i][j] = cum_y_step;
      }
      cum_y_step += y_step;
    }
  }
  // initialize edges with 0
  for(int i = 0; i < grid_dimy; i++){
      h0[i][0] = 0;
      h0[i][grid_dimx-1] = 0;
  }
  for(int i = 0; i < grid_dimx; i++){
      h0[0][i] = 0;
      h0[grid_dimy-1][i] = 0;
  }
}
double Grid::get_x(){return x_length;}
double Grid::get_y(){return y_length;}
double Grid::get_dx(){return dx;}
double Grid::get_dy(){return dy;}
double** Grid::get_h(){return h;}
int Grid::get_grid_dimx(){return grid_dimx;}
int Grid::get_grid_dimy(){return grid_dimy;}
void Grid::show(){
  std::cout << "Grid resolution : " << x_length/dx+2 << "x" << y_length/dy+2  << std::endl;
  std::cout << "Max Depth : " << hmax << std::endl;
  std::cout << "Min Depth : " << hmin << std::endl;
}
void Grid::maxDepth(){
  hmax = 0;
  for(int j=0; j<grid_dimy;j++){
    for(int k=0; k<grid_dimx;k++){
      hmax = fmax(hmax,h0[j][k]);
    }
  }
}
void Grid::minDepth(){
  hmin = h0[1][1];
  for(int j=1; j<grid_dimy-1;j++){
    for(int k=1; k<grid_dimx-1;k++){
      hmin = fmin(hmin,h0[j][k]);
    }
  }
}
void Grid::initialize(){
  int mode=1;
  h = array2d<double>(grid_dimx,grid_dimy);
  u = array2d<double>(grid_dimx,grid_dimy);
  v = array2d<double>(grid_dimx,grid_dimy);
  zeta = array2d<double>(grid_dimx,grid_dimy);
  zeta_star = array2d<double>(grid_dimx,grid_dimy);
  if(mode==1){
    for(int k=0; k<grid_dimy;k++){
      for(int j=0; j<grid_dimx;j++){
        zeta[k][j] = 0.0;
        zeta_star[k][j] = 0.0;
        h[k][j] = h0[k][j]+zeta[k][j];
        u[k][j] = 0.0;
        v[k][j] = 0.0;
     }
    }
    //zeta[grid_dimx/2][grid_dimy/2] = 1.0;
    for(int k=grid_dimy/2; k<grid_dimy/2+2;k++){
      for(int j=grid_dimx/2; j<grid_dimx/2+2;j++){
         //std::cout << k << " " << j << " ";
         zeta[k][j] = 1.0;
      }
    }
  }
  this->maxDepth();
  this->minDepth();
  initialized = 1;
}

int Grid::solve(Grid myGrid, float dt,float time, float epsilon){
   std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
   std::cout << "|░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░|" << std::endl;        
   std::cout << "|░░░░Shallow Water 2D░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░|" << std::endl;        
   std::cout << "|░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░|" << std::endl;        
   std::cout << "|░░░░berkay pirlepeli░░░░2018░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░|" << std::endl;        
   std::cout << "|░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░|" << std::endl;        
   std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    if(!initialized){
      std::cout << "parameters is not initialized"  << std::endl;
      return -1;
    }else{
    // Test stability criteria
    double min_spacing = myGrid.get_dx();
    if (min_spacing > myGrid.get_dy()){
        min_spacing = myGrid.get_dy();}
    if(dt > (min_spacing / (sqrt(2*gravity*hmax)) )){
        std::cerr << "Error! Stability Criteria is not satisfied." << std::endl;
    }
    double x = myGrid.get_x();
    double y = myGrid.get_y();
    //open netcdf file
    NcFile ofile("output.nc", NcFile::Replace);
    // add dimensions
    NcDim *dim_x = ofile.add_dim("x", grid_dimx);
    NcDim *dim_y = ofile.add_dim("y", grid_dimy);
    NcDim *dim_t = ofile.add_dim("time");

   // create variables
    NcVar *var_z = ofile.add_var("zeta", ncFloat, dim_t, dim_y, dim_x);
    var_z->add_att("units", "meter");
    var_z->add_att("long_name", "free surface height");

    double he,hw,hn,hs;
    // simulation loop
    std::cout << "Simulation Loop" << std::endl;
    for(int t=0;t<time/dt+1;t++){
       // predict velocities
       for(int j=1;j<grid_dimy-1;j++){
         for(int k=1;k<grid_dimx-1;k++){
           u[j][k]=u[j][k]-dt*gravity*(zeta[j][k+1]-zeta[j][k])/dx;
           v[j][k]=v[j][k]-dt*gravity*(zeta[j+1][k]-zeta[j][k])/dy;
         }
       }
       // predict sea-level
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
         var_z->put_rec(&zeta[0][0],t/5);
       }
       if(t%50==0){
         std::cout << "Zeta at " << (t)*dt << "s saved." << std::endl;
         save(zeta, t, grid_dimx, grid_dimy);
       }
    } 
    // end of simulation loop
    std::cout << std::endl << "End of Simulation Loop" << std::endl;
    ofile.close();
  }
  return 0;
}

