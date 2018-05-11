#ifndef GRID_H
#define GRID_H
class Grid{
  private:
    double x;
    double y;
    double** h;
    double dx;
    double dy;
    bool flat;
  public:
    Grid();
    void setDepth(double m_h);
//    void show();
    void set(double m_x, double m_y, double m_dx, double m_dy );
    double get_x();
    double get_y();
    double get_dx();
    double get_dy();
    void show();
    void maxDepth();
    void minDepth();

};
#endif
