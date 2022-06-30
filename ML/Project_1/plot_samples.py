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


data = np.array([[]])
data = np.reshape(data, (-1, 3))  # reshape to 2D array, each row has 3 columns.
data = read_to_2d_array(data, random_path)

# plot function curve
x = np.arange(rand_param + 1)
y = m * x + b
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
