import color_space_transformation as cst
import cv2
import frequency_image_enhancement as fie
import glob
import numpy as np
import os
import shutil
import spatial_image_enhancement as sie
import sys
from bcolors import Bcolors

is_show = False
rewrite = False
src_folder = "./HW4_test_image/"
save_folder = "./Img/"
img_list = glob.glob(f"{src_folder}*.png")
sobel_0 = np.array([[-1.0, -2.0, -1.0],
                    [0.0, 0.0, 0.0],
                    [1.0, 2.0, 1.0]]).astype(np.double)
sobel_45 = np.array([[-2.0, -1.0, 0.0],
                     [-1.0, 0.0, 1.0],
                     [0.0, 1.0, 2.0]]).astype(np.double)
sobel_90 = np.array([[-1.0, 0.0, 1.0],
                     [-2.0, 0.0, 2.0],
                     [-1.0, 0.0, 1.0]]).astype(np.double)
sobel_135 = np.array([[0.0, 1.0, 2.0],
                      [-1.0, 0.0, 1.0],
                      [-2.0, -1.0, 0.0]]).astype(np.double)
# This is an example of a LoG approximation kernel where sigma = 1.4.
# LoG = np.array([[0.0, 1.0, 1.0, 2.0, 2.0, 2.0, 1.0, 1.0, 0.0],
#                 [1.0, 2.0, 4.0, 5.0, 5.0, 5.0, 4.0, 2.0, 1.0],
#                 [1.0, 4.0, 5.0, 3.0, 0.0, 3.0, 5.0, 4.0, 1.0],
#                 [2.0, 5.0, 3.0, -12.0, -24.0, -12.0, 3.0, 5.0, 2.0],
#                 [2.0, 5.0, 0.0, -24.0, -40.0, -24.0, 0.0, 5.0, 2.0],
#                 [2.0, 5.0, 3.0, -12.0, -24.0, -12.0, 3.0, 5.0, 2.0],
#                 [1.0, 4.0, 5.0, 3.0, 0.0, 3.0, 5.0, 4.0, 1.0],
#                 [1.0, 2.0, 4.0, 5.0, 5.0, 5.0, 4.0, 2.0, 1.0],
#                 [0.0, 1.0, 1.0, 2.0, 2.0, 2.0, 1.0, 1.0, 0.0]]).astype(np.double)
LoG = np.array([[0.0, 0.0, -1.0, 0.0, 0.0],
                [0.0, -1.0, -2.0, -1.0, 0.0],
                [-1.0, -2.0, 16.0, -2.0, -1.0],
                [0.0, -1.0, -2.0, -1.0, 0.0],
                [0.0, 0.0, -1.0, 0.0, 0.0]]).astype(np.double)

