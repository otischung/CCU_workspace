USE `courses`;

-- What are the names and address of the students who are taking “CS186”?
SELECT s.`PID`, s.`Name`, s.`Address`
FROM `Students` s
INNER JOIN `Take` t ON s.`PID` = t.`StudentPID`
WHERE t.`Number` = 186 AND t.`DeptName` = 'CS';
