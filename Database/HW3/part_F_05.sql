USE `booking_record`;

-- Find the titles of books ordered by those customers
-- who are the only registered customers in their particular zipcode area
-- (i.e., there is no other customer with the same zipcode in the Customers table).
SELECT DISTINCT `btitle`
FROM `Books`
JOIN `Orders` ON `Books`.`bid` = `Orders`.`bid`
JOIN `Customers` ON `Orders`.`cid` = `Customers`.`cid`
WHERE `zipcode` IN (
    SELECT `zipcode`
    FROM `Customers`
    GROUP BY `zipcode`
    HAVING COUNT(*) = 1
);
