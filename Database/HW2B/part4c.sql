-- Use the database
USE `actor`;

-- Add relations to tables
CREATE TABLE `act` (
    `person_ssn` VARCHAR(50),
    `movie_title` VARCHAR(50),
    PRIMARY KEY (`person_ssn`, `movie_title`),
    FOREIGN KEY (`person_ssn`)
        REFERENCES `Person`(`ssn`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (`movie_title`)
        REFERENCES `Movie`(`title`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);
