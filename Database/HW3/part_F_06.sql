USE `booking_record`;

-- Find the authors of the books that were ordered only from zipcode 02125.
SELECT DISTINCT `author`
FROM `Books`
JOIN `Orders` ON `Books`.`bid` = `Orders`.`bid`
JOIN `Customers` ON `Orders`.`cid` = `Customers`.`cid`
WHERE `zipcode` = '02125'
    AND `Books`.`bid` NOT IN (
            SELECT DISTINCT `Books`.`bid`
            FROM `Books`
            JOIN `Orders` ON `Books`.`bid` = `Orders`.`bid`
            JOIN `Customers` ON `Orders`.`cid` = `Customers`.`cid`
            WHERE `zipcode` != '02125'
    );
