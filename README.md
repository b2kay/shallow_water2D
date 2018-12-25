# shallow_water2D
2D Shallow Water Equation Solver
## Requirements
 apt-get install libnetcdf libnetcdf-dev
 apt install libnetcdf-c++4-dev libnetcdf-cxx-legacy-dev
## Compilation and Run
 make

 ./main.x

## plot and save png
 ncview output.nc
or
 octave animation.m (in this case eta*.png files will be saved in png folder)
 cd png
 convert -delay 10 *.png anim.gif

## Parameters file
1st row : x spacing
2nd row : y spacing
3rd : timestep
4th : total time

