import cv2
import glob
import numpy as np
import os
import shutil
import spatial_image_enhancement as sie
import sys
from bcolors import Bcolors

is_show = False
rewrite = False
save_eps = False
dpi = int(600)
src_folder = "./HW1_test_image/"
save_folder = "./Img/"
img_list = glob.glob(f"{src_folder}*.bmp")

if __name__ == "__main__":
    # Determine if rewrite results or not
    if os.path.isdir(save_folder):
        yn = input(
            f"{Bcolors.WARNING}The saving folder {save_folder} exists, do you want to remove it? [y/N]: {Bcolors.ENDC}")
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
        img = cv2.imread(i, cv2.IMREAD_GRAYSCALE)  # numpy.ndarray

        # Global Histogram Equalization
        result = sie.histogram_equalization(img)
        if is_show:
            cv2.imshow("origin", img)
            cv2.imshow("result of global histogram equalization", result)
            print(
                f"{Bcolors.WARNING}Press any key to close the windows, {Bcolors.FAIL}DON'T CLOSE BY YOUR MOUSE{Bcolors.ENDC}", file=sys.stderr)
            cv2.waitKey(0)
            cv2.destroyAllWindows()
        if rewrite:
            cv2.imwrite(f"{save_folder}{filename}_global_histeq.bmp", result)
        if is_show:
            sie.plot_histogram(img, title="origin")
            sie.plot_histogram(result, title="global histogram equalization")
        if rewrite:
            if save_eps:
                sie.save_histogram(result, filename=f"{save_folder}{filename}_global_histeq_hist.eps", is_eps=save_eps, title="global histogram equalization")
            else:
                sie.save_histogram(result, filename=f"{save_folder}{filename}_global_histeq_hist.png", is_eps=save_eps, title="global histogram equalization", dpi=dpi)

        # Local Histogram Equalization
        m = img.shape[0] // 4
        n = img.shape[1] // 4
        result = np.zeros(img.shape)
        for i in range(4):
            for j in range(4):
                row_start = m * i
                row_end = row_start + m if i < 3 else img.shape[0]
                col_start = n * j
                col_end = col_start + n if j < 3 else img.shape[1]
                result[row_start:row_end, col_start:col_end] = sie.histogram_equalization(img[row_start:row_end, col_start:col_end])
        if is_show:
            cv2.imshow("origin", img)
            cv2.imshow("result of local histogram equalization", result)
            print(
                f"{Bcolors.WARNING}Press any key to close the windows, {Bcolors.FAIL}DON'T CLOSE BY YOUR MOUSE{Bcolors.ENDC}", file=sys.stderr)
            cv2.waitKey(0)
            cv2.destroyAllWindows()
        if rewrite:
            cv2.imwrite(f"{save_folder}{filename}_local_histeq.bmp", result)
        if is_show:
            sie.plot_histogram(img, title="origin")
            sie.plot_histogram(result, title="local histogram equalization")
        if rewrite:
            if save_eps:
                sie.save_histogram(result, filename=f"{save_folder}{filename}_local_histeq_hist.eps", is_eps=save_eps, title="local histogram equalization")
            else:
                sie.save_histogram(result, filename=f"{save_folder}{filename}_local_histeq_hist.png", is_eps=save_eps, title="local histogram equalization", dpi=dpi)
