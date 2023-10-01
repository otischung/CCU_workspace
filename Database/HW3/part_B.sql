-- Create database and use the database
CREATE DATABASE IF NOT EXISTS `school_organization`;
USE `school_organization`;

-- Add entities to tables
CREATE TABLE IF NOT EXISTS `professor` (
    `profname` VARCHAR(300) NOT NULL,
    `deptname` VARCHAR(300) NOT NULL,
    PRIMARY KEY (`profname`, `deptname`)
);

CREATE TABLE IF NOT EXISTS `department` (
    `deptname` VARCHAR(300) NOT NULL,
    `building` VARCHAR(300) NOT NULL,
    PRIMARY KEY (`deptname`, `building`)
);

CREATE TABLE IF NOT EXISTS `committee` (
    `commname` VARCHAR(300) NOT NULL,
    `profname` VARCHAR(300) NOT NULL,
    PRIMARY KEY (`commname`, `profname`)
);

-- Insert instance to tables
INSERT INTO `professor` (`profname`, `deptname`)
    VALUES
        ('Piper', 'Computer Science'),
        ('James', 'Computer Science'),
        ('George', 'Computer Science'),
        ('William', 'Electrical Engineering'),
        ('Matthew', 'Electrical Engineering'),
        ('Oliver', 'Mechanical Engineering'),
        ('Lewis', 'Mechanical Engineering');

INSERT INTO `department` (`deptname`, `building`)
    VALUES
        ('Computer Science', 'ICICS/CS'),
        ('Electrical Engineering', 'KAIS'),
        ('Mechanical Engineering', 'CEME');

INSERT INTO `committee` (`commname`, `profname`)
    VALUES
        ('Operation', 'James'),
        ('Operation', 'William'),
        ('Communication', 'James'),
        ('Communication', 'Piper'),
        ('Communication', 'Oliver'),
        ('Communication', 'Lewis'),
        ('Teaching', 'James'),
        ('Teaching', 'Piper'),
        ('Teaching', 'Matthew'),
        ('Teaching', 'Lewis'),
        ('Graduate Admissions', 'William'),
        ('Graduate Admissions', 'George'),
        ('Computing', 'Matthew');
