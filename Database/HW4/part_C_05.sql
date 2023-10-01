USE `course_2`;

-- Find the course identifier cid and the average age over enrolled
-- students who are 20 or older for each course that has at least 50
-- enrolled students (of any age).
SELECT e.`cid`, AVG(s.`age`) AS `students_avg_age`
FROM `Enrolled` e
INNER JOIN `Students` s ON e.`sid` = s.`sid`
GROUP BY e.`cid`
HAVING COUNT(*) >= 50;
