USE `computer_products`;

-- Find the for each speed of desktop PC above 2.5, the average hard-disk size.
SELECT `speed`, AVG(`hd`) AS `avg_hard_disk`
FROM `Desktop`
WHERE `speed` > 2.5
GROUP BY `speed`;
