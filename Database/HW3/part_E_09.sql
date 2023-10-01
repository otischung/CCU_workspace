USE `computer_products`;

-- Find the average hard-disk size of a desktop PC for all those manufacturers that make laptops.
SELECT p.`manu_name`, AVG(d.`hd`)
FROM `Desktop` d
INNER JOIN `Product` p ON d.`model` = p.`model`
WHERE p.`manu_name` IN (
    SELECT DISTINCT p2.`manu_name`
    FROM `Product` p2
    INNER JOIN `Laptop` l ON p2.`model` = l.`model`
);
