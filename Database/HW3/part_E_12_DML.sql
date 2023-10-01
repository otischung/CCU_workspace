USE `computer_products`;

-- Delete all laptops made by a manufacturer that does not make desktop PCs.
DELETE FROM `Laptop`
WHERE `model` IN (
    SELECT p.`model`
    FROM `Product` p
    INNER JOIN `Desktop` l ON p.`model` = l.`model`
    WHERE p.`manu_name` NOT IN (
        SELECT DISTINCT `name`
        FROM `Manufacturer` m
        INNER JOIN `Product` p2 ON m.`name` = p2.`manu_name`
    )
);
