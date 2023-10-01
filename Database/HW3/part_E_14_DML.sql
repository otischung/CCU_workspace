

-- For each laptop made by Dell,
-- add one inch to the screen size and subtract $200 from the price.
UPDATE `Laptop`
SET `screen` = `screen` + 1,
    `list_price` = `list_price` - 200
WHERE `model` IN (
    SELECT `model`
    FROM `Product`
    WHERE `manu_name` = 'DELL'
);
