CREATE DATABASE IF NOT EXISTS `recipes`;
USE `recipes`;

-- Enitites
CREATE TABLE IF NOT EXISTS `Dishes` (
    `did` INT NOT NULL PRIMARY KEY,
    `dname` TEXT NOT NULL,
    `origin` TEXT NOT NULL,
    `popularity` INT NOT NULL
);

CREATE TABLE IF NOT EXISTS `Ingredients` (
    `iid` INT NOT NULL PRIMARY KEY,
    `iname` TEXT NOT NULL,
    `unitprice` INT NOT NULL
);

-- Relations
CREATE TABLE IF NOT EXISTS `Recipes` (
    `did` INT NOT NULL,
    `iid` INT NOT NULL,
    `quantity` INT NOT NULL,
    PRIMARY KEY (`did`, `iid`),
    FOREIGN KEY (`did`)
        REFERENCES `Dishes`(`did`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`iid`)
        REFERENCES `Ingredients`(`iid`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);
