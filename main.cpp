#include<iostream>
#include<fstream>
#include "Grid.h"
#include <cmath>
#include <cmath>
#include <netcdfcpp.h>
using namespace std;
const double gravity = 9.81;

int solve(Grid myGrid, float dt,float time, float epsilon){
    // Test stability criteria
    double min_spacing = myGrid.get_dx();
    if (min_spacing > myGrid.get_dy())
        min_spacing = myGrid.get_dy();
    if(dt > (min_spacing / (sqrt(2*gravity*10)) )){
        cout << "Error! Stability Criteria is not satisfied." << endl;
    }
  
    //allocate velocity components and water height 
    double** u;
    double** v;
    double** zeta;
    double** zeta_star;
    int xdim =  myGrid.get_grid_dimx();
    int ydim =  myGrid.get_grid_dimy();
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
    // initialize u v zeta
    for(int i = 0; i < xdim; i++){
      for(int j = 0; j < ydim; j++){
            u[i][j] = 0.0;
            v[i][j] = 0.0;
            zeta[i][j] = 0.0;
            zeta_star[i][j] = 0.0;
      }
    }
    zeta[xdim/2][ydim/2] = 1.0;
//    zeta_star[xdim/2][ydim/2] = 1.0;
//    std::cout <<  zeta[xdim/2][ydim/2] << std::endl;

    double x = myGrid.get_x();
    double y = myGrid.get_y();
    double dx = myGrid.get_dx();
    double dy = myGrid.get_dy();
    double** h = myGrid.get_h();
    double he,hw,hn,hs;
    NcFile ofile("output.nc", NcFile::Replace);
    // add dimensions
    NcDim *dim_x = ofile.add_dim("x", xdim);
    NcDim *dim_y = ofile.add_dim("y", ydim);
    NcDim *dim_t = ofile.add_dim("time");
   
    // create variables
    NcVar *var_z = ofile.add_var("zeta", ncFloat, dim_t, dim_y, dim_x);
    var_z->add_att("units", "meter");
    var_z->add_att("long_name", "free surface height");

    for(int t=0;t<=time/dt;t++){
    
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
//                    std::cout <<  t/5 << std::endl;
                    var_z->put_rec(&zeta[0][0],t/5);
            }

    }
    ofile.close();

    return 0;
}

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
    a.show();
    solve(a, params[2], params[3], 0.1);
    return 0;
}
