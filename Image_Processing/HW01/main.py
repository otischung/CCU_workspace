import cv2
import glob
import numpy as np
import os
import shutil
import spatial_image_enhancement as sie
import sys
from bcolors import Bcolors

is_show = False
save_eps = False
dpi = int(600)
src_folder = "./HW1_test_image/"
save_folder = "./Img/"
img_list = glob.glob(f"{src_folder}*.bmp")
laplacian = np.array([[0, -1, 0],
                      [-1, 5, -1],
                      [0, -1, 0]]).astype(np.uint8)
if os.path.isdir(save_folder):
    shutil.rmtree(save_folder)
os.mkdir(save_folder)

for i in img_list:
    print(f"Reading file: {i}")
    filename = ((i.split("/")[-1]).split("\\")[-1]).split(".")[0]  # For windows and Linux.
    img = cv2.imread(i, cv2.IMREAD_GRAYSCALE)  # numpy.ndarray

    # Gamma Correction
    result = sie.gamma_correction(img, c=1.0, gamma=0.5)
    result_2 = sie.gamma_correction(img, c=1.0, gamma=2)
    if is_show:
        cv2.imshow("origin", img)
        cv2.imshow("result of gamma transformation, gamma = 0.5", result)
        cv2.imshow("result of gamma transformation, gamma = 2", result_2)
        print(f"{Bcolors.WARNING}Press any key to close the windows, {Bcolors.FAIL}DON'T CLOSE BY YOUR MOUSE{Bcolors.ENDC}", file=sys.stderr)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
    cv2.imwrite(f"{save_folder}{filename}_gamma_0.5.bmp", result)
    cv2.imwrite(f"{save_folder}{filename}_gamma_2.bmp", result_2)
    if is_show:
        sie.plot_histogram(img, title="origin")
        sie.plot_histogram(result, title="gamma transformation, gamma = 0.5")
        sie.plot_histogram(result_2, title="gamma transformation, gamma = 2")
    if save_eps:
        sie.save_histogram(img, filename=f"{save_folder}{filename}_hist.eps", is_eps=save_eps, title="origin")
        sie.save_histogram(result, filename=f"{save_folder}{filename}_gamma_0.5_hist.eps", is_eps=save_eps, title="gamma transformation, gamma = 0.5")
        sie.save_histogram(result_2, filename=f"{save_folder}{filename}_gamma_2_hist.eps", is_eps=save_eps, title="gamma transformation, gamma = 2")
    else:
        sie.save_histogram(img, filename=f"{save_folder}{filename}_hist.png", is_eps=save_eps, title="origin", dpi=dpi)
        sie.save_histogram(result, filename=f"{save_folder}{filename}_gamma_0.5_hist.png", is_eps=save_eps, title="gamma transformation, gamma = 0.5", dpi=dpi)
        sie.save_histogram(result_2, filename=f"{save_folder}{filename}_gamma_2_hist.png", is_eps=save_eps, title="gamma transformation, gamma = 2", dpi=dpi)

    # Histogram Equalization
    result = sie.histogram_equalization(img)
    if is_show:
        cv2.imshow("origin", img)
        cv2.imshow("result of histogram equalization", result)
        print(f"{Bcolors.WARNING}Press any key to close the windows, {Bcolors.FAIL}DON'T CLOSE BY YOUR MOUSE{Bcolors.ENDC}", file=sys.stderr)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
    cv2.imwrite(f"{save_folder}{filename}_histeq.bmp", result)
    if is_show:
        sie.plot_histogram(img, title="origin")
        sie.plot_histogram(result, title="histogram equalization")
    if save_eps:
        sie.save_histogram(result, filename=f"{save_folder}{filename}_histeq_hist.eps", is_eps=save_eps, title="histogram equalization")
    else:
        sie.save_histogram(result, filename=f"{save_folder}{filename}_histeq_hist.png", is_eps=save_eps, title="histogram equalization", dpi=dpi)

    # Convolution of Laplacian Operator
    result = sie.conv2d(img, laplacian, strides=1, padding=1)
    if is_show:
        cv2.imshow("origin", img)
        cv2.imshow("result of Laplacian operator", result)
        print(f"{Bcolors.WARNING}Press any key to close the windows, {Bcolors.FAIL}DON'T CLOSE BY YOUR MOUSE{Bcolors.ENDC}", file=sys.stderr)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
    cv2.imwrite(f"{save_folder}{filename}_laplacian.bmp", result)
    if is_show:
        sie.plot_histogram(img, title="origin")
        sie.plot_histogram(result, title="Laplacian operator")
    if save_eps:
        sie.save_histogram(result, filename=f"{save_folder}{filename}_laplacian_hist.eps", is_eps=save_eps, title="Laplacian operator")
    else:
        sie.save_histogram(result, filename=f"{save_folder}{filename}_laplacian_hist.png", is_eps=save_eps, title="Laplacian operator", dpi=dpi)
