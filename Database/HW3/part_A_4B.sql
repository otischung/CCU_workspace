USE `donation_record`;

SELECT `name`
FROM `politician`
WHERE NOT EXISTS (
    SELECT *
    FROM `government`
    WHERE `government`.`name` = `politician`.`name`
);

-- +---------+
-- | name    |
-- +---------+
-- | Charlie |
-- +---------+
