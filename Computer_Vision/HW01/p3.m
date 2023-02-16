clear;
pic = imread('resized.jpg');

% pic_1 = imgaussfilt(pic, 1, "FilterSize", 3);
% imshow(pic_1);

x = -1:1:1;
y = -1:1:1;
[X, Y] = meshgrid(x, y);
A = [X(:), Y(:)];
z = mvnpdf(A, 0, [1 1]);
z = reshape(z, length(y), length(x));
z = z / sum(z, 'all');

pic_33 = zeros(size(pic));
for i = 1:1:3
    pic_33(:,:,i) = conv2(double(pic(:,:,i)), z, 'same');
end
pic_33 = uint8(pic_33);
if isfile('p3_a.jpg')
    fprintf(2, 'Warning: p3_a.jpg exists, aborting.\n');
else
    imwrite(pic_33, 'p3_a.jpg', 'jpg');
end

x = -3:1:3;
y = -3:1:3;
[X, Y] = meshgrid(x, y);
A = [X(:), Y(:)];
z = mvnpdf(A, 0, [1 1]);
z = reshape(z, length(y), length(x));
z = z / sum(z, 'all');

pic_77 = zeros(size(pic));
for i = 1:1:3
    pic_77(:,:,i) = conv2(double(pic(:,:,i)), z, 'same');
end
pic_77 = uint8(pic_77);
if isfile('p3_b.jpg')
    fprintf(2, 'Warning: p3_b.jpg exists, aborting.\n');
else
    imwrite(pic_77, 'p3_b.jpg', 'jpg');
end
