USE `computer_products`;

-- Find the average HD size of the Desktop PCs.
SELECT AVG(`hd`) AS `avg_hd_size`
FROM `Desktop`;

-- +-------------+
-- | avg_hd_size |
-- +-------------+
-- |   1536.0000 |
-- +-------------+
