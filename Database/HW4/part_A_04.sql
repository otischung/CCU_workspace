USE `courses`;

-- Ref: https://dev.mysql.com/blog-archive/mysql-8-0-1-recursive-common-table-expressions-in-mysql-ctes-part-four-depth-first-or-breadth-first-traversal-transitive-closure-cycle-avoidance/
-- Compute the set of all courses that are their own pre-requisites? (have cycles)
WITH RECURSIVE `descendants` AS (
    SELECT p.`DeptName`, p.`Number`, CONCAT(CAST(p.`DeptName` AS CHAR(1000000)), ' ', CAST(p.`Number` AS CHAR(500))) AS `Path`, 0 AS `is_cycle`
    FROM `PreReq` p
    WHERE p.`PreReqNumber` = 54 AND p.`PreReqDeptName` = 'MATH'
    UNION ALL
    SELECT p.`DeptName`, p.`Number`, CONCAT(CAST(p.`DeptName` AS CHAR(1000000)), ' ', CAST(p.`Number` AS CHAR(500))) AS `Path`, 0 AS `is_cycle`
    FROM `PreReq` p
    WHERE p.`PreReqNumber` = 61 AND p.`PreReqDeptName` = 'CS'
    UNION ALL
    SELECT p.`DeptName`, p.`Number`, CONCAT(CAST(p.`DeptName` AS CHAR(1000000)), ' ', CAST(p.`Number` AS CHAR(500))) AS `Path`, 0 AS `is_cycle`
    FROM `PreReq` p
    WHERE p.`PreReqNumber` = 1 AND p.`PreReqDeptName` = 'MATH'
    UNION ALL
    SELECT p.`DeptName`, p.`Number`, CONCAT(CAST(p.`DeptName` AS CHAR(1000000)), ' ', CAST(p.`Number` AS CHAR(500))) AS `Path`, 0 AS `is_cycle`
    FROM `PreReq` p
    WHERE p.`PreReqNumber` = 132 AND p.`PreReqDeptName` = 'ME'
    UNION ALL
    SELECT p2.`DeptName`, p2.`Number`, CONCAT(d.`Path`, ', ', p2.`DeptName`, ' ', p2.`Number`), FIND_IN_SET(CONCAT(p2.`DeptName`, ' ', p2.`Number`), d.`Path`) != 0
    FROM `PreReq` p2, `descendants` d
    WHERE p2.`PreReqNumber` = d.`Number` AND p2.`PreReqDeptName` = d.`DeptName`
    AND `is_cycle` = 0
)
SELECT * FROM `descendants`;
