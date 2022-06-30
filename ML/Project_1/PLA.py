from params import *


def read_to_2d_array(dataset: np.ndarray, csv_path: str) -> np.ndarray:
    with open(csv_path, "r") as fp:
        first = False
        reader = csv.reader(fp)
        for row in reader:
            if not first:
                first = True
                continue
            for i in range(len(row)):
                row[i] = int(float(row[i]))
            arr = np.array(row)
            arr = np.reshape(arr, (-1, 3))
            dataset = np.append(dataset, arr, axis=0)
    dataset = dataset.astype(int)
    return dataset


def check_error(weight: np.ndarray, dataset: np.ndarray) -> np.ndarray or int:
    result = np.array([[]])
    result = np.reshape(result, (-1, 3))
    error = 0

    for data in dataset:
        x = np.array([1, data[0], data[1]])
        sign = data[2]
        if int(np.sign(weight.T.dot(x)) != sign):
            r = np.reshape(data, (-1, 3))
            result = np.append(result, r, axis=0)
            error += 1
    result = result.astype(int)
    # print(result)
    # print(f"error: {error}/{len(dataset)}")
    return result, error


def PLA(dataset: np.ndarray) -> np.ndarray or int:
    weight = np.zeros(3)
    iteration = 0
    try:
        while iteration < early_stop:
            iteration += 1
            result, error = check_error(weight, data)
            print(f"Training iteration: {iteration}, error: {error}/{len(dataset)}", file=sys.stderr)
            if len(result) == 0:
                break
            x = np.array([1, result[0][0], result[0][1]])
            sign = np.array([result[0][2]])
            weight += sign * x
        if iteration == early_stop:
            print(f"Early stop! Iteration {iteration} times.", file=sys.stderr)
    except KeyboardInterrupt:
        print("Received KeyboradInterrupt. Stop.", file=sys.stderr)
    return weight, iteration


data = np.array([[]])
data = np.reshape(data, (-1, 3))  # reshape to 2D array, each row has 3 columns.
try:
    data = read_to_2d_array(data, random_path)
except FileNotFoundError:
    print(f"{bcolors.FAIL}Error, {random_path} is not found. Please generate first.{bcolors.ENDC}", file=sys.stderr)
    quit(1)
weight, iteration = PLA(data)

# plot function curve
# a + bx + cy = 0
# y = -(b/c)x - (a/c)
m = -(weight[1] / weight[2])
b = -weight[0] / weight[2]
x = np.arange(num_samples + 1) if num_samples > rand_param else np.arange(rand_param + 1)
y = m * x + b
print(f"y = {m}x + {b}")
plt.plot(x, y)

# plot random points. Blue: positive; Red: negative
for i in data:
    if i[2] == 1:
        plt.plot(i[0], i[1], 'o', color="blue")
    elif i[2] == -1:
        plt.plot(i[0], i[1], 'x', color="red")
    else:
        pass

# plt.plot([i[0] for i in data[:pos_num]], [i[1] for i in data[:pos_num]], 'o', color="blue")
# plt.plot([i[0] for i in data[pos_num:]], [i[1] for i in data[pos_num:]], 'x', color="red")
plt.show()
