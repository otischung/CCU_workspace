CREATE DATABASE IF NOT EXISTS `library`;
USE DATABASE `library`;

-- Add entities to tables
CREATE TABLE IF NOT EXISTS `Branch` (
    `bcode` VARCHAR(10) NOT NULL PRIMARY KEY,
    `Librarian` TEXT NOT NULL,
    `Address` TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS `Titles` (
    `title` VARCHAR(300) NOT NULL PRIMARY KEY,
    `author` TEXT NOT NULL,
    `publisher` TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS `Holdings` (
    `branch` VARCHAR(10) NOT NULL,
    `title` VARCHAR(300) NOT NULL,
    `copies` INT UNSIGNED NOT NULL,
    PRIMARY KEY (`branch`, `title`),
    FOREIGN KEY (`branch`)
        REFERENCES `Branch`(`bcode`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`title`)
        REFERENCES `Titles`(`title`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

-- Insert instance to tables
INSERT INTO `Branch` (`bcode`, `Librarian`, `Address`)
    VALUES
        ('B1',  'John Smith',   '2 Anglesea Rd'),
        ('B2',  'Mary Jones',   '34 Pearse St'),
        ('B3',  'Francis',      'Grange X');

INSERT INTO `Titles` (`title`, `author`, `publisher`)
    VALUES
        ('Susannah',            'Ann Brown',        'Macmillan'),
        ('How to Fish',         'Amy Fly',          'Stop Press'),
        ('A History of Dublin', 'David Little',     'Wiley'),
        ('Computers',           'Blaise Pascal',    'Applewoods'),
        ('The Wife',            'Ann Brown',        'Macmillan');

INSERT INTO `Holdings` (`branch`, `title`, `copies`)
    VALUES
        ('B1', 'Susannah',              3),
        ('B1', 'How to Fish',           2),
        ('B1', 'A History of Dublin',   1),
        ('B2', 'How to Fish',           4),
        ('B2', 'Computers',             2),
        ('B2', 'The Wife',              3),
        ('B3', 'A History of Dublin',   1),
        ('B3', 'Computers',             4),
        ('B3', 'Susannah',              3),
        ('B3', 'The Wife',              1);
