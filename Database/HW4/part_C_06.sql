USE `course_2`;

-- Find the names of students who take all the four-credit courses
-- offered and obtained at least grade 7 in every such course.
SELECT s.`sname`
FROM `Students` s
INNER JOIN `Enrolled` e ON s.`sid` = e.`sid`
INNER JOIN `Courses` c ON e.`cid` = c.`cid`
WHERE c.`credits` = 4 AND e.`grade` >= 7
GROUP BY s.`sid`
HAVING COUNT(DISTINCT e.`cid`) = (
    SELECT COUNT(*) 
    FROM `Courses` 
    WHERE `credits` = 4
);
