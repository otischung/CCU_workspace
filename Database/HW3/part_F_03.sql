USE `booking_record`;

-- Find the names of customers who ordered some book published in year 2000 and also ordered at least 10 copies of some book that costs more than $100.
SELECT DISTINCT `cname`
FROM `Customers`
JOIN `Orders` ON `Customers`.`cid` = `Orders`.`cid`
JOIN `Books` ON `Orders`.`bid` = `Books`.`bid`
WHERE `year` = 2000 AND `price` > 100 AND `quantity` >= 10;
