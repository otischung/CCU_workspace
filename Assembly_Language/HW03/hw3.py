import numpy as np

a = np.asarray([[1, 2, 3, 4], [5, 6, 7, 8]])
b = np.asarray([[8, 7], [6, 5], [4, 3], [2, 1]])
c = np.matmul(a, b)
print(c)
