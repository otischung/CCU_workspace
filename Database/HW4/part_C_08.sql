USE `course_2`;

-- Find the ages of students who take some course with 3 credits.
SELECT `Result`.`age`
FROM (
    SELECT DISTINCT s.`sid`, s.`age`
    FROM `Students` s
    INNER JOIN `Enrolled` e ON s.`sid` = e.`sid`
    WHERE e.`cid` IN (
        SELECT c.`cid`
        FROM `Courses` c
        WHERE c.`credits` = 3
    )
) AS `Result`;
