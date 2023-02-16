clear;
clc;

%% Adjust Hyperparamenters
dataFolder = ".\plant-seedlings-classification\";
maskDataFolder = ".\plant-seedlings-classification-masked\";
trainDataFolder = "train\";
testDataFolder = "test\";
result_csv = ".\result.csv";
imageTargetSize = 150;
showTrainDatasetImage = false;
showTestDatasetImage = false;
showCompareImage = true;

%% Reset Mask Data Folder
if exist(maskDataFolder, "dir")
    rmdir(maskDataFolder, "s"); 
end
mkdir(maskDataFolder);
mkdir(maskDataFolder + "train");
mkdir(maskDataFolder + "test");

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

%% Mask Image
bar = waitbar(0, sprintf("Masking Training Dataset, 0/%d", numTrain), ...
    "CreateCancelBtn", "setappdata(gcbf, ""canceling"", true)");
for i = 1:numTrain
    if getappdata(bar, "canceling")
        break;
    end
    waitbar(i / numTrain, bar, sprintf("Masking Training Dataset: %d/%d", i, numTrain));
    img = read(trainImageData);
    img = MaskImg(img);
    fig = figure("Visible", "off");
    imshow(img);
    fileName = string(trainImageData.Files(i));
    fileName = split(fileName, "\");
    fileName = fileName(end);
    labelName = string(trainImageData.Labels(i));
    if ~exist(maskDataFolder + "train\" + labelName, "dir")
        mkdir(maskDataFolder + "train\" + labelName);
    end
    exportgraphics(fig, maskDataFolder + "train\" + labelName + "\" + fileName);
    close(fig);
    clear fig;
end
delete(bar);

bar = waitbar(0, sprintf("Masking Testing Dataset, 0/%d", numTest), ...
    "CreateCancelBtn", "setappdata(gcbf, ""canceling"", true)");
for i = 1:numTest
    if getappdata(bar, "canceling")
        break;
    end
    waitbar(i / numTest, bar, sprintf("Masking Testing Dataset: %d/%d", i, numTest));
    img = read(testImageData);
    img = MaskImg(img);
    fig = figure("Visible", "off");
    imshow(img);
    fileName = string(testImageData.Files(i));
    fileName = split(fileName, "\");
    fileName = fileName(end);
    exportgraphics(fig, maskDataFolder + "test\" + fileName);
    close(fig);
    clear fig;
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
