-- Create database and use the database
CREATE DATABASE IF NOT EXISTS `donation_record`;
USE `donation_record`;

-- Add entities to tables
CREATE TABLE IF NOT EXISTS `government` (
    `name` VARCHAR(300) NOT NULL PRIMARY KEY,
    `rank` TEXT NOT NULL,
    `salary` INT
);

CREATE TABLE IF NOT EXISTS `politician` (
    `name` VARCHAR(300) NOT NULL PRIMARY KEY,
    `party` TEXT,
    `gender` TEXT NOT NULL
);

-- Add relations to tables
CREATE TABLE IF NOT EXISTS `donation` (
    `name` VARCHAR(300) NOT NULL,
    `organization` VARCHAR(300),
    `amount` INT NOT NULL,
    PRIMARY KEY (`name`, `organization`)
);

-- Insert instance to tables
INSERT INTO `government` (`name`, `rank`, `salary`)
    VALUES
        ('Albert', 'minister', 150000),
        ('Bobbie', 'clerk', 50000),
        ('Don', 'clerk', NULL),
        ('Mike', 'clerk', 50000);

INSERT INTO `politician` (`name`, `party`, `gender`)
    VALUES
        ('Albert', 'Republic', 'male'),
        ('Charlie', 'Democrat', 'male'),
        ('Mike', NULL, 'male');

INSERT INTO `donation` (`name`, `organization`, `amount`)
    VALUES
        ('Charlie', 'American Red Cross', 150000),
        ('Charlie', 'National AIDS Fund', 80000),
        ('Charlie', 'UNICEF', 80000),
        ('Don', 'NineMillion', 50000),
        ('Don', 'American Red Cross', 60000),
        ('Campbell', 'American Red Cross', 70000),
        ('Campbell', 'National AIDS Fund', 60000),
        ('Mike', 'NineMillion', 90000);
