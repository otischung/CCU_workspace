USE `company`;

-- For each department with more than 20 full-time-equivalent employees
-- (i.e., where the part-time and full-time employees add up to at least
-- that many full-time employees), print the “did” together with the number
-- of employees that work in that department.
SELECT `Result`.`did`, `Result`.`num_emp`
FROM (
    SELECT w.`did`, SUM(w.`pct_time`) AS `sum_time`, COUNT(*) AS `num_emp`
    FROM `Works` w
    GROUP BY w.`did`
) AS `Result`
WHERE `Result`.`sum_time` > 20;
