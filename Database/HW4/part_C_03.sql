USE `course_2`;

-- Find the ages of students who take only courses with less than
-- four credits (implies they take at least one course).
SELECT `Result`.`age`
FROM (
    SELECT DISTINCT s.`sid`, s.`age`
    FROM `Students` s
    INNER JOIN `Enrolled` e ON s.`sid` = e.`sid`
    WHERE e.`cid` IN (
        SELECT e2.`cid`
        FROM `Enrolled` e2
    ) AND s.`sid` NOT IN (
        SELECT e3.`sid`
        FROM `Enrolled` e3
        INNER JOIN `Courses` c ON e3.`cid` = c.`cid`
        WHERE c.`credits` >= 4
    )
) AS `Result`;
