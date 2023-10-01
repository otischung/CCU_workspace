USE `courses`;

-- Is there any department head who teaches a course in another department?
SELECT DISTINCT p.`PID`, p.`Name`
FROM `Professors` p
INNER JOIN `Departments` d ON p.`PID` = d.`ChairmanPID`
INNER JOIN `Teach` t ON p.`PID` = t.`ProfessorPID`
WHERE p.`DepartmentName` <> t.`DeptName`;
