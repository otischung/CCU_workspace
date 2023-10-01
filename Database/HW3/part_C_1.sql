USE DATABASE `library`;

-- The names of all library books published by Macmillan.
SELECT DISTINCT `title`
FROM `Titles`
WHERE `Publisher` = 'Macmillan';

-- +----------+
-- | title    |
-- +----------+
-- | Susannah |
-- | The Wife |
-- +----------+
