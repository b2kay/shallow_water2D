#ifndef GRID_H
#define GRID_H
class Grid{
  private:
    double x_length; // length in x direction
    double y_length; // length in y direction
    double** h; // the depth in 2 dimension
    double dx; //grid spacing in x direction
    double dy; // grid spacing in y direction
    bool isflat; // the depth type
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

};
#endif
