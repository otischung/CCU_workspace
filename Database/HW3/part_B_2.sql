USE `school_organization`;

SELECT c1.`profname`
FROM `committee` c1
WHERE NOT EXISTS (
    SELECT c2.`commname`
    FROM `committee` c2
    WHERE c2.`profname` = 'Piper'
    AND NOT EXISTS (
        SELECT c3.`commname`
        FROM `committee` c3
        WHERE c3.`profname` = c1.`profname`
        AND c3.`commname` = c2.`commname`
    )
)
AND c1.`profname` != 'Piper'
GROUP BY c1.`profname`;

-- +----------+
-- | profname |
-- +----------+
-- | James    |
-- | Lewis    |
-- +----------+
