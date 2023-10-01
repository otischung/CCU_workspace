USE `donation_record`;

SELECT `name`
FROM `donation` A
WHERE NOT EXISTS (
    SELECT *
    FROM `donation` B
    WHERE `name` = 'Campbell'
    AND NOT EXISTS (
        SELECT *
        FROM `donation` C
        WHERE C.`organization` = B.`organization`
        AND C.`name` = A.`name`
    )
);

-- +----------+
-- | name     |
-- +----------+
-- | Campbell |
-- | Campbell |
-- | Charlie  |
-- | Charlie  |
-- | Charlie  |
-- +----------+
