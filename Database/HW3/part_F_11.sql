USE `booking_record`;

-- Find the zipcode(s) that generated the highest revenue for the store
-- (i.e., the largest combined dollar amount for orders originating in
-- that zipcode).
SELECT c.`zipcode`, SUM(b.`price` * o.`quantity`) AS `total_revenue`
FROM `Customers` c
JOIN `Orders` o ON c.`cid` = o.`cid`
JOIN `Books` b ON o.`bid` = b.`bid`
GROUP BY c.`zipcode`
ORDER BY `total_revenue` DESC
LIMIT 1;
