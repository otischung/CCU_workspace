function iter = mandelbrot(c, ITER)
    z = 0;
    iter = 0;
    while abs(z) <= 2 && iter < ITER
        z = z * z + c;
        iter = iter + 1;
    end
end
