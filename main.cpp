#include<iostream>
#include<fstream>
#include "Grid.h"
using namespace std;

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
