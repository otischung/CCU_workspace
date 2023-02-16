function iter = expIter(x, min, max, step)
    iter = min + exp(1) ^ (log(max - min) * x / step);
end
