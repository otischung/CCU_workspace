USE `courses`;

-- Are there any students who are taking courses and receiving more grade A than grade B?
SELECT s.`PID`, s.`Name`, `ResultA`.`Amount_of_A`, `ResultB`.`Amount_of_B`
FROM `Students` s
INNER JOIN (
    SELECT t.`StudentPID`, COUNT(*) AS `Amount_of_A`
    FROM `Take` t
    WHERE t.`Grade` = 'A'
    GROUP BY t.`StudentPID`
) AS `ResultA` ON s.`PID` = `ResultA`.`StudentPID`
LEFT JOIN (
    SELECT t.`StudentPID`, COUNT(*) AS `Amount_of_B`
    FROM `Take` t
    WHERE t.`Grade` = 'B'
    GROUP BY t.`StudentPID`
) AS `ResultB` ON s.`PID` = `ResultB`.`StudentPID`
WHERE `ResultA`.`Amount_of_A` > `ResultB`.`Amount_of_B`
OR (`ResultA`.`Amount_of_A` IS NOT NULL AND `ResultB`.`Amount_of_B` IS NULL);
