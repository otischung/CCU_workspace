clear;
clc;

% Always create content-obscured, executable files.
% pcode("*.m");

dataFolder = ".\plant-seedlings-classification\";
maskDataFolder = ".\plant-seedlings-classification-masked\";
trainDataFolder = "train\";
testDataFolder = "test\";
result_csv = ".\result.csv";
imageTargetSize = 150;
showTrainDatasetImage = false;
showTestDatasetImage = false;
showCompareImage = false;

% Create image dataset
% Ref: https://www.mathworks.com/help/deeplearning/ug/data-sets-for-deep-learning.html
% The doc. of imageDatastore is shown below
% https://www.mathworks.com/help/matlab/ref/matlab.io.datastore.imagedatastore.html
fprintf(2, "Creating Dataset...\n");
trainImageData = imageDatastore(maskDataFolder + trainDataFolder, ...
    "IncludeSubfolders", true, ...
    "LabelSource", "foldernames", ...
    "FileExtensions", ".png");
testImageData = imageDatastore(maskDataFolder + testDataFolder, ...
    "FileExtensions", ".png");
numTrain = size(trainImageData.Files, 1);
numTest = size(testImageData.Files, 1);
fprintf(2, "Creating Dataset Finished.\n\n");

% Read all data in datastore
fprintf(2, "Transfering Dataset into Cell...\n");
trainImg = readall(trainImageData, "UseParallel", true);
testImg = readall(testImageData, "UseParallel", true);
fprintf(2, "Transfering Dataset into Cell Finished.\n\n");

% Convert cell datatype (struct) to matrix (array)
% Since the dimensions of arrays being concatenated are not consistent,
% i.e., it may be 196*196 instead of imageTargetSize*imageTargetSize,
% we need to resize them to all imageTargetSize*imageTargetSize
% Ref of cell2mat: https://www.mathworks.com/help/matlab/ref/cell2mat.html#d124e176481
% Ref of arrayfun: https://www.mathworks.com/help/matlab/ref/arrayfun.html

bar = waitbar(0, sprintf("Converting Training Image to Matrix, 0/%d", numTrain));
for i = 1:size(trainImg)
    waitbar(i / numTrain, bar, sprintf("Converting Training Image to Matrix, %d/%d", i, numTrain));
%     fprintf(2, "Converting %d/%d image to matrix...\n", i, numTrain);
    image = cell2mat(trainImg(i));
    image = imresize(image, [imageTargetSize, imageTargetSize]);
    trainMat(:,i) = double(reshape(image, imageTargetSize * imageTargetSize * 3, 1));
    if showTrainDatasetImage
        imshow(image);
        drawnow;
        pause(0.01);
    end
end
delete(bar)

bar = waitbar(0, sprintf("Converting Testing Image to Matrix, 0/%d", numTest));
for i = 1:size(testImg)
    waitbar(i / numTest, bar, sprintf("Converting Testing Image to Matrix, %d/%d", i, numTest));
    image = cell2mat(testImg(i));
    image = imresize(image, [imageTargetSize, imageTargetSize]);
    testMat(:,i) = double(reshape(image, imageTargetSize * imageTargetSize * 3, 1));
    if showTestDatasetImage
        imshow(image);
        drawnow;
        pause(0.01);
    end
end
delete(bar)

trainMat = gpuArray(transpose(trainMat));
testMat = gpuArray(transpose(testMat));

% create NN search object
% https://www.mathworks.com/help/stats/createns.html
% https://www.mathworks.com/help/stats/exhaustivesearcher.knnsearch.html

numTest = size(testMat, 1);
% NNSearch = createns(trainMat, "NSMethod", "exhaustive", "Distance", "cityblock");
NNSearch = createns(trainMat, "Distance", "cityblock");

% Waitbar Ref: https://www.mathworks.com/help/matlab/ref/waitbar.html
bar = waitbar(0, sprintf("Inferencing, 0/%d", numTest), ...
    "CreateCancelBtn", "setappdata(gcbf, ""canceling"", true)");
fp = fopen(result_csv, "w+");
fprintf(fp, "%s,%s\n", "file", "species");
for i = 1:numTest
    if getappdata(bar, "canceling")
        break;
    end
    waitbar(i / numTest, bar, sprintf("Inferencing: %d/%d", i, numTest));
    [n, d] = knnsearch(NNSearch, testMat(i,:), "k", 10);
    fileName = string(testImageData.Files(i));
    fileName = split(fileName, "\");
    fileName = fileName(end);
    labelName = string(trainImageData.Labels(n(1)));
    fprintf(fp, "%s,%s\n", fileName, labelName);
    if showCompareImage
        testCompareImage = testMat(i,:);
        testCompareImage = transpose(testCompareImage);
        testCompareImage = reshape(testCompareImage, imageTargetSize, imageTargetSize, 3);
        testCompareImage = uint8(testCompareImage);
        NNImage = NNSearch.X(n(1),:);
        NNImage = transpose(NNImage);
        NNImage = reshape(NNImage, imageTargetSize, imageTargetSize, 3);
        NNImage = uint8(NNImage);
        imshow([testCompareImage, NNImage]);
    end
end
fclose(fp);
delete(bar);
