clear all; close all;clc;
files = glob('./eta/*.dat')
tx = ty = linspace (0, 500, 50)';
[xx, yy] = meshgrid (tx, ty);
abspath = './png/';
fh = figure();
az = 40;
el = 45;
for i=1:numel(files)
  [~, name] = fileparts (files{i});
  eval(sprintf('%s = load("%s", "-ascii");', name, files{i}));
  eval(sprintf('%s = %s(2:51,2:51);', name, name));
  % create figure.
  clf
  eval(sprintf('surf(xx, yy, %s);', name));

  view(az, el);
  hidden on
  axis tight
  xlabel('x')
  ylabel('y')
  zlim([-0.05 0.95])
  drawnow

  framename = sprintf('./png/eta%05d.png', i);
  print(fh, framename);
endfor
