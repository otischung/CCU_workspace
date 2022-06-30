from params import *


def rand_samples(m, b, n_points, rand_paran):
    #  create empty list
    x_coors, y_coors, labels, = np.array([]), np.array([]), np.array([])
    c = 1 if m >= 0 else -1  # coef of r (right: positive; left: negative)

    # number of positive and negative samples
    pos_num = int(n_points / 2)
    neg_num = n_points - pos_num

    # randomly generate points
    for state, n_points in [["pos", pos_num], ["neg", neg_num]]:
        x = np.random.randint(0, rand_paran, n_points)
        r = np.random.randint(2, rand_paran, n_points)  # distance between points and line

        if state == "pos":
            y = m * x + b - (r * c)
            labels = np.append(labels, np.ones(n_points, dtype=int))
        else:
            y = m * x + b + (r * c)
            labels = np.append(labels, -1 * np.ones(n_points, dtype=int))

        x_coors = np.append(x_coors, x)
        y_coors = np.append(y_coors, y)
    return x_coors, y_coors, labels


np.random.seed(seed=int(time.time()))

# random generate points
x_coors, y_coors, labels = rand_samples(m, b, num_samples, rand_param)

with open(random_path, 'w') as fp:
    print(f"Saving results to {random_path}.")
    writer = csv.writer(fp)
    writer.writerow(['x', 'y', "sign (1: Right; -1: Left)"])

    for x, y in zip(list(x_coors[:pos_num]), list(y_coors[:pos_num])):
        writer.writerow([x, y, 1])
    for x, y in zip(list(x_coors[pos_num:]), list(y_coors[pos_num:])):
        writer.writerow([x, y, -1])
