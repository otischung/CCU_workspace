USE `recipes`;

-- Find the dish names that do NOT contain any of the
-- following ingredients: sugar, butter, starch.
SELECT `Result`.`dname`
FROM (
    SELECT DISTINCT d.`did`, d.`dname`
    FROM `Dishes` d
    INNER JOIN `Recipes` r ON d.`did` = r.`did`
    INNER JOIN `Ingredients` i ON r.`iid` = i.`iid`
    WHERE i.`iname` <> 'sugar'
    AND i.`iname` <> 'butter'
    AND i.`iname` <> 'starch'
) AS `Result`;
