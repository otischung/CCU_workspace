USE `company`;

-- Find the “enames” of managers who manage only departments with budgets
-- larger than $1 million, but at least one department with budget less than
-- $5 million.
SELECT DISTINCT e.`ename`
FROM `Emp` e
JOIN `Dept` d ON e.`eid` = d.`managerid`
WHERE d.`budget` > 1000000
AND EXISTS (
    SELECT 1
    FROM `Dept` d2
    WHERE d2.`managerid` = d.`managerid`
    AND d2.`budget` < 5000000
)
AND NOT EXISTS (
    SELECT 1
    FROM `Dept` d3
    WHERE d3.`managerid` = d.`managerid`
    AND d3.`budget` <= 1000000
);
