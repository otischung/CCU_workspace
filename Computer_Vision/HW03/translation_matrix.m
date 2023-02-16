clear;
clc;

%% Read csv file
mat2d = readmatrix("pt2d.csv");
mat3d = readmatrix("pt3d.csv");
dataAmount = size(mat2d, 1);

%% Find projection matrix
A = zeros(2 * size(mat2d, 1), 12);
for i = 1:dataAmount
    A(2 * i - 1, 1:3) = mat3d(i,:);
    A(2 * i - 1, 4) = 1;
    A(2 * i - 1, 9:12) = [mat3d(i,:), 1] .* -mat2d(i, 1);
    A(2 * i, 5:7) = mat3d(i,:);
    A(2 * i, 8) = 1;
    A(2 * i, 9:12) = [mat3d(i,:), 1] .* -mat2d(i, 2);
end

[eigenvector, eigenvalue] = eig(transpose(A) * A);
% proj1d = eigenvalue(1, 1) .* eigenvector(:,1);
proj1d = eigenvector(:,1);
proj = reshape(proj1d, 4, 3);
proj = transpose(proj);

%% Calculate calibration matrix and rotation matrix
M = inv(proj(1:3, 1:3));
[Q, R] = qr(M);
calibration = inv(R);
rotation = inv(Q);

%% Calculate translation matrix
% translation = inv(calibration) * proj(:,4);  % This is slow.
translation = calibration \ proj(:,4);

%% Calculate project error
total_error = 0;
for i = 1:dataAmount
    p = proj * transpose([mat3d(i,:), 1]);
    p = p / p(3,1);
    total_error = total_error + norm(transpose([mat2d(i,:), 1]) - p);
end
error = total_error / dataAmount;
