#include<iostream>
#include "Grid.h"


int main(){
  Grid a;
  a.set(500,500,20,10);
  a.setDepth(10);
  double k;
  k = a.get_x();
  std::cout << k<< std::endl;
  a.show();
  return 0;
}
