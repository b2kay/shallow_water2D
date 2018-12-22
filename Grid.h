#ifndef GRID_H
#define GRID_H
#include <netcdfcpp.h>
const double gravity = 9.81;

class Grid{
  private:
    double x_length; // length in x direction
    double y_length; // length in y direction
    double** h0; // the depth in 2 dimension
    double** h; // the depth in 2 dimension
    double** u; // the depth in 2 dimension
    double** v; // the depth in 2 dimension
    double** zeta; // the depth in 2 dimension
    double** zeta_star; // the depth in 2 dimension
    //grid parameters
    double dx; //grid spacing in x direction
    double dy; // grid spacing in y direction
    bool isflat; // the depth type
    bool initialized; // the depth type
    int grid_dimx, grid_dimy;
    
  public:
    Grid(double, double, double, double, bool);
    void setDepth(double m_h);
    double get_x();
    double get_y();
    double get_dx();
    double get_dy();
    double** get_h();
    int get_grid_dimx();
    int get_grid_dimy();
    void show();
    void maxDepth();
    void minDepth();
    void initialize(int mode);
    void solve(Grid myGrid, float dt,float time, float epsilon);

};
#endif
