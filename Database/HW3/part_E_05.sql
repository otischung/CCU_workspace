USE `computer_products`;

-- Find the manufacturers that make at least 3 different models of desktop PCs.
SELECT m.`name`
FROM `Manufacturer` m
INNER JOIN `Product` p ON m.`name` = p.`manu_name`
INNER JOIN `Desktop` d ON p.`model` = d.`model`
GROUP BY m.`name`
HAVING COUNT(DISTINCT d.`model`) >= 3;

-- +------+
-- | name |
-- +------+
-- | ASUS |
-- +------+
