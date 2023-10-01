USE `computer_products`;

-- Find the average price of laptops with a speed of at least 3.0.
SELECT AVG(`list_price`) AS `avg_price`
FROM `Laptop`
WHERE `speed` >= 3.0;

-- +-----------+
-- | avg_price |
-- +-----------+
-- |      1266 |
-- +-----------+
