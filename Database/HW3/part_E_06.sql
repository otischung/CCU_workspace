USE `computer_products`;

-- Find for each manufacturer that makes desktop the maximum speed of a desktop.
SELECT m.`name`, MAX(d.`speed`) AS max_speed
FROM `Manufacturer` m
INNER JOIN `Product` p ON m.`name` = p.`manu_name`
INNER JOIN `Desktop` d ON p.`model` = d.`model`
GROUP BY m.`name`;

-- +------+-----------+
-- | name | max_speed |
-- +------+-----------+
-- | ASUS |       4.9 |
-- | DELL |       5.2 |
-- | MSI  |       5.8 |
-- +------+-----------+
