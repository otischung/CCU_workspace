USE `recipes`;

-- Delete all rows for every tables.
DELETE FROM `Dishes`;
DELETE FROM `Ingredients`;
DELETE FROM `Recipes`;

-- These are from sample data.
INSERT INTO `Dishes`(`did`, `dname`, `origin`, `popularity`) VALUES
    (1, 'Spaghetti', 'Italy',        8),
    (2, 'Sushi',     'Japan',        9),
    (3, 'Tacos',     'Mexico',       7),
    (4, 'Paella',    'Spain',        6),
    (5, 'Pad Thai',  'Thailand',     8),
    (6, 'Burger',    'USA',      10001);

INSERT INTO `Ingredients`(`iid`, `iname`, `unitprice`) VALUES
    ( 1, 'Pasta',     2),
    ( 2, 'Tomatoes',  3),
    ( 3, 'saffron',  50),
    ( 4, 'Rice',      1),
    ( 5, 'sugar',     4),
    ( 6, 'butter',    6),
    ( 7, 'Beef',     55),
    ( 8, 'Chicken',   7),
    ( 9, 'starch',    4),
    (10, 'Potatoes',  2);

INSERT INTO `Recipes`(`did`, `iid`, `quantity`) VALUES
    (1, 1, 200),
    (1, 2,  50),
    (1, 3, 100),
    (2, 5,  10),
    (2, 6,  20),
    (3, 2,  30),
    (3, 8,  50),
    (4, 4, 100),
    (5, 1, 150),
    (5, 2,  30),
    (5, 9,  50),
    (6, 7,  50);
