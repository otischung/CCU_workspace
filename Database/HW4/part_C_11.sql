USE `course_2`;

-- Find the names of students who took a course with three
-- credits or who obtained grade 10 in some course.
SELECT `Result`.`sname`
FROM (
    SELECT DISTINCT s.`sid`, s.`sname`
    FROM `Students` s
    INNER JOIN `Enrolled` e ON s.`sid` = e.`sid`
    WHERE e.grade = 10
    UNION
    SELECT DISTINCT s2.`sid`, s2.`sname`
    FROM `Students` s2
    INNER JOIN `Enrolled` e2 ON s2.`sid` = e2.`sid`
    WHERE e2.`cid` IN (
        SELECT c.`cid`
        FROM `Courses` c
        WHERE c.`credits` = 3
    )
) AS `Result`;
