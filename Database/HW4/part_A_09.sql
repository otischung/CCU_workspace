USE `courses`;

-- Is there any professor whose age is “still alive” and who receives an average evaluation above 2.5?
SELECT p.`PID`, p.`Name`, AVG(ta.`ProfessorEvaluation`) AS `Average_Evaluation`
FROM `Take` ta
INNER JOIN `Teach` te ON ta.`Number` = te.`Number` AND ta.`DeptName` = te.`DeptName`
INNER JOIN `Professors` p ON te.`ProfessorPID` = p.`PID`
WHERE p.`Age` = 'still alive'
GROUP BY p.`PID`;
