USE `courses`;

-- Delete all rows for every tables.
DELETE FROM `Students`;
DELETE FROM `Professors`;
DELETE FROM `Departments`;
DELETE FROM `Courses`;
DELETE FROM `Take`;
DELETE FROM `Teach`;
DELETE FROM `PreReq`;

INSERT INTO `Students`(`PID`, `Name`, `Address`) VALUES
    ('Zadeh',       'Lofti',    'Seattle, WA'),
    ('Patterson',   'David',    'Los Angeles, CA'),
    ('Smith',       'Alan',     'San Francisco, CA'),
    ('Feiner',      'Steven',   'Boston, MA'),
    ('Kuck',        'David',    'Bloomington, IN'),
    ('Kender',      'John',     'Los Angeles, CA'),
    ('Huang',       'Thomas',   'Atlanta, GA'),
    ('Fischer',     'Michael',  'Madison, WI'),
    ('Appel',       'Andrew',   'Miami, FL'),
    ('Dobkin',      'David',    'Salt Lake City, UT'),
    ('Li',          'Kai',      'Las Vegas, NV'),
    ('Peterson',    'Larry',    'Chicago, IL');

INSERT INTO `Departments`(`Name`, `ChairmanPID`) VALUES
    ('CS',   NULL),
    ('EE',   NULL),
    ('ME',   NULL),
    ('BIO',  NULL),
    ('PHY',  NULL),
    ('MATH', NULL);

INSERT INTO `Professors`(`PID`, `Name`, `Age`, `DepartmentName`) VALUES
    ('Widom',   'Jennifer', 'old',          'BIO'),
    ('Canny',   'John',     'very old',     'EE'),
    ('Ullman',  'Jeff',     'still alive',  'CS'),      -- Chairman
    ('Reiss',   'Steve',    'very old',     'PHY'),     -- Chairman
    ('Karp',    'Richard',  'still alive',  'MATH'),
    ('Lam',     'Monica',   'old',          'ME'),      -- Chairman
    ('Chien',   'Andrew',   'old',          'PHY'),
    ('Wegner',  'Peter',    'still alive',  'MATH'),    -- Chairman
    ('Hart',    'John',     'very old',     'BIO'),
    ('Katz',    'Randy',    'very old',     'CS'),
    ('Knuth',   'Don',      'still alive',  'EE'),      -- Chairman
    ('Barsky',  'Brian',    'old',          'EE');

UPDATE `Departments` SET `ChairmanPID` = 'Ullman' WHERE `Name` = 'CS';
UPDATE `Departments` SET `ChairmanPID` = 'Knuth' WHERE `Name` = 'EE';
UPDATE `Departments` SET `ChairmanPID` = 'Lam' WHERE `Name` = 'ME';
UPDATE `Departments` SET `ChairmanPID` = 'Reiss' WHERE `Name` = 'PHY';
UPDATE `Departments` SET `ChairmanPID` = 'Wegner' WHERE `Name` = 'MATH';

INSERT INTO `Courses`(`Number`, `DeptName`, `CourseName`, `MaxEnrollment`, `ActualEnrollment`) VALUES
    (132, 'ME',   'Dynamic Systems',      120, 118),
    (61,  'CS',   'Data Structure',       100,  90),
    (1,   'MATH', 'Calculus',             150, 132),
    (123, 'EE',   'Digital Signal Proc',   80,  72),
    (111, 'PHY',  'Modern Physics',        40,  39),
    (109, 'ME',   'Heat Transfer',         10,   8),
    (54,  'MATH', 'Linear Algebra',        50,  50),
    (162, 'CS',   'Operating Systems',     50,  32),
    (137, 'PHY',  'Quantum Mech',          10,   3),
    (145, 'BIO',  'Genomics',               5,   2),
    (186, 'CS',   'Database Systems',      50,  48),
    (224, 'EE',   'Digital Comm',          30,  22);


INSERT INTO `Teach`(`ProfessorPID`, `Number`, `DeptName`) VALUES
    ('Knuth',  123, 'EE'),
    ('Reiss',   54, 'MATH'),
    ('Widom',  145, 'BIO'),
    ('Ullman',  61, 'CS'),
    ('Karp',   224, 'EE'),
    ('Lam',    132, 'ME'),
    ('Reiss',  111, 'PHY'),
    ('Wegner',   1, 'MATH'),
    ('Ullman', 186, 'CS'),
    ('Reiss',  137, 'PHY'),
    ('Chien',  109, 'ME'),
    ('Barsky', 162, 'CS');

INSERT INTO `PreReq`(`Number`, `DeptName`, `PreReqNumber`, `PreReqDeptName`) VALUES
    (111, 'PHY',    1, 'MATH'),
    (137, 'PHY',    1, 'MATH'),
    (123, 'EE',    54, 'MATH'),
    (186, 'CS',    54, 'MATH'),
    (224, 'EE',    54, 'MATH'),
    (186, 'CS',    61, 'CS'),
    (224, 'EE',    61, 'CS'),
    (111, 'PHY',  132, 'ME'),
    (145, 'BIO',  132, 'ME'),
    (132, 'ME',   145, 'BIO'),
    ( 54, 'MATH', 162, 'CS'),
    (162, 'CS',   186, 'CS'),
    (109, 'ME',   224, 'EE');
    

INSERT INTO `Take`(`StudentPID`, `Number`, `DeptName`, `Grade`, `ProfessorEvaluation`) VALUES
    ('Appel',     111, 'PHY',  'B', 2),
    ('Patterson', 186, 'CS',   'B', 3),
    ('Li',        137, 'PHY',  'A', 3),
    ('Huang',     186, 'CS',   'A', 4),
    ('Smith',     109, 'ME',   'A', 3),
    ('Appel',       1, 'MATH', 'C', 2),
    ('Huang',     123, 'EE',   'A', 4),
    ('Fischer',   145, 'BIO',  'A', 2),
    ('Zadeh',      61, 'CS',   'A', 1),
    ('Dobkin',    123, 'EE',   'B', 4),
    ('Huang',     111, 'PHY',  'B', 3),
    ('Li',        162, 'CS',   'A', 3),
    ('Kender',     54, 'MATH', 'B', 4);
