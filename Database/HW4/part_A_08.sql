USE `courses`;

-- Are there any students who are taking at least two courses taught by department heads?
SELECT `Result`.`PID`, `Result`.`Name`
FROM (
    SELECT s.`PID`, s.`Name`, COUNT(*) AS `Amount`
    FROM `Students` s
    INNER JOIN `Take` t ON s.`PID` = t.`StudentPID`
    INNER JOIN `Teach` te ON t.`Number` = te.`Number` AND t.`DeptName` = te.`DeptName`
    INNER JOIN `Departments` d ON te.`ProfessorPID` = d.`ChairmanPID`
    GROUP BY s.`PID`
) AS `Result`
WHERE `Result`.`Amount` >= 2;
