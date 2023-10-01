USE `course_2`;

-- Delete all rows for every tables.
DELETE FROM `Students`;
DELETE FROM `Courses`;
DELETE FROM `Enrolled`;

-- These are from sample data.
INSERT INTO `Students`(`sid`, `sname`, `age`) VALUES
    ( 1, 'Alice',   18),
    ( 2, 'Bob',     25),
    ( 3, 'Charlie', 20),
    ( 4, 'David',   19),
    ( 5, 'Ella',    23),
    ( 6, 'Frank',   24),
    ( 7, 'Grace',   18),
    ( 8, 'Henry',   22),
    ( 9, 'Ivy',     25),
    (10, 'John',    21);

INSERT INTO `Courses`(`cid`, `cname`, `credits`) VALUES
    (1, 'Math',         4),
    (2, 'Science',      3),
    (3, 'English',      4),
    (4, 'Databases',    3),
    (5, 'Art',          2),
    (6, 'Music',        2),
    (7, 'Computer Sci', 4);

INSERT INTO `Enrolled`(`sid`, `cid`, `grade`) VALUES
    ( 1, 5,  6),
    ( 1, 7, 10),
    ( 2, 7,  7),
    ( 3, 1,  7),
    ( 3, 3,  7),
    ( 3, 7,  9),
    ( 4, 1,  9),
    ( 4, 7,  8),
    ( 5, 3,  7),
    ( 5, 7,  7),
    ( 6, 4, 10),
    ( 6, 6,  8),
    ( 7, 5,  8),
    ( 7, 7,  9),
    ( 8, 1,  6),
    ( 8, 7,  8),
    ( 9, 2,  7),
    ( 9, 4,  7),
    (10, 7,  8);
