USE `company`;

-- Find the “managerids” of managers who manage only departments with
-- budgets greater than $1 million.
SELECT DISTINCT d.`managerid`
FROM `Dept` d
WHERE d.`budget` > 1000000
AND NOT EXISTS (
    SELECT 1
    FROM `Dept` d2
    WHERE d2.`managerid` = d.`managerid`
    AND d2.`budget` <= 1000000
);
