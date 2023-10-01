-- Create database and use the database
CREATE DATABASE `airline_reservation_system`;
USE `airline_reservation_system`;

-- Add entities to tables
CREATE TABLE `Reservation` (
    `reservation_id` INT NOT NULL PRIMARY KEY,
    `price` REAL NOT NULL,
    `paid` TINYINT NOT NULL DEFAULT 0 COMMENT '0 means not paid, 1 means paid.',
    `customer_information` TEXT NOT NULL,
    `credit_card` VARCHAR(20)
);

CREATE TABLE `Company` (
    `company_id` INT NOT NULL PRIMARY KEY,
    `name` TEXT NOT NULL
);

CREATE TABLE `Aircraft` (
    `registration_number` INT NOT NULL PRIMARY KEY,
    `max_capacity` INT NOT NULL,
    `model` TEXT NOT NULL,
    `make` TEXT NOT NULL,
    `belongs_to` INT NOT NULL,
    FOREIGN KEY (`belongs_to`)
        REFERENCES `Company`(`company_id`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE `Airport` (
    `code` VARCHAR(16) NOT NULL PRIMARY KEY,
    `name` TEXT NOT NULL,
    `country` TEXT NOT NULL,
    `city` TEXT NOT NULL
);

CREATE TABLE `Seat` (
    `aircraft_registration_number` INT NOT NULL,
    `id` INT NOT NULL,
    `reservation_id` INT,
    `class` TINYINT UNSIGNED NOT NULL COMMENT '0: First Class; 1: Business Class; 2:  Economy class',
    PRIMARY KEY (`aircraft_registration_number`, `id`),
    FOREIGN KEY (`aircraft_registration_number`)
        REFERENCES `Aircraft`(`registration_number`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
) COMMENT = 'This is a weak entity.';

CREATE TABLE `Flight` (
    `number` INT NOT NULL PRIMARY KEY,
    `route` TINYINT UNSIGNED NOT NULL COMMENT '0: Domestic; 1: International',
    `airline` INT NOT NULL,
    `aircraft_use` INT NOT NULL,
    `depart` VARCHAR(16) NOT NULL,
    `arrive` VARCHAR(16) NOT NULL,
    FOREIGN KEY (`airline`)
        REFERENCES `Company`(`company_id`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`aircraft_use`)
        REFERENCES `Aircraft`(`registration_number`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`depart`)
        REFERENCES `Airport`(`code`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`arrive`)
        REFERENCES `Airport`(`code`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE `Ticket` (
    `ticket_id` INT NOT NULL PRIMARY KEY,
    `ticket_order` SMALLINT UNSIGNED NOT NULL DEFAULT 0,
    `reservation_id` INT NOT NULL,
    `reserve_time` INT NOT NULL,
    `flight_number` INT NOT NULL,
    `aircraft_registration_number` INT NOT NULL,
    `seat_id` INT NOT NULL,
    FOREIGN KEY (`reservation_id`)
        REFERENCES `Reservation`(`reservation_id`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`flight_number`)
        REFERENCES `Flight`(`number`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`aircraft_registration_number`, `seat_id`)
        REFERENCES `Seat`(`aircraft_registration_number`, `id`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);
