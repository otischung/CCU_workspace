import math
import numpy as np
import sys
from tqdm import tqdm


def rgb2hsv(src: np.ndarray) -> np.ndarray:
    """
    Convert the RGB color space to HSV color space.

    Note that the input RGB values are [0, 255].
    The output hue is [0, 359].
    The output saturation is [0, 1].
    The output intensity value is [0, 1].

    Parameters
    ----------
    src: np.ndarray
        Input image.

    Returns
    -------
    out: np.ndarray
        The corresponding HSV image.

    Raises
    ------
    ValueError
        If the value of any channel of one or more pixels
        is greater than 255 or less than 0, then the error
        occurs.

    Notes
    -----
    Ref: https://www.geeksforgeeks.org/program-change-rgb-color-model-hsv-color-model/
    Ref: https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
    """
    print("Performing RGB to HSV.", file=sys.stderr)
    result = np.zeros(src.shape)
    r = src[:, :, 0] / 255.0
    g = src[:, :, 1] / 255.0
    b = src[:, :, 2] / 255.0

    for i in tqdm(range(src.shape[0])):
        for j in range(src.shape[1]):
            cmax = max(r[i, j], g[i, j], b[i, j])
            cmin = min(r[i, j], g[i, j], b[i, j])
            diff = cmax - cmin

            # Error handling
            if cmax > 255.0:
                raise ValueError(f"Error, index [{i}, {j}] has a value greater than 255.")
            if cmin < 0.0:
                raise ValueError(f"Error, index [{i}, {j}] has a value less than 0.")

            # Hue
            if cmax == cmin:
                result[i, j, 0] = 0
            elif cmax == r[i, j]:
                result[i, j, 0] = (60 * ((g[i, j] - b[i, j]) / diff) + 360) % 360
            elif cmax == g[i, j]:
                result[i, j, 0] = (60 * ((b[i, j] - r[i, j]) / diff) + 120) % 360
            else:  # cmax == b[i, j]
                result[i, j, 0] = (60 * ((r[i, j] - g[i, j]) / diff) + 240) % 360

            # Saturation
            if cmax == 0:
                result[i, j, 1] = 0
            else:
                result[i, j, 1] = diff / cmax

            # Value
            result[i, j, 2] = cmax

    return result


def hsv2rgb(src: np.ndarray) -> np.ndarray:
    """
    Convert the HSV color space to RGB color space.

    Note that the input hue is [0, 359].
    The input saturation is [0, 1].
    The input intensity value is [0, 1].
    The output RGB values are [0, 255] stored in double type.

    Parameters
    ----------
    src: np.ndarray
        Input HSV image.

    Returns
    -------
    out: np.ndarray
        The corresponding RGB image stored in double type.

    Raises
    ------
    ValueError
        If the input HSV image does not follow the spec. above,
        then the error is raised.

    Notes
    -----
    Ref: https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
    """
    print("Performing HSV to RGB.", file=sys.stderr)
    result = np.zeros(src.shape)
    h = src[:, :, 0]
    s = src[:, :, 1]
    v = src[:, :, 2]
    for i in tqdm(range(src.shape[0])):
        for j in range(src.shape[1]):
            # Error handling
            if h[i, j] < 0.0:
                raise ValueError(f"Error, the hue in index [{i}, {j}] is less than 0.")
            if s[i, j] < 0.0:
                raise ValueError(f"Error, the saturation in index [{i}, {j}] is less than 0.")
            if s[i, j] > 1.0:
                raise ValueError(f"Error, the saturation in index [{i}, {j}] is greater than 1.")
            if v[i, j] < 0.0:
                raise ValueError(f"Error, the intensity value in index [{i}, {j}] is less than 0.")
            if v[i, j] > 1.0:
                raise ValueError(f"Error, the intensity value in index [{i}, {j}] is greater than 1.")

            # If saturation is 0, then RGB = intensity
            if s[i, j] == 0.0:
                result[i, j, 0] = v[i, j]
                result[i, j, 1] = v[i, j]
                result[i, j, 2] = v[i, j]
                continue

            # hd is the abbreviation of hue divide
            hd = h[i, j] / 60.0  # [0, 6)
            # hdi is the abbreviation of hue-divide integer
            hdi = math.floor(hd)  # integer 0, 1, 2, 3, 4, 5
            # hdid is the abbreviation of hue-divide-integer difference
            hdid = hd - hdi  # [0, 1)

            p = v[i, j] * (1.0 - s[i, j])
            q = v[i, j] * (1.0 - (s[i, j] * hdid))
            t = v[i, j] * (1.0 - (s[i, j] * (1 - hdid)))

            if hdi == 0:
                result[i, j, 0] = v[i, j]
                result[i, j, 1] = t
                result[i, j, 2] = p
            elif hdi == 1:
                result[i, j, 0] = q
                result[i, j, 1] = v[i, j]
                result[i, j, 2] = p
            elif hdi == 2:
                result[i, j, 0] = p
                result[i, j, 1] = v[i, j]
                result[i, j, 2] = t
            elif hdi == 3:
                result[i, j, 0] = p
                result[i, j, 1] = q
                result[i, j, 2] = v[i, j]
            elif hdi == 4:
                result[i, j, 0] = t
                result[i, j, 1] = p
                result[i, j, 2] = v[i, j]
            else:  # hdi == 5
                result[i, j, 0] = v[i, j]
                result[i, j, 1] = p
                result[i, j, 2] = q

    result *= 255
    return result


