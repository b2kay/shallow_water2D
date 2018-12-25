#include<iostream>
#include<fstream>
#include "Grid.h"
using namespace std;
int read_params(ifstream &file_obj, double* params);
int main(){
  double parameters[4]; 
  // open param.txt and read
  // param[0] grid spacing x
  // param[1] grid spacing y
  // param[2] timestep
  // param[3] simulation time
  ifstream input_file("param.txt");
  read_params(input_file, parameters);
  // Grid class parameters:
  // x length
  // y length
  // x dimension spacing
  // y dimension spacing
  // bathymetry (flat,xslope,yslope)
  Grid a(500,500,parameters[0],parameters[1],flat);
  a.setDepth(10);
  // initialize u,v: parameters:  mode 1 dam-break case
  a.initialize();
  a.show();
  a.solve(a, parameters[2], parameters[3], 0.1);
  return 0;
}

int read_params(ifstream &file_obj,double *params){
  if (!file_obj){
    cerr << "error: open file for output failed!" << endl;
    return -1;
  }
  int i = 0;
  while(!file_obj.eof()){
      file_obj >> params[i]; 
      i++;
  }
  file_obj.close();
}
