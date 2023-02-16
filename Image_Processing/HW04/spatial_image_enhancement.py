import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import sys
from bcolors import Bcolors
from tqdm import tqdm


def plot_histogram(img: np.ndarray, title: str = ""):
    # Linux works perfect with GTK but struggle with Qt.
    # Windows works perfect with Qt instead.
    try:
        matplotlib.use("GTK4Agg")
    except ImportError:
        pass
    img = img.astype(np.uint8)
    img_flatten = img.flatten()
    plt.hist(img_flatten, bins=256)
    plt.title(title)
    print(f"{Bcolors.WARNING}Use mouse click to close the histogram windows.{Bcolors.ENDC}", file=sys.stderr)
    plt.show()


def save_histogram(img: np.ndarray, filename: str, is_eps: bool, title: str = "", dpi: int = 600):
    # Linux works perfect with GTK but struggle with Qt.
    # Windows works perfect with Qt instead.
    try:
        matplotlib.use("GTK4Agg")
    except ImportError:
        pass
    img = img.astype(np.uint8)
    img_flatten = img.flatten()
    plt.hist(img_flatten, bins=256)
    plt.title(title)
    if is_eps:
        plt.savefig(filename)
    else:
        plt.savefig(filename, dpi=dpi)
    plt.close()


def gamma_correction(origin: np.ndarray, c: float = 1.0, gamma: float = 1.0) -> np.ndarray:
    # https://geek-docs.com/opencv/opencv-examples/gamma-correction.html
    result = origin.copy()
    result = result.astype(np.longdouble)

    # Normalize to [0, 1]
    result /= 255.0

    # Apply Gamma Correction
    result = c * (result ** gamma)

    # Transfer back to [0, 255]
    result *= 255
    result = result.astype(np.uint8)
    return result


def histogram_equalization(origin: np.ndarray) -> np.ndarray:
    # https://levelup.gitconnected.com/introduction-to-histogram-equalization-for-digital-image-enhancement-420696db9e43
    origin = origin.astype(np.uint8)
    img_flatten = origin.flatten()

    # Create Histogram
    hist = np.bincount(img_flatten, minlength=256)

    # Normalize to [0, 1]
    num_pixel = np.sum(hist)
    norm_hist = hist / num_pixel

    # Normalization CDF
    cum_hist = np.cumsum(norm_hist)

    # Translation Lookup Table
    table = np.floor(255 * cum_hist).astype(np.uint8)

    # Save result
    result = np.array([]).astype(np.uint8)
    for i in img_flatten:
        result = np.append(result, table[i])
    result = np.reshape(result, origin.shape)
    return result


def conv2d(img: np.ndarray, kernel: np.ndarray, strides: int = 1, padding: int = 0) -> np.ndarray:
    # cv2.filter2D(img, -1, kernel)
    # https://medium.com/analytics-vidhya/2d-convolution-using-python-numpy-43442ff5f381
    # Apply cross correlation to the kernel by flipping the matrix horizontally then vertically.
    kernel = np.flipud(np.fliplr(kernel))

    # Shape of Output Convolution
    x_size = int(((img.shape[0] - kernel.shape[0] + 2 * padding) / strides) + 1)
    y_size = int(((img.shape[1] - kernel.shape[1] + 2 * padding) / strides) + 1)
    output = np.zeros((x_size, y_size), dtype=np.double)  # Tuple of int

    # Apply Equal Padding to All Sides
    if padding != 0:
        ''' Example for padding = 1
        0 0 0 0 0 0 0 0
        0 I I I I I I 0
        0 I I I I I I 0
        0 I I I I I I 0
        0 I I I I I I 0
        0 I I I I I I 0
        0 I I I I I I 0
        0 0 0 0 0 0 0 0
        '''
        img_pad = np.zeros((img.shape[0] + padding * 2, img.shape[1] + padding * 2), dtype=np.double)
        img_pad[int(padding):int(-1 * padding), int(padding):int(-1 * padding)] = img
    else:
        img_pad = img.astype(np.double)

    # Iterate through image
    ''' Let A be (x, y)
    A - + 0 0 0 0 0
    | x | I I I I 0
    + - + I I I I 0
    0 I I I I I I 0
    0 I I I I I I 0
    0 I I I I I I 0
    0 I I I I I I 0
    0 0 0 0 0 0 0 0
    '''
    for y in tqdm(range(img.shape[1] - kernel.shape[1])):
        if y % strides == 0:
            for x in range(img.shape[0] - kernel.shape[0]):
                try:
                    # Only Convolve if A(x, y) has moved by the specified Strides
                    if x % strides == 0:
                        output[x, y] = (kernel * img_pad[x: x + kernel.shape[0], y: y + kernel.shape[1]]).sum()
                        if output[x, y] < 0.0:
                            output[x, y] = 0.0
                        elif output[x, y] > 255.0:
                            output[x, y] = 255.0
                except IndexError:
                    break
    output = output.astype(np.uint8)
    return output
