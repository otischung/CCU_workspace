# DS HW01 Erasure Code

## Why We Need Erasure Code

A data center consists of multiple severs, they are connected by switches in a local area network.

When the system needs to be upgraded, the power failure, or system crash, etc., the data will not be available. Therefore, data cannot be stored in one server only. We need **backup** schemes to maintain availability.

There are two schemas to maintain data availability, one is to make three copies. Assume that the availability rate of each data is 90%, the availability of three copies of data is 1 - (1 - 0.9)^3 = 99.9%. The redundancy rate is 200%.

The other schema is **erasure code**, we divide data into n chunks, and we make (n + m) chunks. Any n chunks in these (n + m) chunks can reconstruct the data. For instance, if we make (5 + 5) chunks, the availability rate of data is 99.9985%. Furthermore, the redundancy rate is less than copying data, it is only 100%.

## Project

If we have n linear equations with n variables, and the equations are linear independent, then there is a unique solution.

We can use **Vandermonde matrix** to generate m chunks

> 1	1	1	1	...	1
>
> 1	2	4	8	...	2^n-1
>
> 1	3	9	27  ...	3^n-1
>
> ...

For example, if the data is 22 and we need to cut into 2 chunks and generate 2 additional chunks, we first divide the data 22 into [2, 2], then we will have

x = 2

y = 2

That is, the augmented matrix will be

>1	0	2
>
>0	1	2

Then, we use x, y, and Vandermonde matrix to generate 2 chunks

x + y = 4

x + 2y = 6

That is, the augmented matrix will be

> 1	1	4
>
> 1	2	6

Then, we have 4 chunks (equations). We can choose any 2 distinct equations here to reconstruct the data 22.

## stdin and stdout

Mode 0 means encode, mode 1 means decode.

When it is in encode mode:

Input:

Mode	n	m

Input string

Output: 

(n + m) equations

Example:

stdin:

0	2	2

22

stdout:

1	0	2

0	1	2

1	1	4

1	2	6

When it is in decode mode:

Input:

Mode	n

n_equations

Output: 

Data

Example:

stdin:

1	2

1	1	4

1	2	6

stdout:

22

