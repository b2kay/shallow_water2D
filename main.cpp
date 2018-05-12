#include<iostream>
#include "Grid.h"
#include <cmath>
using namespace std;
const double gravity = 9.81;

int solve(Grid myGrid, float dt,float time, float eta){
    // stability criteria
    double min_spacing = myGrid.get_dx();
    if (min_spacing > myGrid.get_dy())
        min_spacing = myGrid.get_dy();
    if(dt > (min_spacing / (sqrt(2*gravity*10)) )){
        cout << " time spacing is too large." << endl;
    }
    double**** timeArray;
    return 0;
}

int main(){
  Grid a(500,500,10,10,true);
  a.setDepth(10);
  double k;
  k = a.get_x();
  std::cout << k<< std::endl;
  a.show();
  solve(a, 5.7, 100, 1);
  return 0;
}
