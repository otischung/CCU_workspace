CREATE DATABASE IF NOT EXISTS `booking_record`;
USE `booking_record`;

-- Entities
CREATE TABLE IF NOT EXISTS `Books` (
    `bid` INT UNSIGNED NOT NULL PRIMARY KEY COMMENT 'book unique id',
    `btitle` TEXT NOT NULL COMMENT 'book title',
    `author` TEXT NOT NULL COMMENT 'name of book author',
    `year` SMALLINT UNSIGNED NOT NULL COMMENT 'book publication year',
    `price` INT NOT NULL COMMENT 'unit price per copy'
);

CREATE TABLE IF NOT EXISTS `Customers` (
    `cid` INT UNSIGNED NOT NULL PRIMARY KEY COMMENT 'unique customer identifier',
    `cname` TEXT NOT NULL COMMENT 'customer name',
    `zipcode` TEXT NOT NULL COMMENT 'customer address zipcode'
);

-- Relations
CREATE TABLE IF NOT EXISTS `Orders` (
    `cid` INT UNSIGNED NOT NULL,
    `bid` INT UNSIGNED NOT NULL,
    `quantity` INT NOT NULL COMMENT 'number of book copies purchased with an order',
    PRIMARY KEY (`cid`, `bid`),
    FOREIGN KEY (`cid`)
        REFERENCES `Customers`(`cid`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`bid`)
        REFERENCES `Books`(`bid`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);
