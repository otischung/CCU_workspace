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

# ----- hyper parameters ------
is_show = True
# Gamma value
gamma = {
    "aloe": 0.4,
    "church": 0.4,
    "house": 2.5,
    "kitchen": 2.0
}
src_folder = "./HW3_test_image/"
save_folder = "./Img/"
# ----- hyper parameters ------

rewrite = False
img_list = glob.glob(f"{src_folder}*")

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

for i in img_list:
    path = os.path.abspath(i)
    filename = os.path.basename(path)
    print(f"\n----- Reading file: {filename} -----", file=sys.stderr)
    filename = os.path.splitext(filename)[0]

    # Read Image to numpy array
    img = cv2.imread(path, cv2.IMREAD_COLOR)  # numpy.ndarray  # BGR image

    # Transfer to RGB color space
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)  # RGB image

    # Transfer RGB to HSV
    img_hsv = cst.rgb2hsv(img.astype(np.double))
    img_hsv_gamma = img_hsv.copy()
    img_hsv_histeq = img_hsv.copy()

    # Gamma Transformation
    img_hsv_gamma[:, :, 2] = sie.gamma_correction(img_hsv_gamma[:, :, 2], c=1.0, gamma=gamma[filename])
    # Transfer HSV to RGB
    img_hsv_gamma_back = cst.hsv2rgb(img_hsv_gamma).astype(np.uint8)

    # Histogram Equalization
    img_hsv_histeq[:, :, 2] *= 255
    img_hsv_histeq[:, :, 2] = sie.histogram_equalization(img_hsv_histeq[:, :, 2])
    img_hsv_histeq[:, :, 2] /= 255
    # Transfer HSV to RGB
    img_hsv_histeq_back = cst.hsv2rgb(img_hsv_histeq).astype(np.uint8)

    # Transfer RGB to CIELAB
    img_cie = cst.rgb2cie(img.astype(np.double))
    img_cie_gamma = img_cie.copy()
    img_cie_histeq = img_cie.copy()

    # Gamma Transformation
    img_cie_gamma[:, :, 0] /= 100.0
    img_cie_gamma[:, :, 0] = sie.gamma_correction(img_cie_gamma[:, :, 0], c=1.0, gamma=gamma[filename])
    img_cie_gamma[:, :, 0] *= 100.0
    # Transfer CIELAB to RGB
    img_cie_gamma_back = cst.cie2rgb(img_cie_gamma).astype(np.uint8)

    # Histogram Equalization
    img_cie_histeq[:, :, 0] /= 100.0
    img_cie_histeq[:, :, 0] *= 255.0
    img_cie_histeq[:, :, 0] = sie.histogram_equalization(img_cie_histeq[:, :, 0])
    img_cie_histeq[:, :, 0] /= 255.0
    img_cie_histeq[:, :, 0] *= 100.0
    # Transfer CIELAB to RGB
    img_cie_histeq_back = cst.cie2rgb(img_cie_histeq).astype(np.uint8)

    # Transfer Back to BGR color space
    img = cv2.cvtColor(img, cv2.COLOR_RGB2BGR)  # BGR image
    img_hsv_gamma_back = cv2.cvtColor(img_hsv_gamma_back, cv2.COLOR_RGB2BGR)  # BGR image
    img_hsv_histeq_back = cv2.cvtColor(img_hsv_histeq_back, cv2.COLOR_RGB2BGR)  # BGR image
    img_cie_gamma_back = cv2.cvtColor(img_cie_gamma_back, cv2.COLOR_RGB2BGR)  # BGR image
    img_cie_histeq_back = cv2.cvtColor(img_cie_histeq_back, cv2.COLOR_RGB2BGR)  # BGR image

    if is_show:
        cv2.imshow("Input Image", img)
        cv2.imshow(f"Gamma Transformation gamma = {gamma[filename]} in HSV", img_hsv_gamma_back)
        cv2.imshow(f"Histogram Equalization in HSV", img_hsv_histeq_back)
        cv2.imshow(f"Gamma Transformation gamma = {gamma[filename]} in CIE", img_cie_gamma_back)
        cv2.imshow(f"Histogram Equalization in CIE", img_cie_histeq_back)
        print(f"{Bcolors.WARNING}Press any key to close the windows, {Bcolors.FAIL}DON'T CLOSE BY YOUR MOUSE{Bcolors.ENDC}", file=sys.stderr)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
    if rewrite:
        cv2.imwrite(f"{save_folder}{filename}_hsv_gamma_{gamma[filename]}.jpg", img_hsv_gamma_back)
        cv2.imwrite(f"{save_folder}{filename}_hsv_histeq.jpg", img_hsv_histeq_back)
        cv2.imwrite(f"{save_folder}{filename}_cie_gamma_{gamma[filename]}.jpg", img_cie_gamma_back)
        cv2.imwrite(f"{save_folder}{filename}_cie_histeq.jpg", img_cie_histeq_back)
