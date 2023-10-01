USE `booking_record`;

-- Find the authors of books that cost at most $40 and were ordered from zipcode 12345.
SELECT DISTINCT `author`
FROM `Books`
INNER JOIN `Orders` ON `Books`.`bid` = `Orders`.`bid`
INNER JOIN `Customers` ON `Orders`.`cid` = `Customers`.`cid`
WHERE `price` <= 40 AND `zipcode` = '12345';
