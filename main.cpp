#include<iostream>
#include "Grid.h"


int main(){
  Grid a(500,500,10,10,true);
  a.setDepth(10);
  double k;
  k = a.get_x();
  std::cout << k<< std::endl;
  a.show();
  return 0;
}
