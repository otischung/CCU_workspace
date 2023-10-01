USE `company`;

-- If a manager manages more than one department, he or she “controls” the
-- sum of all the budgets for those departments. Find the “managerids” of
-- managers who control more than $5 million.
SELECT e.`ename`
FROM (
    SELECT d.`managerid`, SUM(d.`budget`) AS `tot_budget`
    FROM `Dept` d
    GROUP BY d.`managerid`
) AS `result`
INNER JOIN `Emp` e ON `result`.`managerid` = e.`eid`
WHERE `result`.`tot_budget` > 5000000;
