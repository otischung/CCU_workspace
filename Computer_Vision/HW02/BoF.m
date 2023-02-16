clear;
clc;
% ===================================================================================================
% The Bag of Features is used in this program
% https://www.mathworks.com/help/vision/ug/image-category-classification-using-bag-of-features.html
% ===================================================================================================

%% Adjust Hyperparamenters
dataFolder = ".\plant-seedlings-classification\";
maskDataFolder = ".\plant-seedlings-classification-masked\";
maskResizedDataFolder = ".\plant-seedlings-classification-masked-resized\";
trainDataFolder = "train\";
testDataFolder = "test\";
result_csv = ".\result.csv";
imageTargetSize = 150;
showTrainDatasetImage = false;
showTestDatasetImage = false;
showCompareImage = true;

% Training Step
%% Create image dataset
fprintf(2, "Creating Dataset...\n");
trainImageData = imageDatastore(maskResizedDataFolder + trainDataFolder, ...
    "IncludeSubfolders", true, ...
    "LabelSource", "foldernames", ...
    "FileExtensions", ".png");
testImageData = imageDatastore(maskResizedDataFolder + testDataFolder, ...
    "FileExtensions", ".png");
numTrain = size(trainImageData.Files, 1);
numTest = size(testImageData.Files, 1);
fprintf(2, "Creating Dataset Finished.\n\n");

% Separate the sets into training and validation data
[trainSet, validSet] = splitEachLabel(trainImageData, 0.9, "randomized");

%% Create Bag of Features
% https://www.mathworks.com/help/vision/ref/bagoffeatures.html
bag = bagOfFeatures(trainSet, ...
    "GridStep", [8, 8], ...
    "TreeProperties", [1, 100000], ...
    "StrongestFeatures", 1, ...
    "Verbose", true, ...
    "UseParallel", true);

%% Encoded training images from each category
% This function relies on the multiclass linear SVM classifier, we have
% modified to RBF kernel.
% https://www.mathworks.com/help/vision/ref/trainimagecategoryclassifier.html
% opt = templateSVM("BoxConstraint", 12, "KernelFunction", "rbf");
% categoryClassifier = trainImageCategoryClassifier(trainSet, bag, "LearnerOptions", opt, "Verbose", true, "UseParallel", true);
categoryClassifier = trainImageCategoryClassifier(trainSet, bag, "Verbose", true, "UseParallel", true);

%% Evaluate Classifier Performance by producing near perfect confusion matrix
% https://www.mathworks.com/help/vision/ref/imagecategoryclassifier.evaluate.html
[confTrainMatrix, truthLabelIdx, predLabelIdx, trainScore] = evaluate(categoryClassifier, trainSet);
[confValidMatrix, truthLabelIdx, predLabelIdx, validScore] = evaluate(categoryClassifier, validSet);

%% Inference Step
% Read all data in datastore
% https://www.mathworks.com/help//vision/ref/imagecategoryclassifier.predict.html
fprintf("Transfering Dataset into Cell...\n");
testImg = readall(testImageData, "UseParallel", true);
fprintf("Transfering Dataset into Cell Finished.\n\n");

bar = waitbar(0, sprintf("Inferencing, 0/%d", numTest), ...
    "CreateCancelBtn", "setappdata(gcbf, ""canceling"", true)");
fp = fopen(result_csv, "w+");
fprintf(fp, "%s,%s\n", "file", "species");
for i = 1:size(testImg, 1)
    if getappdata(bar, "canceling")
        break;
    end
    waitbar(i / numTest, bar, sprintf("Inferencing: %d/%d", i, numTest));
    [labelIdx, scores] = predict(categoryClassifier, cell2mat(testImg(i)), "Verbose", false);
    labelName = string(categoryClassifier.Labels(labelIdx));
    fileName = string(testImageData.Files(i));
    fileName = split(fileName, "\");
    fileName = fileName(end);
    fprintf(fp, "%s,%s\n", fileName, labelName);
end
fclose(fp);
delete(bar);

%% test
% https://www.mathworks.com/help/vision/ug/create-a-custom-feature-extractor.html
