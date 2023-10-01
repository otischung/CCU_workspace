USE `booking_record`;

-- For each customer who ordered at least 5 distinct books
-- (regardless of publication year),
-- find the price of the most expensive book published in 1990
-- which was ordered by that customer.
-- In the output, the costumer should be listed by name.
SELECT c.`cname`, MAX(b.`price`) AS `max_price`
FROM (
    SELECT o.`cid`
    FROM `Orders` o
    GROUP BY o.`cid`
    HAVING COUNT(DISTINCT o.`bid`) >= 5
) AS `subq`
JOIN `Customers` c ON `subq`.`cid` = c.`cid`
JOIN `Orders` o2 ON `subq`.`cid` = o2.`cid`
JOIN `Books` b ON o2.`bid` = b.`bid`
WHERE b.`year` = 1990
GROUP BY c.`cname`;
