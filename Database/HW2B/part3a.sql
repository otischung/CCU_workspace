-- Create database and use the database
CREATE DATABASE `courses`;
USE `courses`;

-- Add entities to tables
CREATE TABLE `Person` (
    `ssn` TEXT NOT NULL,
    `name` TEXT NOT NULL,
    `age` INT NOT NULL,
    PRIMARY KEY (`ssn`)
);

CREATE TABLE `Teacher` (
    `ssn` TEXT NOT NULL,
    `tid` INT NOT NULL,
    UNIQUE (`tid`),
    PRIMARY KEY (`ssn`)
);

CREATE TABLE `Student` (
    `ssn` TEXT NOT NULL,
    `sid` INT NOT NULL,
    UNIQUE (`sid`),
    PRIMARY KEY (`ssn`)
);

CREATE TABLE `Department` (
    `department_id` INT NOT NULL,
    `name` TEXT NOT NULL,
    PRIMARY KEY (`department_id`)
);

CREATE TABLE `Classroom` (
    `building_number` INT NOT NULL,
    `room_number` INT NOT NULL,
    PRIMARY KEY (`building_number`, `room_number`)
);

CREATE TABLE `Course` (
    `crn` INT NOT NULL,
    `title` TEXT NOT NULL,
    `use_classroom_building` INT COMMENT 'A course may not use any classroom.',
    `use_classroom_room` INT COMMENT 'A course may not use any classroom.',
    `lecturer` INT COMMENT 'A course may not be taught by any person.',
    `teacher` INT COMMENT 'If the lecturer is a teacher, then it will be same as lecturer. Otherwise, it will be NULL.',
    `department` INT COMMENT 'A course is offered by at most one department.',
    PRIMARY KEY (`crn`),
    FOREIGN KEY (`use_classroom_building`, `use_classroom_room`)
        REFERENCES `Classroom`(`building_number`, `room_number`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`lecturer`)
        REFERENCES `Person`(`ssn`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`teacher`)
        REFERENCES `Teacher`(`ssn`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`department`)
        REFERENCES `Department`(`department_id`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

-- Add relations to tables
CREATE TABLE `belongs` (
    `person_ssn` INT NOT NULL,
    `department_id` INT COMMENT 'A person may not belong to any department.',
    PRIMARY KEY (`person_ssn`, `department_id`),
    FOREIGN KEY (`person_ssn`)
        REFERENCES `Person`(`ssn`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`department_id`)
        REFERENCES `Department`(`department_id`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE `registers` (
    `student_ssn` INT NOT NULL,
    `course_crn` INT NOT NULL,
    PRIMARY KEY (`student_ssn`, `course_crn`),
    FOREIGN KEY (`student_ssn`)
        REFERENCES `Student`(`ssn`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`course_crn`)
        REFERENCES `Course`(`crn`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);
