USE `school_organization`;

SELECT DISTINCT c1.`profname`
FROM `committee` c1
JOIN `committee` c2
ON c1.`commname` = c2.`commname`
WHERE c2.`profname` = 'Piper'
AND c1.`profname` != 'Piper';

-- +----------+
-- | profname |
-- +----------+
-- | James    |
-- | Lewis    |
-- | Oliver   |
-- | Matthew  |
-- +----------+
