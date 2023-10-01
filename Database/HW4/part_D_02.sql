USE `recipes`;

-- Find the ingredient names that cost at least $10
-- per unit and that appear in at least one dish with
-- popularity higher than 10,000.
SELECT `Result`.`iname`
FROM (
    SELECT DISTINCT i.`iid`, i.`iname`
    FROM `Ingredients` i
    INNER JOIN `Recipes` r ON i.`iid` = r.`iid`
    INNER JOIN `Dishes` d ON r.`did` = d.`did`
    WHERE i.`unitprice` >= 10
    AND d.`popularity` > 10000
) AS `Result`;
