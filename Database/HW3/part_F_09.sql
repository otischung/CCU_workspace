USE `booking_record`;

-- Find the title(s) of the book(s) that were
-- ordered from every zipcode present in the customers table.
SELECT b.`btitle`
FROM `Books` b
JOIN `Orders` o ON b.`bid` = o.`bid`
JOIN `Customers` c ON o.`cid` = c.`cid`
JOIN (
    SELECT c.`zipcode`, COUNT(DISTINCT b.`bid`) AS `book_count`
    FROM `Customers` c
    JOIN `Orders` o ON c.`cid` = o.`cid`
    JOIN `Books` b ON o.`bid` = b.`bid`
    GROUP BY c.`zipcode`
) AS `subq` ON c.`zipcode` = `subq`.`zipcode`
GROUP BY b.`bid`
HAVING COUNT(DISTINCT c.`zipcode`) =
    (SELECT COUNT(DISTINCT `zipcode`) FROM `Customers`);
