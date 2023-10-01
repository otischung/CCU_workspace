USE `donation_record`;

SELECT `name`
FROM `politician`
WHERE `name` NOT IN (
    SELECT `name`
    FROM `government`
);

-- +---------+
-- | name    |
-- +---------+
-- | Charlie |
-- +---------+
