USE `computer_products`;

-- Find, for each different price, the average speed of a PC.
SELECT pc.`list_price`, AVG(pc.`speed`) AS avg_speed
FROM (
    SELECT `model`, `speed`, `list_price`
    FROM `Desktop`
    UNION ALL
    SELECT `model`, `speed`, `list_price`
    FROM `Laptop`
) pc
INNER JOIN `Product` p ON pc.`model` = p.`model`
GROUP BY pc.`list_price`;

-- +------------+-----------+
-- | list_price | avg_speed |
-- +------------+-----------+
-- |        396 |       3.4 |
-- |        630 |       4.4 |
-- |        730 |       4.4 |
-- |        900 |       4.9 |
-- |        963 |       4.6 |
-- |       1130 |       2.1 |
-- |       1266 |       3.3 |
-- |       1550 |       5.2 |
-- |       6633 |       5.8 |
-- +------------+-----------+
