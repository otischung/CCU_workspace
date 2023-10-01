USE `company`;

-- Delete all rows for every tables.
DELETE FROM `Emp`;
DELETE FROM `Dept`;
DELETE FROM `Works`;

-- These are from sample data.
INSERT INTO `Emp`(`eid`, `ename`, `age`, `salary`) VALUES
    ( 1, 'Alice',    28,  55000.0),
    ( 2, 'Bob',      32,  62000.0),
    ( 3, 'Charlie',  45,  75000.0),
    ( 4, 'David',    22, 100000.0),
    ( 5, 'Emily',    36,  80000.0),
    ( 6, 'Frank',    50,  95000.0),
    ( 7, 'George',   29,  56000.0),
    ( 8, 'Henry',    41,  68000.0),
    ( 9, 'Isabelle', 27,  50000.0),
    (10, 'Jack',     31,  61000.0);

INSERT INTO `Dept`(`did`, `dname`, `budget`, `managerid`) VALUES
    (1, 'Software', 3000000.0, 3),
    (2, 'Marketing',  75000.0, 5),
    (3, 'Hardware', 4000001.0, 6),
    (4, 'Finance',  1000000.0, 7),
    (5, 'HR',         90000.0, 9),
    (6, 'Sales',    1000000.0, 6);

INSERT INTO `Works`(`eid`, `did`, `pct_time`) VALUES
    ( 1, 1, 100),
    ( 2, 1, 100),
    ( 3, 1,  33),
    ( 3, 3,  33),
    ( 3, 4,  34),
    ( 4, 1,  30),
    ( 4, 2,  70),
    ( 5, 1,  30),
    ( 5, 2,  70),
    ( 6, 3,  70),
    ( 6, 6,  30),
    ( 7, 1,  70),
    ( 7, 4,  30),
    ( 8, 1,  70),
    ( 8, 4,  30),
    ( 9, 1,  70),
    ( 9, 5,  30),
    (10, 1,  70),
    (10, 5,  30);
