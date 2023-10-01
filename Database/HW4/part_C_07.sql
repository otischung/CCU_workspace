USE `course_2`;

-- Find the name(s) of students(s) who have the highest GPA
-- (assume the GPA is computed only based on grades available in Enrolled).
SELECT s.`sname`
FROM (
    SELECT *, `weight_sum_grade` / `cnt_courses` AS `GPA`
    FROM (
        SELECT r.`sid`, SUM(r.`weight_grade`) AS `weight_sum_grade`,
        COUNT(r.`sid`) AS `cnt_courses`
        FROM (
            SELECT e.`sid`, e.`grade` * c.`credits` AS `weight_grade`
            FROM `Enrolled` e
            INNER JOIN `Courses` c ON e.`cid` = c.`cid`
        ) AS r
        GROUP BY r.`sid`
    ) AS r2
) AS r3
INNER JOIN `Students` s ON r3.`sid` = s.`sid`
WHERE r3.`GPA` = (
    SELECT MAX(r6.`GPA`)
    FROM (
        SELECT *, `weight_sum_grade` / `cnt_courses` AS `GPA`
        FROM (
            SELECT r4.`sid`, SUM(r4.`weight_grade`) AS `weight_sum_grade`,
            COUNT(r4.`sid`) AS `cnt_courses`
            FROM (
                SELECT e2.`sid`, e2.`grade` * c2.`credits` AS `weight_grade`
                FROM `Enrolled` e2
                INNER JOIN `Courses` c2 ON e2.`cid` = c2.`cid`
            ) AS r4
            GROUP BY r4.`sid`
        ) AS r5
    ) AS r6
);
