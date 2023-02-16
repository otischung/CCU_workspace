import math

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
# For Ideal Low Pass Filter and Ideal High Pass Filter
# This value determine the ratio of min(height / 2, width / 2)
# This value must not greater than 1
radius_ratio = 0.8
# The value "A" for high-boost filter.
# This value must greater than 1
high_boost_A = 3
src_folder = "./HW2_test_image/"
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

    img = cv2.imread(i, cv2.IMREAD_GRAYSCALE)  # numpy.ndarray
    img_double = img.astype(np.double)
    # Image size
    M = img.shape[0]
    N = img.shape[1]

    # DFT
    img_dft = fie.dft2d(img_double)
    img_dft_shift = fie.fftshift(img_dft)
    img_magnitude_spectrum = fie.calspec(img_dft_shift)
    if rewrite:
        cv2.imwrite(f"{save_folder}{filename}.bmp", img)
        cv2.imwrite(f"{save_folder}{filename}_magnitude_spectrum.bmp", img_magnitude_spectrum)

    # ----- Laplacian Operator -----
    print(f"{Bcolors.OKBLUE}Laplacian Operator{Bcolors.ENDC}", file=sys.stderr)
    laplacian = np.zeros(img.shape)
    for u in range(M):
        for v in range(N):
            # laplacian[u][v] = -4 * (np.pi ** 2) * ((u - M // 2) ** 2 + (v - N // 2) ** 2)
            laplacian[u][v] = -1 * ((u - M // 2) ** 2 + (v - N // 2) ** 2)

    # Apply Laplacian Operator
    lap_freq_result = img_dft_shift * laplacian
    lap_result_magnitude_spectrum = fie.calspec(lap_freq_result)

    # inv DFT
    lap_result = fie.ifftshift(lap_freq_result)
    lap_result = fie.idft2d(lap_result)
    lap_result = np.abs(lap_result)
    lap_result = lap_result / lap_result.max()  # Normalize to [0, 1]
    lap_result = lap_result * 255  # Transfer back to [0, 255]
    lap_result = lap_result.astype(np.uint8)

    if is_show:
        cv2.imshow("Input Image", img)
        cv2.imshow("Magnitude Spectrum of Input", img_magnitude_spectrum)
        cv2.imshow("Laplacian Operator", lap_result)
        cv2.imshow("Magnitude Spectrum of the Result of Laplacian Operator", lap_result_magnitude_spectrum)
        print(f"{Bcolors.WARNING}Press any key to close the windows, {Bcolors.FAIL}DON'T CLOSE BY YOUR MOUSE{Bcolors.ENDC}", file=sys.stderr)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
    if rewrite:
        cv2.imwrite(f"{save_folder}{filename}_laplacian.bmp", lap_result)
        cv2.imwrite(f"{save_folder}{filename}_laplacian_magnitude_spectrum.bmp", lap_result_magnitude_spectrum)

    # ----- Ideal Low Pass Filter ILPF -----
    print(f"{Bcolors.OKBLUE}Unsharp Mask{Bcolors.ENDC}", file=sys.stderr)
    ilpf = np.zeros(img.shape)
    radius = (M / 2) * radius_ratio if M <= N else (N / 2) * radius_ratio
    for u in range(M):
        for v in range(N):
            ilpf[u][v] = 0 if math.dist([u, v], [M / 2, N / 2]) > radius else 1

    # Apply ILPF
    lp_freq_result = img_dft_shift * ilpf
    lp_result_magnitude_spectrum = fie.calspec(lp_freq_result)

    # inv DFT
    lp_result = fie.ifftshift(lp_freq_result)
    lp_result = fie.idft2d(lp_result)
    lp_result = np.abs(lp_result)
    lp_result = lp_result / lp_result.max()  # Normalize to [0, 1]
    lp_result = lp_result * 255  # Transfer back to [0, 255]
    lp_result = lp_result.astype(np.uint8)

    # ----- Unsharp Mask -----
    unsharp = 2 * img_double - lp_result
    unsharp = unsharp / unsharp.max()
    unsharp = unsharp * 255
    unsharp = unsharp.astype(np.uint8)
    unsharp_dft = fie.dft2d(unsharp)
    unsharp_dft_shift = fie.fftshift(unsharp_dft)
    unsharp_magnitude_spectrum = fie.calspec(unsharp_dft_shift)

    if is_show:
        cv2.imshow("Input Image", img)
        cv2.imshow("Magnitude Spectrum of Input", img_magnitude_spectrum)
        cv2.imshow("Ideal Low Pass Filter", lp_result)
        cv2.imshow("Magnitude Spectrum of the Result of ILPF", lp_result_magnitude_spectrum)
        cv2.imshow("Unsharp Masking", unsharp)
        cv2.imshow("Magnitude Spectrum of the Result of Unsharp Masking", unsharp_magnitude_spectrum)
        print(f"{Bcolors.WARNING}Press any key to close the windows, {Bcolors.FAIL}DON'T CLOSE BY YOUR MOUSE{Bcolors.ENDC}", file=sys.stderr)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
    if rewrite:
        cv2.imwrite(f"{save_folder}{filename}_ILPF_r_{radius_ratio}.bmp", lp_result)
        cv2.imwrite(f"{save_folder}{filename}_ILPF_r_{radius_ratio}_magnitude_spectrum.bmp", lp_result_magnitude_spectrum)
        cv2.imwrite(f"{save_folder}{filename}_unsharp.bmp", unsharp)
        cv2.imwrite(f"{save_folder}{filename}_unsharp_magnitude_spectrum.bmp", unsharp_magnitude_spectrum)

    # ----- Ideal High Pass Filter IHPF -----
    print(f"{Bcolors.OKBLUE}High-Boost Filter{Bcolors.ENDC}", file=sys.stderr)
    ihpf = 1 - ilpf

    # ----- High-Boost Filter -----
    high_boost = (high_boost_A - 1) + ihpf

    # Apply High-Boost Filter
    hb_freq_result = img_dft_shift * high_boost
    hb_result_magnitude_spectrum = fie.calspec(hb_freq_result)

    # inv DFT
    hb_result = fie.ifftshift(hb_freq_result)
    hb_result = fie.idft2d(hb_result)
    hb_result = np.abs(hb_result)
    hb_result = hb_result / hb_result.max()  # Normalize to [0, 1]
    hb_result = hb_result * 255  # Transfer back to [0, 255]
    hb_result = hb_result.astype(np.uint8)

    if is_show:
        cv2.imshow("Input Image", img)
        cv2.imshow("Magnitude Spectrum of Input", img_magnitude_spectrum)
        cv2.imshow("High-Boost Filter", hb_result)
        cv2.imshow("Magnitude Spectrum of the Result of High-Boost Filter", hb_result_magnitude_spectrum)
        print(f"{Bcolors.WARNING}Press any key to close the windows, {Bcolors.FAIL}DON'T CLOSE BY YOUR MOUSE{Bcolors.ENDC}", file=sys.stderr)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
    if rewrite:
        cv2.imwrite(f"{save_folder}{filename}_High_Boost_A_{high_boost_A}.bmp", hb_result)
        cv2.imwrite(f"{save_folder}{filename}_High_Boost_A_{high_boost_A}_magnitude_spectrum.bmp", hb_result_magnitude_spectrum)
