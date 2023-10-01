CREATE DATABASE IF NOT EXISTS `course_2`;
USE `course_2`;

-- Entities
CREATE TABLE IF NOT EXISTS `Students` (
    `sid` INT NOT NULL PRIMARY KEY,
    `sname` TEXT NOT NULL,
    `age` INT NOT NULL
);

CREATE TABLE IF NOT EXISTS `Courses` (
    `cid` INT NOT NULL PRIMARY KEY,
    `cname` TEXT NOT NULL,
    `credits` INT NOT NULL
);

-- Relations
CREATE TABLE IF NOT EXISTS `Enrolled` (
    `sid` INT NOT NULL,
    `cid` INT NOT NULL,
    `grade` INT NOT NULL,
    PRIMARY KEY (`sid`, `cid`),
    FOREIGN KEY (`sid`)
        REFERENCES `Students`(`sid`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`cid`)
        REFERENCES `Courses`(`cid`)
            ON DELETE CASCADE
            ON UPDATE CASCADE
);
