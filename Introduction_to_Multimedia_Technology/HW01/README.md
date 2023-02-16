**Introduction to Multimedia Technology HW01 \-  CSIE 4B 408410120  鍾博丞**

---

**Environment Requirements**

MATLAB R2020a \- for `exportgraphics()`

Image Processing Toolbox \- for `histeq()` (histogram equalization), `ordfilt2()` (order statistic filter).

*This MarkDown file is edited by Typora*

# Find Nearest Neighbor

## Result

Our result is extraordinary, we have reached an average of **<font color=#FF0000>90% accuracy</font>** for the testing dataset using **SAD** in this project.

![1](./Correct_Image_Folder/1.jpg)

![10](./Correct_Image_Folder/10.jpg)

![20](./Correct_Image_Folder/20.jpg)

![30](./Correct_Image_Folder/30.jpg)

![40](./Correct_Image_Folder/40.jpg)

## Implementation

We remove all the "Ambient" `.pgm` file because it is unnecessary and the size is 480 \* 640 instead of 192 \* 168.

Two image processing methods are used in image preprocessing.

- Histogram equalization
  - In order to enhance some images that look very dark.
- 3\*3 median filter
  - In order to remove salt-and-pepper noise.

The **SAD** (Sum of Absolute Differences) is used in this project.

The function `createns()` in MATLAB is to create the nearest neighbor searcher object.

We specify the Name-Value argument "cityblock", which is the implementation of SAD.

## Discussion

- Image preprocessing plays an important role in this project.
- If we use the original image directly, then the accuracy will be only 60%.
