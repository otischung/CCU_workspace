USE `booking_record`;

-- Find the zipcodes of customers who ordered at least 10 copies
-- (in a single order) of a book written by an author whose name
-- starts with “Cod”.
SELECT DISTINCT `zipcode`
FROM `Customers`
JOIN `Orders` ON `Customers`.`cid` = `Orders`.`cid`
JOIN `Books` ON `Orders`.`bid` = `Books`.`bid`
WHERE `author` LIKE 'Cod%'
    AND `quantity` >= 10;
