USE `company`;

-- Find the “enames” of managers who manage the departments with the largest budgets.
SELECT e.`ename`
FROM `Emp` e
INNER JOIN `Dept` d ON e.`eid` = d.`managerid`
WHERE d.`budget` = (
    SELECT MAX(`budget`)
    FROM `Dept`
);
