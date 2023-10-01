USE `course_2`;

-- Find the ages of students who got grade 10 in a course named 'Databases'.
SELECT s.`age`
FROM `Students` s
INNER JOIN `Enrolled` e ON s.`sid` = e.`sid`
INNER JOIN `Courses` c ON e.`cid` = c.`cid`
WHERE e.`grade` = 10 AND c.`cname` = 'Databases';
