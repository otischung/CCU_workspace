USE `booking_record`;

-- Find the authors of books for which there are at least two orders placed.
SELECT `author`
FROM `Books`
JOIN `Orders` ON `Books`.`bid` = `Orders`.`bid`
GROUP BY `author`
HAVING COUNT(DISTINCT `Orders`.`cid`) >= 2;
