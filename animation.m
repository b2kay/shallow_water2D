clear all; close all;clc;
files = glob('./eta/*.dat')
x_spacing = 10;
y_spacing = 10;
dx = 500/x_spacing+1;
dy = 500/y_spacing+1;
tx = linspace (0, 500, dx)';
ty = linspace (0, 500, dy)';
[xx, yy] = meshgrid (tx, ty);
abspath = './png/'
az = 40;
el = 45;
fh = figure('visible','off');
for i=1:numel(files)
  [~, name] = fileparts (files{i});
  eval(sprintf('%s = load("%s", "-ascii");', name, files{i}));
  %eval(sprintf('%s = transpose(%s);', name, name));
  eval(sprintf('%s = %s(2:%d,2:%d);', name, name, dy+1,dx+1));
  % create figure.
  clf
  eval(sprintf('surf(xx, yy, %s);', name));

  view(az, el);
  hidden on
  axis tight
  xlabel('x')
  ylabel('y')
  zlim([-0.07 0.95])
  colorbar
  caxis([-0.002 0.05]) 
  drawnow

  framename = sprintf('./png/eta%05d.png', i);
  print(fh, framename);
endfor
