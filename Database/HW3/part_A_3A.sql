USE `donation_record`;

SELECT `name`
FROM `government`
WHERE `rank` = 'minister'
UNION
SELECT `name`
FROM `donation`
WHERE `amount` >= 100000;

-- +---------+
-- | name    |
-- +---------+
-- | Albert  |
-- | Charlie |
-- +---------+
