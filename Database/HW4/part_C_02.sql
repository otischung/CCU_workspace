USE `course_2`;

-- Find the name(s) of students(s) with the youngest age.
SELECT s.`sname`
FROM `Students` s
WHERE s.`age` = (
    SELECT MIN(s2.`age`)
    FROM `Students` s2
);
