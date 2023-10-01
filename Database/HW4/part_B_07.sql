USE `company`;

-- Find the “managerids” of managers who control the largest amounts.
SELECT e.`ename`
FROM (
    SELECT d.`managerid`, SUM(d.`budget`) AS `tot_budget`
    FROM `Dept` d
    GROUP BY d.`managerid`
) AS `result`
INNER JOIN `Emp` e ON `result`.`managerid` = e.`eid`
WHERE `result`.`tot_budget` = (
    SELECT MAX(`result2`.`tot_budget`)
    FROM (
        SELECT d2.`managerid`, SUM(d2.`budget`) AS `tot_budget`
        FROM `Dept` d2
        GROUP BY d2.`managerid`
    ) AS `result2`
);
