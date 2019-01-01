make clean > log
make >> log
./main.x >> log
octave animation.m >> log
convert -delay 10 png/*png anim.gif >>log
eog anim.gif
