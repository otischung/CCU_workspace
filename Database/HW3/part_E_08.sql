USE `computer_products`;

-- Find for each manufacturer, the average speed of its laptops.
SELECT p.`manu_name`, AVG(l.`speed`) AS `avg_speed`
FROM `Product` p
INNER JOIN `Laptop` l ON p.`model` = l.`model`
GROUP BY p.`manu_name`;

-- +-----------+-----------+
-- | manu_name | avg_speed |
-- +-----------+-----------+
-- | DELL      |       2.7 |
-- +-----------+-----------+
