USE `company`;

-- Print the names of each employee whose salary exceeds the budget of
-- all of the departments that he or she works in.

SELECT e.`ename`
FROM `Emp` e
INNER JOIN `Works` w ON e.`eid` = w.`eid`
INNER JOIN `Dept` d ON w.`did` = d.`did`
WHERE e.`salary` > ALL (
    SELECT d2.`budget`
    FROM `Works` w2
    JOIN `Dept` d2 ON w2.`did` = d2.`did`
    WHERE w2.`eid` = e.`eid`
);
