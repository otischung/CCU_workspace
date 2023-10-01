USE `computer_products`;

-- Find the average price of desktop and laptops made by DELL.
SELECT AVG(`price`) AS `avg_price`
FROM (
    SELECT d.`list_price` AS `price`
    FROM `Product` p
    INNER JOIN `Desktop` d ON p.`model` = d.`model`
    INNER JOIN `Manufacturer` m ON p.`manu_name` = m.`name`
    WHERE m.`name` = 'DELL'
    UNION ALL
    SELECT l.`list_price` AS `price`
    FROM `Product` p
    INNER JOIN `Laptop` l ON p.`model` = l.`model`
    INNER JOIN `Manufacturer` m ON p.`manu_name` = m.`name`
    WHERE m.`name` = 'DELL'
) AS `subquery`;


-- +-----------+
-- | avg_price |
-- +-----------+
-- |      1144 |
-- +-----------+
