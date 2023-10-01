USE DATABASE `library`;

-- The total number of books held at each branch.
SELECT b.`Librarian`, SUM(`Holdings`.`copies`) AS `Total Books`
FROM `Branch` b
JOIN `Holdings` ON b.`bcode` = `Holdings`.`branch`
GROUP BY b.`bcode`;

-- +------------+-------------+
-- | Librarian  | Total Books |
-- +------------+-------------+
-- | John Smith |           6 |
-- | Mary Jones |           9 |
-- | Francis    |           9 |
-- +------------+-------------+
