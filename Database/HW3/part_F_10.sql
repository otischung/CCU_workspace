USE `booking_record`;

-- Find the total dollar amount of purchases for every customer in
-- zipcode 02125; list customer name in the output along with the amount.
SELECT c.`cname`, SUM(b.`price` * o.`quantity`) AS `total_purchase`
FROM `Customers` c
JOIN `Orders` o ON c.`cid` = o.`cid`
JOIN `Books` b ON o.`bid` = b.`bid`
WHERE c.`zipcode` = '02125'
GROUP BY c.`cname`;
