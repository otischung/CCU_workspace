% exportgraphics() requires R2020a or later

clear;
x = [-1 0 1];
y = [-1 0 1];
[X, Y] = meshgrid(x, y);
A = [X(:), Y(:)];
z = mvnpdf(A, 0, [1 1]);
z = reshape(z, length(y), length(x));
z = z / sum(z, 'all');
disp(z);
% p2_a = figure('Visible', 'off');
% surf(x, y, z);
% title('mean = 0, stdev = 1');
% colorbar;
% if isfile('p2_a.jpg')
%     fprintf(2, 'Warning: p2_a.jpg exists, aborting.\n');
% else
%     exportgraphics(p2_a, 'p2_a.jpg', 'Resolution', 1200); 
% end
% if isfile('p2_a.pdf')
%     fprintf(2, 'Warning: p2_a.pdf exists, aborting.\n');
% else
%     exportgraphics(p2_a, 'p2_a.pdf', 'ContentType', 'vector');
% end

z = mvnpdf(A, 0, [4 4]);
z = reshape(z, length(y), length(x));
z = z / sum(z, 'all');
disp(z);
% p2_b = figure('Visible', 'off');
% surf(x, y, z);
% title('mean = 0, stdev = 4');
% colorbar;
% if isfile('p2_b.jpg')
%     fprintf(2, 'Warning: p2_b.jpg exists, aborting.\n');
% else
%     exportgraphics(p2_b, 'p2_b.jpg', 'Resolution', 1200); 
% end
% if isfile('p2_b.pdf')
%     fprintf(2, 'Warning: p2_b.pdf exists, aborting.\n');
% else
%     exportgraphics(p2_b, 'p2_b.pdf', 'ContentType', 'vector');
% end
