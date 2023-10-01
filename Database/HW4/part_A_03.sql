USE `courses`;

-- Which department have course that have pre-requisites in other departments?
SELECT DISTINCT d.`Name` AS 'Department Name'
FROM `Departments` d
INNER JOIN `Courses` c ON d.`Name` = c.`DeptName`
INNER JOIN `PreReq` p ON c.`Number` = p.`Number` AND c.`DeptName` = p.`DeptName`
INNER JOIN `Departments` dp ON p.`PreReqDeptName` = dp.`Name`
WHERE dp.`Name` <> d.`Name`;
