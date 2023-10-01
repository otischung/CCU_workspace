USE `course_2`;

-- Find the names of students who are enrolled in a
-- single course.
SELECT s.`sname`
FROM `Students` s
INNER JOIN (
    SELECT e.`sid`, COUNT(*) AS `cnt_courses`
    FROM `Enrolled` e
    GROUP BY e.`sid`
    HAVING `cnt_courses` = 1
) AS r ON s.`sid` = r.`sid`;
