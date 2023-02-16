clear;
clc;

img = imread(".\plant-seedlings-classification\train\Black-grass\1af1eddd3.png");
imgRed = img(:,:,1);
imgGreen = img(:,:,2);
imgBlue = img(:,:,3);
imgGray = rgb2gray(img);
imgGrayGaussFilt = imgaussfilt(imgGray, 1, FilterSize=7);

% imshow([imgGray, imgGrayGaussFilt]);

[yRed, x] = imhist(imgRed);
[yGreen, x] = imhist(imgGreen);
[yBlue, x] = imhist(imgBlue);

% plot(x, yRed, "Red", x, yGreen, "Green", x, yBlue, "Blue");
% imshow(img(:,:,2));

% Harris corner detection
corners = detectHarrisFeatures(imgGray);
% imshow(imgGray);
% hold on;
% plot(corners.selectStrongest(50));

% Edge detection
imgSobel = edge(imgGrayGaussFilt, "sobel");
imgCanny = edge(imgGrayGaussFilt, "canny");
imgPrewitt = edge(imgGrayGaussFilt, "prewitt");
imgRoberts = edge(imgGrayGaussFilt, "roberts");
% imshow([imgSobel, imgCanny; imgPrewitt, imgRoberts]);

% points = detectSIFTFeatures(imgGray);
% imshow(imgGray);
% hold on;
% plot(points.selectStrongest(10));

% WTF = imshow(img);
% roi = images.roi.AssistedFreehand(WTF, "Color", [62/255, 82/255, 37/255]);
% draw(roi);

imgHSV = rgb2hsv(img);
trans = imgHSV(:,:,1) >= 60 / 360 & imgHSV(:,:,1) <= 90 / 360;
maskedImg = bsxfun(@times, img, cast(trans, "like", img));
imshow(maskedImg);
