CREATE DATABASE IF NOT EXISTS `courses`;
USE `courses`;

-- Entities
CREATE TABLE IF NOT EXISTS `Students` (
    `PID` VARCHAR(100) NOT NULL PRIMARY KEY,
    `Name` TEXT NOT NULL,
    `Address` TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS `Professors` (
    `PID` VARCHAR(100) NOT NULL PRIMARY KEY,
    `Name` TEXT NOT NULL,
    `Age` TEXT NOT NULL,
    `DepartmentName` VARCHAR(100) NOT NULL
);

CREATE TABLE IF NOT EXISTS `Departments` (
    `Name` VARCHAR(100) NOT NULL PRIMARY KEY,
    `ChairmanPID` VARCHAR(100) DEFAULT NULL COMMENT 'there are times when a department may not have a chairperson'
);

-- Circular References
ALTER TABLE `Professors`
ADD CONSTRAINT `FK_DepartmentName`
FOREIGN KEY (`DepartmentName`)
    REFERENCES `Departments`(`Name`)
    ON DELETE CASCADE
    ON UPDATE CASCADE;

ALTER TABLE `Departments`
ADD CONSTRAINT `FK_ChairmanPID`
FOREIGN KEY (`ChairmanPID`)
    REFERENCES `Professors`(`PID`)
    ON DELETE CASCADE
    ON UPDATE CASCADE;


CREATE TABLE IF NOT EXISTS `Courses` (
    `Number` INT NOT NULL PRIMARY KEY,
    `DeptName` VARCHAR(100) NOT NULL,
    `CourseName` TEXT NOT NULL,
    `MaxEnrollment` INT NOT NULL,
    `ActualEnrollment` INT NOT NULL DEFAULT 0,
    CONSTRAINT `check_enrollment`
        CHECK (`ActualEnrollment` <= `MaxEnrollment`),
    FOREIGN KEY (`DeptName`)
        REFERENCES `Departments`(`Name`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
) COMMENT 'The actual enrollment must be at most the maximum enrollment.';

-- Relations
CREATE TABLE IF NOT EXISTS `Take` (
    `StudentPID` VARCHAR(100) NOT NULL,
    `Number` INT NOT NULL COMMENT 'Course Number',
    `DeptName` VARCHAR(100) NOT NULL,
    `Grade` TEXT DEFAULT NULL,
    `ProfessorEvaluation` INT DEFAULT NULL,
    PRIMARY KEY (`StudentPID`, `Number`, `DeptName`),
    FOREIGN KEY (`StudentPID`)
        REFERENCES `Students`(`PID`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`Number`)
        REFERENCES `Courses`(`Number`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`DeptName`)
        REFERENCES `Departments`(`Name`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS `Teach` (
    `ProfessorPID` VARCHAR(100) NOT NULL,
    `Number` INT NOT NULL COMMENT 'Course Number',
    `DeptName` VARCHAR(100) NOT NULL,
    PRIMARY KEY (`ProfessorPID`, `Number`, `DeptName`),
    FOREIGN KEY (`ProfessorPID`)
        REFERENCES `Professors`(`PID`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`Number`)
        REFERENCES `Courses`(`Number`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`DeptName`)
        REFERENCES `Departments`(`Name`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS `PreReq` (
    `Number` INT NOT NULL COMMENT 'Course Number',
    `DeptName` VARCHAR(100) NOT NULL,
    `PreReqNumber` INT NOT NULL COMMENT 'PreReq Course Number',
    `PreReqDeptName` VARCHAR(100) NOT NULL,
    PRIMARY KEY (`Number`, `DeptName`, `PreReqNumber`, `PreReqDeptName`),
    FOREIGN KEY (`Number`)
        REFERENCES `Courses`(`Number`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`DeptName`)
        REFERENCES `Departments`(`Name`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`PreReqNumber`)
        REFERENCES `Courses`(`Number`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`PreReqDeptName`)
        REFERENCES `Departments`(`Name`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

-- Trigger
-- A course cannot be a pre-requisite for itself.
DELIMITER $$
CREATE TRIGGER `trg_check_prereq_self`
BEFORE INSERT ON `PreReq`
FOR EACH ROW BEGIN
    IF NEW.`Number` = NEW.`PreReqNumber` AND NEW.`DeptName` = NEW.`PreReqDeptName` THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'A course cannot be a pre-requisite for itself.';
    END IF;
END $$
DELIMITER ;

-- A student enrolled in a course must have
-- enrolled in all its pre-requisites.
DELIMITER //
CREATE TRIGGER `enforce_prereq` BEFORE INSERT ON `Take`
FOR EACH ROW BEGIN
    DECLARE num_prereqs INT;
    DECLARE num_completed_prereqs INT;
    SET num_prereqs = (
        SELECT COUNT(*) FROM `PreReq`
        WHERE `Number` = NEW.`Number` 
        AND `DeptName` = NEW.`DeptName`
    );
    SET num_completed_prereqs = (
        SELECT COUNT(*)
        FROM `Take`
        WHERE `StudentPID` = NEW.`StudentPID`
            AND `DeptName` = NEW.`DeptName`
            AND `Number` IN (
                SELECT `PreReqNumber` FROM `PreReq`
                WHERE `Number` = NEW.`Number`
                AND `DeptName` = NEW.`DeptName`
            )
            AND `Grade` IS NOT NULL
    );
    IF num_completed_prereqs < num_prereqs THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'Cannot enroll in course without completing all pre-requisites.';
    END IF;
END //
DELIMITER ;
