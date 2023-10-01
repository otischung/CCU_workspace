**Database HW5**

---
## Author Information

- Name: 鍾博丞

- Student ID: 408410120

- E-mail: my072814638@csie.io



## Project Information

- Programming Language: C++ standard 11
- CMake: 3.0.0 or newer
- Demo video in YouTube:
  - https://youtu.be/Vjcx1fBBWaI




## Feature

- Initialization
- Perform **Binary Search** for all internal nodes and data leaf nodes
- All the internal nodes and data leaf nodes have their **parent's pointer** and thus can traverse back to the root.
- Insertion **with re-distribution**
- Deletion **with re-distribution**
- Templated class implementation, which can allow another numerical type.
- Display
- **Ignore** the same data
- SIGINT handling
- Quit



## CMake and Makefile

1. Make a new directory called `build`.
2. Change to `build` directory.
3. Type `cmake ..`, or `cmake -S .. -B .` This will create a Makefile inside the `build` directory.
4. Type `make`. This will create the target executable file called `BTree` inside the `build` directory.



## Execution

- `./BTree` will enter the shell directly.
- `./BTree [ORDER] [VAULE 1] [VALUE 2] ...` will specify the order and insert the following values.



## Shell

- Type `h` or `help` can get the full usage.
- All floating points will convert to integers by taking float automatically.
- All invalid input and all the following commands, e.g. type `abc` in integer area, will be ignored.
- `c 2` will create a B+ tree with order 2, capacity 4.
  - Note that `c 2 3 4` will ignore `3 4`.
- `dd` will delete the whole B+ tree.
- `i 1 2 3 4` will insert the value in order with 1, 2, 3, and 4.
  - `i 1 2 a 3` will insert the value in order with 1 and 2, ignore a and 3.

- `d 3 1 4 2` will delete the value in order with 3, 1, 4, and 2.
- `f 4 1 3 2` will find the value in order with 4, 1, 3, and 2.
- `s` will show the B+ tree.
- `sd` will show the B+ tree with debug message. Including the amount of data in an internal node, the height of a node, and traversing the leaf node from left to right and then from right to left.
- `\! [COMMAND]` will execute the shell command. Just like MySQL.
- `q`, `exit`, EOF, or Ctrl+C will exit the program.



## Example

```bash
./BTree 2 60 58 56 54 52 50 48 46 44 42 40 38 36 34 32 30 28 26 24 22 20 18 16 14 12 10 8 6 4 2
> sd
```

Output: 

```
(32,50,_,_): #30, h: 0
        (8,14,20,26): #15, h: 1
                [2,4,6,_]
                [8,10,12,_]
                [14,16,18,_]
                [20,22,24,_]
                [26,28,30,_]
        (38,44,_,_): #9, h: 1
                [32,34,36,_]
                [38,40,42,_]
                [44,46,48,_]
        (56,61,_,_): #6, h: 1
                [50,52,54,_]
                [56,58,60,_]

30 data in B+ tree.

-------------------------------
Testing the doubly-linked list.

From left to right:
[2,4,6,_] --> [8,10,12,_] --> [14,16,18,_] --> [20,22,24,_] --> [26,28,30,_] --> [32,34,36,_] --> [38,40,42,_] --> [44,46,48,_] --> [50,52,54,_] --> [56,58,60,_] --> NULL

From right to left:
[56,58,60,_] --> [50,52,54,_] --> [44,46,48,_] --> [38,40,42,_] --> [32,34,36,_] --> [26,28,30,_] --> [20,22,24,_] --> [14,16,18,_] --> [8,10,12,_] --> [2,4,6,_] --> NULL
```



