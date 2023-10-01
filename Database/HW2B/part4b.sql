-- Use the database
USE `actor`;

-- Add entities to tables
CREATE TABLE `Movie` (
    `title` VARCHAR(50) NOT NULL,
    `release_year` INT NOT NULL,
    `rating` INT NOT NULL,
    PRIMARY KEY (`title`)
);
