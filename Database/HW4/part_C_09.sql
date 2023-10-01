USE `course_2`;

-- Find the names of students who obtained grade at least 8 in some course
-- that has less than 4 credits.
SELECT `Result`.`sname`
FROM (
    SELECT DISTINCT s.`sid`, s.`sname`
    FROM `Students` s
    INNER JOIN `Enrolled` e ON s.`sid` = e.`sid`
    WHERE e.`cid` IN (
        SELECT c.`cid`
        FROM `Courses` c
        WHERE c.`credits` < 4
    ) AND e.`grade` >= 8
) AS `Result`;
