USE `booking_record`;

-- Find the titles of books that were ordered only in quantities of at least 100.
SELECT b.`btitle`
FROM `Books` b
INNER JOIN `Orders` o ON b.`bid` = o.`bid`
GROUP BY o.`bid`
HAVING SUM(o.`quantity`) >= 100
-- AND MAX(o.`quantity`) < 100
;
