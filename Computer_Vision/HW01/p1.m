% exportgraphics() requires R2020a or later

clear;
x = -1000:1:1000;
p1_a = figure('Visible', 'off');
plot(x, normpdf(x, 0, 5));
title('mean = 0, stdev = 5');
if isfile('p1_a.jpg')
    fprintf(2, 'Warning: p1_a.jpg exists, aborting.\n');
else
    exportgraphics(p1_a, 'p1_a.jpg', 'Resolution', 1200); 
end
if isfile('p1_a.pdf')
    fprintf(2, 'Warning: p1_a.pdf exists, aborting.\n');
else
    exportgraphics(p1_a, 'p1_a.pdf', 'ContentType', 'vector');
end

p1_b = figure('Visible', 'off');
plot(x, normpdf(x, 0, 150));
title('mean = 0, stdev = 150');
if isfile('p1_b.jpg')
    fprintf(2, 'Warning: p1_b.jpg exists, aborting.\n');
else
    exportgraphics(p1_b, 'p1_b.jpg', 'Resolution', 1200);
end
if isfile('p1_b.pdf')
    fprintf(2, 'Warning: p1_b.pdf exists, aborting.\n');
else
    exportgraphics(p1_b, 'p1_b.pdf', 'ContentType', 'vector');
end
