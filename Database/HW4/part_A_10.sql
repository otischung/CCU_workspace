USE `courses`;

-- Is there any “straight A” student?
SELECT DISTINCT s.`PID`, s.`Name`
FROM `Students` s
INNER JOIN `Take` t ON s.`PID` = t.`StudentPID`
WHERE EXISTS (
    SELECT *
    FROM `Take` t1
    WHERE t.`StudentPID` = t1.`StudentPID` AND NOT EXISTS (
        SELECT *
        FROM `Take` t2
        WHERE t2.`StudentPID` = s.`PID` AND t2.`Grade` <> 'A'
    )
);
