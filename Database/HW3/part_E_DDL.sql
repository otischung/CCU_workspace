CREATE DATABASE IF NOT EXISTS `computer_products`;
USE `computer_products`;

-- Entities
CREATE TABLE IF NOT EXISTS `Manufacturer` (
    `name` VARCHAR(100) NOT NULL PRIMARY KEY,
    `country` TEXT NOT NULL,
    `phone` TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS `Computer` (
    `model` VARCHAR(100) NOT NULL PRIMARY KEY
) COMMENT 'Base Table';

CREATE TABLE IF NOT EXISTS `Desktop` (
    `model` VARCHAR(100) NOT NULL PRIMARY KEY,
    `speed` REAL NOT NULL,
    `ram` INT UNSIGNED NOT NULL COMMENT 'Unsigned int in GB',
    `hd` INT UNSIGNED NOT NULL COMMENT 'Hard Disk size, unsigned int in GB',
    `list_price` REAL UNSIGNED NOT NULL
) COMMENT 'Derived Table from Computer';

CREATE TABLE IF NOT EXISTS `Laptop` (
    `model` VARCHAR(100) NOT NULL PRIMARY KEY,
    `speed` REAL NOT NULL,
    `ram` INT UNSIGNED NOT NULL COMMENT 'Unsigned int in GB',
    `hd` INT UNSIGNED NOT NULL COMMENT 'Hard Disk size, unsigned int in GB',
    `screen` REAL UNSIGNED NOT NULL COMMENT 'Unsigned real in inch',
    `list_price` REAL UNSIGNED NOT NULL
) COMMENT 'Derived Table from Computer';

-- Relations
CREATE TABLE IF NOT EXISTS `Product` (
    `manu_name` VARCHAR(100) NOT NULL,
    `model` VARCHAR(100) NOT NULL,
    `style` VARCHAR(100) NOT NULL,
    PRIMARY KEY (`manu_name`, `model`, `style`),
    FOREIGN KEY (`manu_name`)
        REFERENCES `Manufacturer`(`name`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`model`)
        REFERENCES `Computer`(`model`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);
