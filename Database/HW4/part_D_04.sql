USE `recipes`;

-- List the popularity of “exclusive” dishes, defined as
-- dishes that contain only ingredients costing at least
-- $50 per unit.
SELECT `Result`.`popularity`
FROM (
    SELECT d.`did`, d.`popularity`
    FROM `Dishes` d
    WHERE NOT EXISTS (
        SELECT 1
        FROM `Recipes` r
        WHERE d.`did` = r.`did`
        AND EXISTS (
            SELECT 1
            FROM `Ingredients` i
            WHERE r.`iid` = i.`iid`
            AND i.`unitprice` < 50
        )
    )
) AS `Result`;
