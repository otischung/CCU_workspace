USE DATABASE `library`;

-- Branches that hold any books by Ann Brown.
SELECT DISTINCT b.`librarian`
FROM `Branch` b
JOIN `Holdings` h ON b.`bcode` = h.`branch`
JOIN `Titles` t ON h.`title` = t.`title`
WHERE t.`author` = 'Ann Brown';

-- +------------+
-- | librarian  |
-- +------------+
-- | John Smith |
-- | Mary Jones |
-- | Francis    |
-- +------------+
