USE `course_2`;

-- Find the names of students who obtained only grades of 10
-- (implies that they took at least one course).
SELECT s.`sname`
FROM `Students` s
INNER JOIN `Enrolled` e ON s.`sid` = e.`sid`
WHERE NOT EXISTS (
    SELECT 1
    FROM `Enrolled` e2
    WHERE e.`sid` = e2.`sid`
    AND e2.`grade` <> 10
);
