-- Delete all rows for every tables.
DELETE FROM `computer_products`.`Manufacturer`;
DELETE FROM `computer_products`.`Computer`;
DELETE FROM `computer_products`.`Desktop`;
DELETE FROM `computer_products`.`Laptop`;
DELETE FROM `computer_products`.`Product`;

LOAD DATA LOCAL INFILE
'/home/otischung/DATA/workspace/CCU_private_workspace/Database/HW3/samples/戊/Manufacturer.csv'
INTO TABLE computer_products.Manufacturer
FIELDS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;

LOAD DATA LOCAL INFILE
'/home/otischung/DATA/workspace/CCU_private_workspace/Database/HW3/samples/戊/Computer.csv'
INTO TABLE computer_products.Computer
FIELDS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;

LOAD DATA LOCAL INFILE
'/home/otischung/DATA/workspace/CCU_private_workspace/Database/HW3/samples/戊/Desktop.csv'
INTO TABLE computer_products.Desktop
FIELDS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;

LOAD DATA LOCAL INFILE
'/home/otischung/DATA/workspace/CCU_private_workspace/Database/HW3/samples/戊/Laptop.csv'
INTO TABLE computer_products.Laptop
FIELDS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;

LOAD DATA LOCAL INFILE
'/home/otischung/DATA/workspace/CCU_private_workspace/Database/HW3/samples/戊/Product.csv'
INTO TABLE computer_products.Product
FIELDS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;
