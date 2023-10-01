USE `recipes`;

-- Find the name and unit price of rare ingredients,
-- i.e., those that appear in a single dish.
SELECT i.`iname`, i.`unitprice`
FROM `Ingredients` i
INNER JOIN (
    SELECT r.`iid`, COUNT(*) AS `cnt_dishes`
    FROM `Recipes` r
    GROUP BY r.`iid`
    HAVING `cnt_dishes` = 1
) AS `Result` ON i.`iid` = `Result`.`iid`;
