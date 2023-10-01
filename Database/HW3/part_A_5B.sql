USE `donation_record`;

SELECT `politician`.`name`
FROM `politician`, `government`
WHERE NOT `politician`.`name` = `government`.`name`;

-- +---------+
-- | name    |
-- +---------+
-- | Charlie |
-- | Mike    |
-- | Albert  |
-- | Charlie |
-- | Mike    |
-- | Albert  |
-- | Charlie |
-- | Mike    |
-- | Albert  |
-- | Charlie |
-- +---------+
