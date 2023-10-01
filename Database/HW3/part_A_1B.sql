USE `donation_record`;

SELECT `name`
FROM `donation` A
WHERE NOT EXISTS (
    SELECT *
    FROM `donation`
    WHERE `name` = 'Campbell'
    AND `organization` NOT IN (
        SELECT `organization`
        FROM `donation` B
        WHERE B.`name` = A.`name`
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
