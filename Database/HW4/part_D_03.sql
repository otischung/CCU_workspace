USE `recipes`;

-- Find the origin of dishes that use at least one unit
-- of an ingredient called ‘saffron’.
SELECT `Result`.`origin`
FROM (
    SELECT DISTINCT d.`did`, d.`origin`
    FROM `Dishes` d
    INNER JOIN `Recipes` r ON d.`did` = r.`did`
    INNER JOIN `Ingredients` i ON r.`iid` = i.`iid`
    WHERE i.`iname` = 'saffron'
    AND r.`quantity` >= 1
) AS `Result`;
