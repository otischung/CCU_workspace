USE `donation_record`;

SELECT `name`
FROM `government`
WHERE `salary` >= 100000
UNION
SELECT `name`
FROM `government`
WHERE `salary` < 100000;

-- +--------+
-- | name   |
-- +--------+
-- | Albert |
-- | Bobbie |
-- | Mike   |
-- +--------+
