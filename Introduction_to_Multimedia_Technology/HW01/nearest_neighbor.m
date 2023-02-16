clear;
clc;

dataFolder = ".\CroppedYale\";
correctImageFolder = "Correct_Image_Folder";
numTrain = 35;
showTrainDatasetImage = false;
showTestDatasetImage = false;
showCompareImage = false;

if showCompareImage
    if ~exist(correctImageFolder, "dir")
        mkdir(correctImageFolder);
    else
        delete(correctImageFolder + "\*");
    end
end

% Create image dataset
% Ref: https://www.mathworks.com/help/deeplearning/ug/data-sets-for-deep-learning.html
imageData = imageDatastore(dataFolder, ...
    "IncludeSubfolders", true, ...
    "LabelSource", "foldernames", ...
    "FileExtensions", ".pgm");

% The doc. of imageDatastore is shown below
% https://www.mathworks.com/help/matlab/ref/matlab.io.datastore.imagedatastore.html

% Split imageDataStore
% Ref: https://www.mathworks.com/help/matlab/ref/matlab.io.datastore.imagedatastore.spliteachlabel.html
[trainData, testData] = splitEachLabel(imageData, numTrain, "randomized");

% Read all data in datastore
trainImg = readall(trainData);
testImg = readall(testData);

% Convert cell datatype (struct) to matrix (array)
% Since the dimensions of arrays being concatenated are not consistent,
% i.e., it may be 480*640 instead of 192*168, 
% we need to resize them to all 192*168
% Ref of cell2mat: https://www.mathworks.com/help/matlab/ref/cell2mat.html#d124e176481
% Ref of arrayfun: https://www.mathworks.com/help/matlab/ref/arrayfun.html
% UniformOutput = false means arrayfun returns the outputs of func in cell arrays. The outputs of func can have any sizes and different data types.

% trainMat = cell2mat(arrayfun(@(x) imresize(cell2mat(x), [192, 168]), trainImg, "UniformOutput", false));
% testMat = cell2mat(arrayfun(@(x) imresize(cell2mat(x), [192, 168]), testImg, "UniformOutput", false));

for i = 1:size(trainImg)
    image = cell2mat(trainImg(i));
    if size(image) ~= [192, 168]
%         fprintf(2, "Error, %s is %d*%d, ignored.\n", string(trainData.Files(i)), size(image, 1), size(image, 2));
%         continue;
        fprintf(2, "Error, %s is %d*%d, resize to 192*168 automatically.\n", trainData.Files(i), size(image, 1), size(image, 2));
        image = imresize(image, [192, 168]);
    end
    image = histeq(image);  % histogram equalization
    image = ordfilt2(image, 5, ones(3,3));  % 3*3 median filter
    trainMat(:,i) = double(reshape(image, 192 * 168, 1));
    if showTrainDatasetImage
        imshow(image);
        drawnow;
        pause(0.01);
    end
end

for i = 1:size(testImg)
    image = cell2mat(testImg(i));
    if size(image) ~= [192, 168]
%         fprintf(2, "Error, %s is %d*%d, ignored.\n", string(testData.Files(i)), size(image, 1), size(image, 2));
%         continue;
        fprintf(2, "Error, %s is %d*%d, resize to 192*168 automatically.\n", trainData.Files(i), size(image, 1), size(image, 2));
        image = imresize(image, [192, 168]);
    end
    image = histeq(image);  % histogram equalization
    image = ordfilt2(image, 5, ones(3,3));  % 3*3 median filter
    testMat(:,i) = double(reshape(image, 192 * 168, 1));
    if showTestDatasetImage
        imshow(image);
        drawnow;
        pause(0.01);
    end
end

trainMat = transpose(trainMat);
testMat = transpose(testMat);

% create NN search object
% https://www.mathworks.com/help/stats/createns.html
% https://www.mathworks.com/help/stats/exhaustivesearcher.knnsearch.html

correct = 0;
numTest = size(testMat, 1);
NNSearch = createns(trainMat, "NSMethod", "exhaustive", "Distance", "cityblock");
for i = 1:numTest
    fprintf("Inferencing: %d/%d\r", i, numTest);
    [n, d] = knnsearch(NNSearch, testMat(i,:), "k", 38);
    bool_correct = false;
    if testData.Labels(i) == trainData.Labels(n(1))
        correct = correct + 1;
        bool_correct = true;
        if showCompareImage
            testCompareImage = testMat(i,:);
            testCompareImage = transpose(testCompareImage);
            testCompareImage = reshape(testCompareImage, 192, 168);
            testCompareImage = uint8(testCompareImage);
            NNImage = NNSearch.X(n(1),:);
            NNImage = transpose(NNImage);
            NNImage = reshape(NNImage, 192, 168);
            NNImage = uint8(NNImage);
            fig = figure("Visible", "off");
            imshow([testCompareImage, NNImage]);
            if bool_correct
                title("CORRECT test img vs. NN result CORRECT");
                fileName = sprintf("%d.jpg", correct);
                fileName = fullfile(pwd + "\" + correctImageFolder, fileName);
                exportgraphics(fig, fileName, "Resolution", 150);
            else
                title("test img vs. NN result");
            end
            drawnow;
            pause(0.01);
        end
    end
end
accuracy = correct / numTest;
fprintf("Correct: %d, Total test image: %d\nAccuracy = %f\n", correct, numTest, accuracy);
