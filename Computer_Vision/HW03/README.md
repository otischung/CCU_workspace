Computer Vision Assignment 2 \- CSIE4B 408410120 鍾博丞

---

## Given the 2D-to-3D corresponding points, calculate the projection matrix

First, we create a zero matrix with size $2d \times 12$, where $d$ is the amount of data. We have $d=298$ in our dataset.

We have 298-pair $(x_i, y_i)$ and $(X_i, Y_i, Z_i)$. We also know that $x_i=P(X_i)$ and thus
$$
\begin{bmatrix}
	x_i \\ y_i \\ 1
\end{bmatrix}
=
\begin{bmatrix}
	P_{11} & P_{12} & P_{13}& P_{14} \\
	P_{21} & P_{22} & P_{23}& P_{24} \\
	P_{31} & P_{32} & P_{33}& P_{34} \\
\end{bmatrix}
\begin{bmatrix}
	X_i \\ Y_i \\ Z_i \\ 1
\end{bmatrix}
$$
We can rewrite this equation to
$$
\mathbf{AP} = \mathbf{0} \\
\begin{bmatrix}
	X_1 & Y_1 & Z_1 & 1 & 0 & 0 & 0 & 0 & -x_1X_1 & & -x_1Y_1 & -x_1Z_1 & -x_1 \\
	0 & 0 & 0 & 0 & X_1 & Y_1 & Z_1 & 1 & -x_1X_1 & & -x_1Y_1 & -x_1Z_1 & -x_1 \\
	...\\
	X_n & Y_n & Z_n & 1 & 0 & 0 & 0 & 0 & -x_nX_n & & -x_nY_n & -x_nZ_n & -x_n \\
	0 & 0 & 0 & 0 & X_n & Y_n & Z_n & 1 & -x_nX_n & & -x_nY_n & -x_nZ_n & -x_n \\
\end{bmatrix}
\begin{bmatrix}
	P_{11} \\ P_{12} \\ ... \\ P_{33} \\ P_{34}
\end{bmatrix}
= \mathbf{0}
$$


To solve the projection matrix $\mathbf{P}$ based on known matrix $\mathbf{A}$, our target is to minimize the distance between $\mathbf{AP}$ and $\mathbf{0}$.
$$
\min ||\mathbf{AP} - \mathbf{0}|| = \min \mathbf{P}^T\mathbf{A}^T\mathbf{AP}
$$
 Therefore, if we use the corresponding eigenvector with the minimum eigenvalue of $\mathbf{A}^T\mathbf{A}$, then we can minimize the objective function to $\lambda_{min}$.

We have the eigenvector $\mathbf{e_{min}} = \mathbf{P}$ and reshape it to the original form
$$
\begin{bmatrix}
	0.6265 & 0.0137 & -0.3748 & -0.0604 \\
   -2.2751e-4 & -0.6241 & -0.2715 & -0.0012 \\
   -4.8611e-8 & 3.0957e-5 & -9.3982e-4 & 1.5004e-5 \\
\end{bmatrix}
$$

## Based on the projection matrix, calculate the calibration matrix、rotation matrix, and translation matrix.

$$
\mathbf{P}_{3 \times 4} = \mathbf{K}_{3 \times 3} [\mathbf{R}_{3 \times 3} | \mathbf{T}_{3 \times 1}]
$$

where $\mathbf{K}$ is the upper triangular calibration matrix, $\mathbf{R}$ is the orthogonal rotation matrix, and $\mathbf{T}$ is the translation vector.

Let $\mathbf{M}_{3 \times 3} = \mathbf{KR}$, then $\mathbf{P}_{3 \times 3} \text{(the left-most part)}= \mathbf{M}_{3 \times 3}^{-1} = (\mathbf{KR})^{-1} = \mathbf{R}^{-1}\mathbf{K}^{-1}$.

Next, we perform QR-decomposition to $\mathbf{M}^{-1}$, then we have
$$
\mathbf{K} = 
\begin{bmatrix}
	-0.6265 & -0.0016 & -0.3750 \\
          0 &  0.6327 & -0.2508 \\
          0 &       0 & -9.4033e-4
\end{bmatrix}
$$
and 
$$
\mathbf{R} = 
\begin{bmatrix}
	-1.0000 &  3.3722e-4 & 6.2831e-5 \\
   	-3.3911e-4 & -0.9995 &  -0.0329 \\
     5.1696e-5 &  -0.0329 &  0.9995
\end{bmatrix}
$$
For translation vector $\mathbf{T}$, we have the right-most part of $\mathbf{P}_{3 \times 1}$ and $\mathbf{K}$ and hence $\mathbf{T} = \mathbf{K}^{-1} \mathbf{P}_{3 \times 1}$, we have
$$
\mathbf{T} = 
\begin{bmatrix}
	0.1060 \\ -0.0083 \\ -0.0160
\end{bmatrix}
$$

## Use the projection matrix to calculate the projected 2D points from 3D points. Calculate the average projection error

$$
\begin{align}
	\text{Error} &= \dfrac{1}{N} \sum_{i = 1}^{N} ||\mathbf{x}_{gt} - \mathbf{PX}_i|| \\
	&= \dfrac{1}{289} \sum_{i = 1}^{289} ||\mathbf{x}_{gt} - \mathbf{PX}_i|| \\
	&= 0.4271
\end{align}
$$

