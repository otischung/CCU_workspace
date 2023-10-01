USE `computer_products`;

-- Check it.
SELECT * FROM `Desktop`;

-- For each PC, double the amount of HD and add 2048 to the amount of RAM.
UPDATE `Desktop`
SET `hd` = `hd` * 2,
    `ram` = `ram` + 2048;

-- Check it.
SELECT * FROM `Desktop`;
