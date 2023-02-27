import math
import numpy as np


# # ---------- I wrote it, it doesn't work ----------
# def omega(x, m) -> complex:
#     return np.exp(2j * np.pi * x / m)
#
#
# def zeropadding(arr: np.ndarray) -> np.ndarray:
#     m = math.ceil(math.log(arr.shape[0], 2))
#     return np.concatenate((arr, [0] * (2 ** m - arr.shape[0]))).astype(np.complex)
#
#
# def unpadding(arr: np.ndarray, m) -> np.ndarray:
#     return arr[0:m]
#
#
# def fft(a: np.ndarray):
#     n = a.shape[0]
#     if n == 1:  # recursive terminate
#         return a
#     even = fft(a[0::2])
#     odd = fft(a[1::2])
#     combine = np.zeros(n).astype(np.complex)
#     print(combine)
#     for i in range(n // 2):
#         print(combine[i])
#         combine[i] = even[i].astype(np.complex) + omega(-i, n) * odd[i].astype(np.complex)
#         combine[i + n / 2] = even[i].astype(np.complex) - omega(-i, n) * odd[i].astype(np.complex)
#     return combine
#
#
# def ifft(a: np.ndarray) -> np.ndarray:
#     return fft(np.array([u.conjugate() for u in a]))
#
#
# def zeropadding2(arr: np.ndarray) -> np.ndarray:
#     m = 2 ** (math.ceil(math.log(arr.shape[0], 2)))
#     n = 2 ** (math.ceil(math.log(arr.shape[1], 2)))
#     pad = np.zeros((m, n))
#     pad[0:arr.shape[0], 0:arr.shape[1]] = arr
#     return pad
#
#
# def unpadding2(arr: np.ndarray, m, n) -> np.ndarray:
#     return arr[0:m][0:n]
#
#
# def fft2(a: np.ndarray) -> np.ndarray:
#     F = zeropadding2(a)
#     return np.transpose(fft(np.transpose(fft(F))))
#
#
# def ifft2(a: np.ndarray, m=None, n=None) -> np.ndarray:
#     f = fft2(np.conjugate(a))
#     return f[0:m][0:n] if m is not None and n is not None else f


# # ---------- Paste from github, it doesn't work perfectly ----------
# # Ref: https://gist.github.com/bistaumanga/5682774
# def omega(p, q):
#     ''' The omega term in DFT and IDFT formulas'''
#     return np.exp((2.0 * np.pi * 1j * q) / p)
#
#
# def pad(lst):
#     '''padding the list to next nearest power of 2 as FFT implemented is radix 2'''
#     k = 0
#     while 2 ** k < len(lst):
#         k += 1
#     return np.concatenate((lst, ([0] * (2 ** k - len(lst)))))
#
#
# def fft(x):
#     ''' FFT of 1-d signals
#     usage : X = fft(x)
#     where input x = list containing sequences of a discrete time signals
#     and output X = dft of x '''
#
#     n = len(x)
#     if n == 1:
#         return x
#     Feven, Fodd = fft(x[0::2]), fft(x[1::2])
#     combined = [0] * n
#     for m in range(n // 2):
#         combined[m] = Feven[m] + omega(n, -m) * Fodd[m]
#         combined[m + n // 2] = Feven[m] - omega(n, -m) * Fodd[m]
#     return combined
#
#
# def ifft(X):
#     ''' IFFT of 1-d signals
#     usage x = ifft(X)
#     unpadding must be done implicitly'''
#
#     x = fft([x.conjugate() for x in X])
#     return [x.conjugate() / len(X) for x in x]
#
#
# def pad2(x):
#     m, n = np.shape(x)
#     M, N = 2 ** int(math.ceil(math.log(m, 2))), 2 ** int(math.ceil(math.log(n, 2)))
#     F = np.zeros((M, N), dtype=x.dtype)
#     F[0:m, 0:n] = x
#     return F, m, n
#
#
# def fft2(f):
#     '''FFT of 2-d signals/images with padding
#     usage X, m, n = fft2(x), where m and n are dimensions of original signal'''
#
#     f, m, n = pad2(f)
#     return np.transpose(fft(np.transpose(fft(f)))), m, n
#
#
# def ifft2(F, m, n):
#     ''' IFFT of 2-d signals
#     usage x = ifft2(X, m, n) with unpaded,
#     where m and n are odimensions of original signal before padding'''
#
#     f, M, N = fft2(np.conj(F))
#     f = np.matrix(np.real(np.conj(f))) / (M * N)
#     return f[0:m, 0:n]


def dft2d(a: np.ndarray, s=None, axes=(-2, -1), norm=None) -> np.ndarray:
    return np.fft.fft2(a, s=s, axes=axes, norm=norm)


def idft2d(a: np.ndarray, s=None, axes=(-2, -1), norm=None) -> np.ndarray:
    return np.fft.ifft2(a, s=s, axes=axes, norm=norm)


def fftshift(x: np.ndarray, axes: int | tuple = None) -> np.ndarray:
    # np.fft.fftshift(x, axes=axes)
    dim = x.ndim
    is_tuple = True if type(axes) == tuple else False
    result = x.copy()
    for i in range(dim):
        if axes is not None:
            if is_tuple:
                if i not in axes:
                    continue
            else:
                if i != axes:
                    continue
        center = math.ceil(x.shape[i] / 2)
        tail = result.take(np.arange(center, x.shape[i]), axis=i)
        front = result.take(np.arange(0, center), axis=i)
        result = np.concatenate((tail, front), axis=i)
    return result


def ifftshift(x: np.ndarray, axes: int | tuple = None) -> np.ndarray:
    # np.fft.ifftshift(x, axes=axes)
    dim = x.ndim
    is_tuple = True if type(axes) == tuple else False
    result = x.copy()
    for i in range(dim):
        if axes is not None:
            if is_tuple:
                if i not in axes:
                    continue
            else:
                if i != axes:
                    continue
        center = math.floor(x.shape[i] / 2)
        tail = result.take(np.arange(center, x.shape[i]), axis=i)
        front = result.take(np.arange(0, center), axis=i)
        result = np.concatenate((tail, front), axis=i)
    return result


def calspec(img_freq: np.ndarray) -> np.ndarray:
    # Calculate Magnitude Spectrum
    spectrum = np.abs(img_freq)
    spectrum = np.log(spectrum + 1)  # To prevent log(0) = -NaN
    spectrum = spectrum / spectrum.max()  # Normalize to [0, 1]
    spectrum = 255 * spectrum  # Transfer back to [0, 255]
    spectrum = spectrum.astype(np.uint8)
    return spectrum
