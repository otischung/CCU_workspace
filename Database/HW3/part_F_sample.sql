-- Delete all rows for every tables.
DELETE FROM `booking_record`.`Books`;
DELETE FROM `booking_record`.`Customers`;
DELETE FROM `booking_record`.`Orders`;

LOAD DATA LOCAL INFILE
'/home/otischung/DATA/workspace/CCU_private_workspace/Database/HW3/samples/己/Books.csv'
INTO TABLE booking_record.Books
FIELDS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;

LOAD DATA LOCAL INFILE
'/home/otischung/DATA/workspace/CCU_private_workspace/Database/HW3/samples/己/Customers.csv'
INTO TABLE booking_record.Customers
FIELDS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;

LOAD DATA LOCAL INFILE
'/home/otischung/DATA/workspace/CCU_private_workspace/Database/HW3/samples/己/Orders.csv'
INTO TABLE booking_record.Orders
FIELDS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;
