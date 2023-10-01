USE `computer_products`;

-- Delete all desktop PCs with less than 400GB of HD.
DELETE FROM `Desktop` 
WHERE `hd` < 400;
