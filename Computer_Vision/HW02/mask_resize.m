clear;
clc;

%% Adjust Hyperparamenters
dataFolder = ".\plant-seedlings-classification\";
maskDataFolder = ".\plant-seedlings-classification-masked\";
maskResizedDataFolder = ".\plant-seedlings-classification-masked-resized\";
trainDataFolder = "train\";
testDataFolder = "test\";
result_csv = ".\result.csv";
imageTargetSize = 256;
showTrainDatasetImage = false;
showTestDatasetImage = false;
showCompareImage = true;

%% Reset Mask Data Folder
if exist(maskResizedDataFolder, "dir")
    rmdir(maskResizedDataFolder, "s"); 
end
mkdir(maskResizedDataFolder);
mkdir(maskResizedDataFolder + "train");
mkdir(maskResizedDataFolder + "test");

%% Create image dataset
fprintf(2, "Creating Dataset...\n");
trainImageData = imageDatastore(dataFolder + trainDataFolder, ...
    "IncludeSubfolders", true, ...
    "LabelSource", "foldernames", ...
    "FileExtensions", ".png");
testImageData = imageDatastore(dataFolder + testDataFolder, ...
    "FileExtensions", ".png");
numTrain = size(trainImageData.Files, 1);
numTest = size(testImageData.Files, 1);
fprintf(2, "Creating Dataset Finished.\n\n");

%% Read all data in datastore
fprintf(2, "Transfering Dataset into Cell...\n");
trainImg = readall(trainImageData, "UseParallel", true);
testImg = readall(testImageData, "UseParallel", true);
fprintf(2, "Transfering Dataset into Cell Finished.\n\n");

%% Convert cell datatype (struct) to matrix (array)
% Since the dimensions of arrays being concatenated are not consistent,
% i.e., it may be 196*196 instead of imageTargetSize*imageTargetSize,
% we need to resize them to all imageTargetSize*imageTargetSize
% Ref of cell2mat: https://www.mathworks.com/help/matlab/ref/cell2mat.html#d124e176481
% Ref of arrayfun: https://www.mathworks.com/help/matlab/ref/arrayfun.html

bar = waitbar(0, sprintf("Converting Training Image to Matrix, 0/%d", numTrain));
for i = 1:size(trainImg)
    waitbar(i / numTrain, bar, sprintf("Converting Training Image to Matrix, %d/%d", i, numTrain));
    image = cell2mat(trainImg(i));
    image = imresize(image, [imageTargetSize, imageTargetSize]);
    trainMat(:,:,:,i) = image;
end
delete(bar)

bar = waitbar(0, sprintf("Converting Testing Image to Matrix, 0/%d", numTest));
for i = 1:size(testImg)
    waitbar(i / numTest, bar, sprintf("Converting Testing Image to Matrix, %d/%d", i, numTest));
    image = cell2mat(testImg(i));
    image = imresize(image, [imageTargetSize, imageTargetSize]);
    testMat(:,:,:,i) = image;
end
delete(bar)

%% Mask Image
bar = waitbar(0, sprintf("Masking Training Dataset, 0/%d", numTrain), ...
    "CreateCancelBtn", "setappdata(gcbf, ""canceling"", true)");
for i = 1:numTrain
    if getappdata(bar, "canceling")
        break;
    end
    waitbar(i / numTrain, bar, sprintf("Masking Training Dataset: %d/%d", i, numTrain));
    img = trainMat(:,:,:,i);
    img = MaskImg(img);
    fig = figure("Visible", "off");
    imshow(img);
    fileName = string(trainImageData.Files(i));
    fileName = split(fileName, "\");
    fileName = fileName(end);
    labelName = string(trainImageData.Labels(i));
    if ~exist(maskResizedDataFolder + "train\" + labelName, "dir")
        mkdir(maskResizedDataFolder + "train\" + labelName);
    end
    exportgraphics(fig, maskResizedDataFolder + "train\" + labelName + "\" + fileName);
    close(fig);
end
delete(bar);

bar = waitbar(0, sprintf("Masking Testing Dataset, 0/%d", numTest), ...
    "CreateCancelBtn", "setappdata(gcbf, ""canceling"", true)");
for i = 1:numTest
    if getappdata(bar, "canceling")
        break;
    end
    waitbar(i / numTest, bar, sprintf("Masking Testing Dataset: %d/%d", i, numTest));
    img = testMat(:,:,:,i);
    img = MaskImg(img);
    fig = figure("Visible", "off");
    imshow(img);
    fileName = string(testImageData.Files(i));
    fileName = split(fileName, "\");
    fileName = fileName(end);
    exportgraphics(fig, maskResizedDataFolder + "test\" + fileName);
    close(fig);
end
delete(bar);

%% Mask Function
function result = MaskImg(input)
    imgHSV = rgb2hsv(input);
    mask = imgHSV(:,:,1) >= 50 / 360 & imgHSV(:,:,1) <= 140 / 360 & imgHSV(:,:,2) >= 0.15;
%     result = bsxfun(@times, input, cast(mask, "like", input));
    result = input .* uint8(mask);
    for j = 1:3
        result(:,:,j) = ordfilt2(result(:,:,j), 1, ones(3, 3));
    end
end
