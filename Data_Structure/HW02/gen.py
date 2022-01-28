import random

n = random.randint(100, 300)
weights = []
edges = []

for i in range(n):
    weight = random.randint(1, 30)
    weights.append(weight)
    m = random.randint(1, n-1)
    e = set()
    for i in range(m):
        e.add(random.randint(1, n-1))
    edges.append(e)

print(n, len(edges),  7)
weights[0] = 0
for i, w in enumerate(weights):
    print(i, w)

for i, e in enumerate(edges):
    for j, v in enumerate(e):
        print(0, i, v)
