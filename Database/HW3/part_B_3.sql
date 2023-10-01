USE `school_organization`;

SELECT DISTINCT p.`profname`
FROM `professor` p
JOIN `department` d ON p.`deptname` = d.`deptname`
WHERE d.`building` NOT IN (
    SELECT d.`building`
    FROM `professor` p
    JOIN `department` d ON p.`deptname` = d.`deptname`
    WHERE p.`profname` = 'Piper'
);

-- +----------+
-- | profname |
-- +----------+
-- | Lewis    |
-- | Matthew  |
-- | Oliver   |
-- | William  |
-- +----------+