if __name__ == "__main__":
    # Determine if rewrite results or not
    if os.path.isdir(save_folder):
        yn = input(f"{Bcolors.WARNING}The saving folder {save_folder} exists, do you want to remove it? [y/N]: {Bcolors.ENDC}")
        if yn == "Y" or yn == "y":
            print(f"{Bcolors.FAIL}The folder {save_folder} will be removed and rebuild.{Bcolors.ENDC}")
            shutil.rmtree(save_folder)
            os.mkdir(save_folder)
            rewrite = True
        else:
            print(f"The images inside the folder {save_folder} will {Bcolors.WARNING}remain the same.{Bcolors.ENDC}")
    else:
        rewrite = True
        os.mkdir(save_folder)

    # Start Algorithm
    for i in img_list:
        path = os.path.abspath(i)
        filename = os.path.basename(path)
        print(f"Reading file: {i}")
        filename = os.path.splitext(filename)[0]
        img = cv2.imread(i, cv2.IMREAD_COLOR)  # numpy.ndarray  # BGR image

        # Transfer to RGB color space
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)  # RGB image

        # Transfer RGB to HSV
        img_hsv = cst.rgb2hsv(img.astype(np.double))

        # ----- Convolution of Sobel Operator -----
        result_sobel_0 = img_hsv.copy()
        result_sobel_0[:, :, 2] *= 255.0
        result_sobel_0[:, :, 2] = sie.conv2d(result_sobel_0[:, :, 2], sobel_0, strides=1, padding=1)
        result_sobel_0[:, :, 2] /= 255.0
        result_sobel_45 = img_hsv.copy()
        result_sobel_45[:, :, 2] *= 255.0
        result_sobel_45[:, :, 2] = sie.conv2d(result_sobel_45[:, :, 2], sobel_45, strides=1, padding=1)
        result_sobel_45[:, :, 2] /= 255.0
        result_sobel_90 = img_hsv.copy()
        result_sobel_90[:, :, 2] *= 255.0
        result_sobel_90[:, :, 2] = sie.conv2d(result_sobel_90[:, :, 2], sobel_90, strides=1, padding=1)
        result_sobel_90[:, :, 2] /= 255.0
        result_sobel_135 = img_hsv.copy()
        result_sobel_135[:, :, 2] *= 255.0
        result_sobel_135[:, :, 2] = sie.conv2d(result_sobel_135[:, :, 2], sobel_135, strides=1, padding=1)
        result_sobel_135[:, :, 2] /= 255.0
        result_sobel = img_hsv.copy()
        result_sobel[:, :, 2] = (result_sobel_0[:, :, 2].astype(np.double) + result_sobel_45[:, :, 2].astype(np.double) + result_sobel_90[:, :, 2].astype(np.double) + result_sobel_135[:, :, 2].astype(np.double)) / 4

        # Transfer HSV to RGB
        result_sobel_0 = cst.hsv2rgb(result_sobel_0).astype(np.uint8)
        result_sobel_45 = cst.hsv2rgb(result_sobel_45).astype(np.uint8)
        result_sobel_90 = cst.hsv2rgb(result_sobel_90).astype(np.uint8)
        result_sobel_135 = cst.hsv2rgb(result_sobel_135).astype(np.uint8)
        result_sobel = cst.hsv2rgb(result_sobel).astype(np.uint8)

        # Transfer Back to BGR color space
        img = cv2.cvtColor(img, cv2.COLOR_RGB2BGR)
        result_sobel_0 = cv2.cvtColor(result_sobel_0, cv2.COLOR_RGB2BGR)
        result_sobel_45 = cv2.cvtColor(result_sobel_45, cv2.COLOR_RGB2BGR)
        result_sobel_90 = cv2.cvtColor(result_sobel_90, cv2.COLOR_RGB2BGR)
        result_sobel_135 = cv2.cvtColor(result_sobel_135, cv2.COLOR_RGB2BGR)
        result_sobel = cv2.cvtColor(result_sobel, cv2.COLOR_RGB2BGR)

        if is_show:
            cv2.imshow("origin", img)
            cv2.imshow("result of Sobel operator, degree = 0", result_sobel_0)
            cv2.imshow("result of Sobel operator, degree = 45", result_sobel_45)
            cv2.imshow("result of Sobel operator, degree = 90", result_sobel_90)
            cv2.imshow("result of Sobel operator, degree = 135", result_sobel_135)
            cv2.imshow("result of Sobel operator in all degree", result_sobel)
            print(f"{Bcolors.WARNING}Press any key to close the windows, {Bcolors.FAIL}DON'T CLOSE BY YOUR MOUSE{Bcolors.ENDC}", file=sys.stderr)
            cv2.waitKey(0)
            cv2.destroyAllWindows()
        if rewrite:
            cv2.imwrite(f"{save_folder}{filename}_sobel_0.jpg", result_sobel_0)
            cv2.imwrite(f"{save_folder}{filename}_sobel_45.jpg", result_sobel_45)
            cv2.imwrite(f"{save_folder}{filename}_sobel_90.jpg", result_sobel_90)
            cv2.imwrite(f"{save_folder}{filename}_sobel_135.jpg", result_sobel_135)
            cv2.imwrite(f"{save_folder}{filename}_sobel.jpg", result_sobel)

        # # ----- Convolution of Laplacain of a Gaussian (LoG) -----
        # result_LoG = img_hsv.copy()
        # result_LoG[:, :, 2] *= 255.0
        # result_LoG[:, :, 2] = sie.conv2d(result_LoG[:, :, 2], LoG, strides=1, padding=2)
        # result_LoG[:, :, 2] /= 255.0
        #
        # # Transfer HSV to RGB
        # result_LoG = cst.hsv2rgb(result_LoG).astype(np.uint8)
        #
        # # Transfer Back to BGR color space
        # result_LoG = cv2.cvtColor(result_LoG, cv2.COLOR_RGB2BGR)
        #
        # if is_show:
        #     cv2.imshow("origin", img)
        #     cv2.imshow("result of LoG", result_LoG)
        #     print(f"{Bcolors.WARNING}Press any key to close the windows, {Bcolors.FAIL}DON'T CLOSE BY YOUR MOUSE{Bcolors.ENDC}", file=sys.stderr)
        #     cv2.waitKey(0)
        #     cv2.destroyAllWindows()
        # if rewrite:
        #     cv2.imwrite(f"{save_folder}{filename}_LoG.jpg", result_LoG)
