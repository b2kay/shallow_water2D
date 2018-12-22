#include<iostream>
#include<fstream>
#include "Grid.h"
#include <cmath>
#include <netcdfcpp.h>
using namespace std;
//int solve(Grid myGrid, float dt,float time, float epsilon);

int main(){
  // open param.txt and read
  ifstream input;
  input.open("param.txt");
  double params[4];
  int i = 0;
  while(!input.eof()){
      input >> params[i]; 
      i++;
  }
  
  Grid a(500,500,params[0],params[1],true);
  a.setDepth(10);
  a.initialize(1);
  a.show();
  a.solve(a, params[2], params[3], 0.1);
  return 0;
}

//int solve(Grid myGrid, float dt,float time, float epsilon){
//    // Test stability criteria
//    double min_spacing = myGrid.get_dx();
//    if (min_spacing > myGrid.get_dy())
//        min_spacing = myGrid.get_dy();
//    if(dt > (min_spacing / (sqrt(2*gravity*10)) )){
//        cout << "Error! Stability Criteria is not satisfied." << endl;
//    }
//  
//    //allocate velocity components and water height 
//    int xdim =  myGrid.get_grid_dimx();
//    int ydim =  myGrid.get_grid_dimy();
//    double** u;
//    u = array2d<double>(xdim,ydim);
//    double** v;
//    v = array2d<double>(xdim,ydim);
//    double** zeta;
//    zeta = array2d<double>(xdim,ydim);
//    double** zeta_star;
//    zeta_star = array2d<double>(xdim,ydim);
//    // initialize u v zeta
//    for(int i = 0; i < xdim; i++){
//      for(int j = 0; j < ydim; j++){
//            u[i][j] = 0.0;
//            v[i][j] = 0.0;
//            zeta[i][j] = 0.0;
//            zeta_star[i][j] = 0.0;
//      }
//    }
//    zeta[xdim/2][ydim/2] = 1.0;
//    //zeta_star[xdim/2][ydim/2] = 1.0;
////    std::cout <<  zeta[xdim/2][ydim/2] << std::endl;
//
//    double x = myGrid.get_x();
//    double y = myGrid.get_y();
//    double dx = myGrid.get_dx();
//    double dy = myGrid.get_dy();
//    double** h0 = myGrid.get_h();
//    double he,hw,hn,hs;
//    NcFile ofile("output.nc", NcFile::Replace);
//    // add dimensions
//    NcDim *dim_x = ofile.add_dim("x", xdim);
//    NcDim *dim_y = ofile.add_dim("y", ydim);
//    NcDim *dim_t = ofile.add_dim("time");
//   
//    // create variables
//    NcVar *var_z = ofile.add_var("zeta", ncFloat, dim_t, dim_y, dim_x);
//    var_z->add_att("units", "meter");
//    var_z->add_att("long_name", "free surface height");
//
//    
//    //h[xdim/2][ydim/2] += zeta[xdim/2][ydim/2];
//
//    for(int t=0;t<=time/dt;t++){
//       for(int j=1;j<ydim-1;j++){
//         for(int k=1;k<xdim-1;k++){
//           u[j][k]=u[j][k]-dt*gravity*(zeta[j][k+1]-zeta[j][k])/dx;
//           v[j][k]=v[j][k]-dt*gravity*(zeta[j+1][k]-zeta[j][k])/dy;
//           if(u[j][k]>0)
//                   he=h[j][k];
//           else if(u[j][k]<0)
//                   he=h[j][k+1];
//           if(u[j][k-1]>0)
//                   hw=h[j][k-1];
//           else if(u[j][k-1]<0)
//                   hw=h[j][k];
//           if(v[j][k]>0)
//                   hn=h[j][k];
//           else if(v[j][k]<0)
//                   hn=h[j+1][k];
//           if(v[j-1][k]>0)
//                   hs=h[j-1][k];
//           else if(v[j-1][k]<0)
//                   hs=h[j][k];
//
//           zeta_star[j][k]=zeta[j][k]-dt*(u[j][k]*he-u[j][k-1]*hw)/dx-dt*(v[j][k]*hn-v[j-1][k]*hs)/dy;
//           zeta[j][k]=(1-epsilon)*zeta_star[j][k]+0.25*epsilon*(zeta_star[j][k-1]+zeta_star[j][k+1]+zeta_star[j-1][k]+zeta_star[j+1][k]);
//           h[j][k] += zeta[j][k];
//         }
//       }
//       if(t%5==0){
////                    std::cout <<  zeta[xdim/2][ydim/2] << std::endl;
////                    std::cout <<  t/5 << std::endl;
//                    var_z->put_rec(&zeta[0][0],t/5);
////                    var_z->put_rec(&h[0][0],t/5);
//            }
//
//    }
//    ofile.close();
//
//    return 0;
//}
