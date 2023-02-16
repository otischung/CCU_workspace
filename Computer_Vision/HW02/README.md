**Computer Vision HW02 \-  CSIE 4B 408410120  鍾博丞**

---

**Environment Requirements**

MATLAB R2020a \- for `exportgraphics()`

Image Processing Toolbox \- for `histeq()` (histogram equalization), `ordfilt2()` (order statistic filter).

Computer Vision Toolbox - for `detectHarrisFeatures()`, `bagOfFeatures()`, ..., etc.

*This MarkDown file is edited by Typora*

## Usage

First, you have to download the dataset from Kaggle

https://www.kaggle.com/competitions/plant-seedlings-classification/

The script `mask.m` provides a color mask and order statistic 3 \* 3 minimum filter.

The script `mask_resize.m` provides the services based on `mask.m` and resizes the dataset images into `imageTargetSize`, which is 256, defined in the script.

The script `knn_search.m` reads the masked and resized images and does the Nearest Neighbor (NN) directly.

The script `BoF.m` reads the masked and resized images and performs the SIFT, sorts features by the corresponding eigenvalues, balances each class in order to keep the same amount of features in each class, K-means clustering, linear kernel Support Vector Machine.



## Methods

We have done the data preprocessing by masking out the background of the images.

First, we transfer the RGB space into HSV space and then choose the target hue of green, which is $60\degree \le \text{hue} \le 90\degree$, and mask out the **low saturation** of less than **0.15**.

Then, we can create images that only contain leaves without any background.

We can get quite pure images that only contain leaves though, we still have some white points coming from the ruler in the background and the hue is in the range of green. Therefore, we use the order statistic 3 \* 3 **minimum filter** to mask out these points.

| Original image                                               | Masked image                                                 |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| ![0d5f555a3](./plant-seedlings-classification/train/Charlock/0d5f555a3.png) | ![0d5f555a3](./plant-seedlings-classification-masked/train/Charlock/0d5f555a3.png) |

The images shown above are `0d5f555a3.png` from Charlock's class.



We compare NN directly for these masked images.



We have also implemented Bag of Features (BoF) for these masked datasets. The parameters for `bagOfFeatures` we've adjusted are shown below

- First
  - Grid step: [8, 8]
  - Tree properties: [1, 10K] ([num of levels, branching factor])
  - Strongest features: 1 (100%)
- Second
  - Grid step: [8, 8]
  - Tree properties: [1, 100K]
  - Strongest features: 1 (100%)



## Result

We have 0.6738 accuracies for direct NN with masked images.

![NN_masked](./Result_Screenshots/NN_masked.png)

We have 0.76322 accuracies for the first BoF algorithm with masked images.

![BoF_1_masked](./Result_Screenshots/BoF_1_masked.png)

We have 0.75314 accuracies for the second BoF algorithm with masked images.

![BoF_2_masked](./Result_Screenshots/BoF_2_masked.png)



## Problems and difficulties

32GB RAM is not enough for the BoF method; thus, we got worse results than direct NN. Thus, we have adjusted the swap space of Windows 11 to let the swap size is between 32GB and 96GB.

