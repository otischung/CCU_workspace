USE `courses`;

-- What are the courses that the head of the CS department is teaching?
SELECT c.`CourseName`
FROM `Teach` t
INNER JOIN `Courses` c ON t.`Number` = c.`Number` AND t.`DeptName` = c.`DeptName`
INNER JOIN `Departments` d ON t.`DeptName` = d.`Name`
LEFT JOIN `Professors` p ON d.`ChairmanPID` = p.`PID`
WHERE t.`DeptName` = 'CS' AND p.`PID` IS NOT NULL AND d.`ChairmanPID` = p.`PID`;