def rgb2cie(src: np.ndarray) -> np.ndarray:
    """
    Convert the RGB color space to CIELAB D65 standard color space.

    Note that the input RGB values are [0, 255].
    The output Luminance is [0, 100].
    The output a, which is the location between green to magenta, is [-500, 500].
    The output b, which is the location between blue to yellow, is [-200, 200].

    Parameters
    ----------
    src: np.ndarray
        Input image.

    Returns
    -------
    out: np.ndarray
        The corresponding CIELAB D65 standard image.

    Raises
    ------
    ValueError
        If the value of any channel of one or more pixels
        is greater than 255 or less than 0, then the error
        occurs.

    Notes
    -----
    Ref: https://cg2010studio.com/2012/10/02/rgb%E8%88%87cielab%E8%89%B2%E5%BD%A9%E7%A9%BA%E9%96%93%E8%BD%89%E6%8F%9B/
    Ref: https://stackoverflow.com/questions/13405956/convert-an-image-rgb-lab-with-python
    """
    print("Performing RGB to CIELAB D65.", file=sys.stderr)
    xn = 0.9515
    yn = 1.0
    zn = 1.0886
    result = np.zeros(src.shape)
    r = src[:, :, 0] / 255.0
    g = src[:, :, 1] / 255.0
    b = src[:, :, 2] / 255.0
    M = np.array([[0.412453, 0.357580, 0.180423],
                  [0.212671, 0.715160, 0.072169],
                  [0.019334, 0.119193, 0.950227]])
    xyz = np.matmul(M, np.append(r.reshape((1, r.shape[0] * r.shape[1])),
                                 [g.reshape((1, g.shape[0] * g.shape[1]))[0],
                                  b.reshape((1, b.shape[0] * b.shape[1]))[0]], axis=0))
    x = xyz[0, :].reshape((src.shape[0], src.shape[1]))
    y = xyz[1, :].reshape((src.shape[0], src.shape[1]))
    z = xyz[2, :].reshape((src.shape[0], src.shape[1]))
    for i in tqdm(range(src.shape[0])):
        for j in range(src.shape[1]):
            # L
            if y[i, j] / yn > 0.008856:
                result[i, j, 0] = 116 * ((y[i, j] / yn) ** (1 / 3)) - 16
            else:
                result[i, j, 0] = 903.3 * (y[i, j] / yn)

            # a
            result[i, j, 1] = 500 * (_ciefunc(x[i, j] / xn) - _ciefunc(y[i, j] / yn))

            # b
            result[i, j, 2] = 200 * (_ciefunc(y[i, j] / yn) - _ciefunc(z[i, j] / zn))

    return result


def _ciefunc(x: float) -> float:
    return x ** (1 / 3) if x > 0.008856 else 7.787 * x + (16 / 116)


def cie2rgb(src: np.ndarray) -> np.ndarray:
    """
    Convert the CIELAB D65 standard color space to the RGB color space.

    Note that the output RGB values are [0, 255].
    The input Luminance is [0, 100].
    The input a, which is the location between green to magenta, is [-500, 500].
    The input b, which is the location between blue to yellow, is [-200, 200].

    Parameters
    ----------
    src: np.ndarray
        Input CIELAB D65 standard image.

    Returns
    -------
    out: np.ndarray
        The corresponding RGB image.

    Raises
    ------
    ValueError
        If the value of any channel of one or more pixels
        is does not follow the spec., then the error
        occurs.

    Notes
    -----
    Ref: https://cg2010studio.com/2012/10/02/rgb%E8%88%87cielab%E8%89%B2%E5%BD%A9%E7%A9%BA%E9%96%93%E8%BD%89%E6%8F%9B/
    Ref: https://stackoverflow.com/questions/13405956/convert-an-image-rgb-lab-with-python
    """
    print("Performing CIELAB D65 to RGB.", file=sys.stderr)
    xn = 0.9515
    yn = 1.0
    zn = 1.0886
    result = np.zeros(src.shape)
    M = np.array([[3.240479, -1.537150, -0.498535],
                  [-0.969256, 1.875992, 0.041556],
                  [0.055648, -0.204043, 1.057311]])
    x = np.zeros((src.shape[0], src.shape[1]))
    y = np.zeros((src.shape[0], src.shape[1]))
    z = np.zeros((src.shape[0], src.shape[1]))
    for i in tqdm(range(src.shape[0])):
        for j in range(src.shape[1]):
            fy = (src[i, j, 0] + 16) / 116
            fx = fy + src[i, j, 1] / 500
            fz = fy - src[i, j, 2] / 200

            y[i, j] = yn * (fy ** 3) if fy > 0.008856 else (fy - 16) / 116 * 3 * (0.008856 ** 2) * yn
            x[i, j] = xn * (fx ** 3) if fx > 0.008856 else (fx - 16) / 116 * 3 * (0.008856 ** 2) * xn
            z[i, j] = zn * (fz ** 3) if fz > 0.008856 else (fz - 16) / 116 * 3 * (0.008856 ** 2) * zn

    rgb = np.matmul(M, np.append(x.reshape((1, x.shape[0] * x.shape[1])),
                                 [y.reshape((1, y.shape[0] * y.shape[1]))[0],
                                  z.reshape((1, z.shape[0] * z.shape[1]))[0]], axis=0))
    result[:, :, 0] = rgb[0, :].reshape((src.shape[0], src.shape[1]))
    result[:, :, 1] = rgb[1, :].reshape((src.shape[0], src.shape[1]))
    result[:, :, 2] = rgb[2, :].reshape((src.shape[0], src.shape[1]))
    result *= 255.0
    return result
