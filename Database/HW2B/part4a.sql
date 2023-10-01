-- Create database and use the database
CREATE DATABASE `actor`;
USE `actor`;

-- Add entities to tables
CREATE TABLE `Person` (
    `ssn` VARCHAR(50) NOT NULL,
    `name` VARCHAR(50) NOT NULL,
    `age` INT NOT NULL,
    PRIMARY KEY (`ssn`)
);
