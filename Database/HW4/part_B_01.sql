USE `company`;

-- Print the names and ages of each employee who
-- works in both the Hardware department and the Software department.
SELECT e.`ename`, e.`age`
FROM `Emp` e
INNER JOIN `Works` w ON e.`eid` = w.`eid`
INNER JOIN `Dept` d ON w.`did` = d.`did`
WHERE d.`dname` = 'Hardware'
INTERSECT
SELECT e.`ename`, e.`age`
FROM `Emp` e
INNER JOIN `Works` w ON e.`eid` = w.`eid`
INNER JOIN `Dept` d ON w.`did` = d.`did`
WHERE d.`dname` = 'Software';
