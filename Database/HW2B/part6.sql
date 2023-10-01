-- Create database and use the database
CREATE DATABASE `mod`;
USE `mod`;

-- Add entities to tables
CREATE TABLE `Movie` (
    `title` VARCHAR(300) NOT NULL PRIMARY KEY,
    `rating` TINYINT UNSIGNED NOT NULL,
    `release_date` INT NOT NULL,
    `running_time` INT NOT NULL,
    `director` TEXT NOT NULL,
    `is_new_release` TINYINT UNSIGNED NOT NULL COMMENT '0: False; 1: True'
);

CREATE TABLE `Foreign_Movie` (
    `title` VARCHAR(300) NOT NULL PRIMARY KEY,
    `language` TEXT NOT NULL,
    `english_subtitle` TINYINT UNSIGNED NOT NULL COMMENT '0: False; 1: True'
);

CREATE TABLE `Domestic_Movie` (
    `title` VARCHAR(300) NOT NULL PRIMARY KEY
);

CREATE TABLE `Comedy_Movie` (
    `title` VARCHAR(300) NOT NULL PRIMARY KEY,
    `funniness` REAL NOT NULL
);

CREATE TABLE `Drama_Movie` (
    `title` VARCHAR(300) NOT NULL PRIMARY KEY,
    `discription` TEXT NOT NULL
);

CREATE TABLE `Action_Movie` (
    `title` VARCHAR(300) NOT NULL PRIMARY KEY
);

CREATE TABLE `Horror` (
    `title` VARCHAR(300) NOT NULL PRIMARY KEY
);

CREATE TABLE `Customer` (
    `ssn` VARCHAR(16) NOT NULL PRIMARY KEY,
    `name` TEXT NOT NULL,
    `phone_number` TEXT NOT NULL,
    `address` TEXT NOT NULL
);

CREATE TABLE `Credit_Card` (
    `card_number` VARCHAR(32) NOT NULL PRIMARY KEY,
    `type` TEXT NOT NULL,
    `expiration_date` INT NOT NULL,
    `owner` VARCHAR(16) NOT NULL,
    FOREIGN KEY (`owner`)
        REFERENCES `Customer`(`ssn`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE `Billing_Statement` (
    `buyer` VARCHAR(16) NOT NULL,
    `billing_number` INT NOT NULL,
    `charge` INT NOT NULL,
    `billing_date` INT NOT NULL,
    PRIMARY KEY (`buyer`, `billing_number`),
    FOREIGN KEY (`buyer`)
        REFERENCES `Customer`(`ssn`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
) COMMENT = 'This is a weak entity.';

CREATE TABLE `Viewing_Transation` (
    `view_id` INT NOT NULL PRIMARY KEY,
    `viewer` VARCHAR(16) NOT NULL,
    `movie` VARCHAR(300) NOT NULL,
    `time` INT NOT NULL,
    `date` INT NOT NULL,
    FOREIGN KEY (`viewer`)
        REFERENCES `Customer`(`ssn`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`movie`)
        REFERENCES `Movie`(`title`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE `Server` (
    `id` INT NOT NULL PRIMARY KEY,
    `address` TEXT NOT NULL
);

CREATE TABLE `Employee` (
    `ssn` VARCHAR(16) NOT NULL PRIMARY KEY,
    `name` TEXT NOT NULL,
    `birthday` INT NOT NULL,
    `phone_number` TEXT NOT NULL,
    `salary` INT NOT NULL,
    `is_permanent` TINYINT UNSIGNED NOT NULL COMMENT '0: False; 1: True',
    `works_at` INT NOT NULL,
    FOREIGN KEY (`works_at`)
        REFERENCES `Server`(`id`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE `Award` (
    `category` VARCHAR(300) NOT NULL PRIMARY KEY
);

CREATE TABLE `Actor` (
    `id` VARCHAR(16) NOT NULL PRIMARY KEY,
    `name` TEXT NOT NULL
);

CREATE TABLE `Critic` (
    `id` INT NOT NULL PRIMARY KEY,
    `name` TEXT NOT NULL,
    `phone_number` TEXT NOT NULL
);

CREATE TABLE `Address` (
    `id` INT NOT NULL PRIMARY KEY,
    `zip_code` VARCHAR(16) NOT NULL,
    `state` TEXT NOT NULL,
    `city` TEXT NOT NULL,
    `street_address` TEXT NOT NULL
);

CREATE TABLE `Distributor` (
    `id` INT NOT NULL PRIMARY KEY,
    `name` TEXT NOT NULL,
    `phone_number` TEXT NOT NULL,
    `address_id` INT NOT NULL,
    FOREIGN KEY (`address_id`)
        REFERENCES `Address`(`id`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

-- Add relations to tables
CREATE TABLE `store` (
    `movie` VARCHAR(300) NOT NULL,
    `server` INT NOT NULL,
    PRIMARY KEY (`movie`, `server`),
    FOREIGN KEY (`movie`)
        REFERENCES `Movie`(`title`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`server`)
        REFERENCES `Server`(`id`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE `reports_to` (
    `supervisor` VARCHAR(16) NOT NULL,
    `subordinate` VARCHAR(16) NOT NULL,
    PRIMARY KEY (`supervisor`, `subordinate`),
    FOREIGN KEY (`supervisor`)
        REFERENCES `Employee`(`ssn`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`subordinate`)
        REFERENCES `Employee`(`ssn`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE `win` (
    `movie` VARCHAR(300) NOT NULL,
    `award` VARCHAR(300) NOT NULL,
    PRIMARY KEY (`movie`, `award`),
    FOREIGN KEY (`movie`)
        REFERENCES `Movie`(`title`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`award`)
        REFERENCES `Award`(`category`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE `act` (
    `movie` VARCHAR(300) NOT NULL,
    `actor` VARCHAR(16) NOT NULL,
    PRIMARY KEY (`movie`, `actor`),
    FOREIGN KEY (`movie`)
        REFERENCES `Movie`(`title`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`actor`)
        REFERENCES `Actor`(`id`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE `evaluate` (
    `movie` VARCHAR(300) NOT NULL,
    `critic` INT NOT NULL,
    `star` TINYINT UNSIGNED NOT NULL,
    PRIMARY KEY (`movie`, `critic`),
    FOREIGN KEY (`movie`)
        REFERENCES `Movie`(`title`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`critic`)
        REFERENCES `Critic`(`id`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE `provide` (	
    `movie` VARCHAR(300) NOT NULL,
    `distributor` INT NOT NULL,
    PRIMARY KEY (`movie`, `distributor`),
    FOREIGN KEY (`movie`)
        REFERENCES `Movie`(`title`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`distributor`)
        REFERENCES `Distributor`(`id`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);
