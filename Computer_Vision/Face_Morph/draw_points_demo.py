import cv2
import numpy as np
import sys

from bcolors import Bcolors


def demo(img: np.ndarray, points: list):
    for point in points:
        cv2.circle(img, point, 5, (0, 255, 0), -1)
    cv2.imshow("test", img)
    print(f"{Bcolors.WARNING}Press any key to close the windows, {Bcolors.FAIL}DON'T CLOSE BY YOUR MOUSE{Bcolors.ENDC}", file=sys.stderr)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
