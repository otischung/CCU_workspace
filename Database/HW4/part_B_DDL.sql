CREATE DATABASE IF NOT EXISTS `company`;
USE `company`;

-- Entities
CREATE TABLE IF NOT EXISTS `Emp` (
    `eid` INT NOT NULL PRIMARY KEY,
    `ename` TEXT NOT NULL,
    `age` INT NOT NULL,
    `salary` REAL NOT NULL
);

CREATE TABLE IF NOT EXISTS `Dept` (
    `did` INT NOT NULL PRIMARY KEY,
    `dname` TEXT NOT NULL,
    `budget` REAL NOT NULL,
    `managerid` INT NOT NULL
);

-- Relations
CREATE TABLE IF NOT EXISTS `Works` (
    `eid` INT NOT NULL,
    `did` INT NOT NULL,
    `pct_time` INT NOT NULL COMMENT 'the percentage of time that a given employee works in a given department.',
    PRIMARY KEY (`eid`, `did`),
    FOREIGN KEY (`eid`)
        REFERENCES `Emp`(`eid`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`did`)
        REFERENCES `Dept`(`did`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);
