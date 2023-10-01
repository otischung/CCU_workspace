USE `computer_products`;

-- Using 2 insert statements, insert the following data in the DB:
-- desktop PC model 1500 is made by Acer, has speed 3.1, RAM 2048, HD 300, and sells for $799.
INSERT INTO `Computer` (`model`) VALUES
    ('1500');

INSERT INTO `Desktop` (`model`, `speed`, `ram`, `hd`, `list_price`) VALUES
    ('1500', 3.1, 2048, 300, 799);

INSERT INTO `Product` (`manu_name`, `model`, `style`) VALUES
    ('ACER', '1500', 'N/A');
