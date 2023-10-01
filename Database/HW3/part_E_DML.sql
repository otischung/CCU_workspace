USE `computer_products`;

-- Delete all rows for every tables.
DELETE FROM `Manufacturer`;
DELETE FROM `Computer`;
DELETE FROM `Desktop`;
DELETE FROM `Laptop`;
DELETE FROM `Product`;

-- Insert rows to tables
INSERT INTO `Manufacturer` (`name`, `country`, `phone`) VALUES
    ('ASUS',    'Taiwan R.O.C', '+886-0800-093-456'),
    ('ACER',    'Taiwan R.O.C', '+886-0800-258-222'),
    ('MSI',     'Taiwan R.O.C', '+886-0800-018-880'),
    ('GIGABYTE','Taiwan R.O.C', '+886-2-8912-4000'),
    ('LENOVO',  'China',        '+886-0800-000-702'),
    ('DELL',    'U.S.A',        '+886-0080-1861-015'),
    ('RAZER',   'Singapore',    '+886-2-2793-1520'),
    ('FUJITSU', 'Japan',        '+886-2-2788-8099#2'),
    ('HP',      'U.S.A',        '+886-0800-010-055'),
    ('APPLE',   'U.S.A',        '+886-0800-020-021'),
    ('TOSHIBA', 'Japan',        '+886-0800-278-000');

INSERT INTO `Computer` (`model`) VALUES
    ('H-S500SD-71270015W'),
    ('H-S501MD-51240F022W'),
    ('H-S700TA-51040F0010'),
    ('H-S500SD-0G6900011W'),
    ('MAG Trident S 5M'),
    ('MEG, Trident X2 13NUI'),
    ('V3020T-R1308STW'),
    ('V3020T-R3718STW'),
    ('13-5320-R1808STW'),
    ('G15-5525-R1848ATW');

INSERT INTO `Desktop` (`model`, `speed`, `ram`, `hd`, `list_price`) VALUES
    ('H-S500SD-71270015W',    4.9, 16,  512,  900),  -- ASUS
    ('H-S501MD-51240F022W',   4.4, 8,   1280, 730),  -- ASUS
    ('H-S700TA-51040F0010',   4.3, 8,   512,  630),  -- ASUS
    ('H-S500SD-0G6900011W',   3.4, 4,   1024, 396),  -- ASUS
    ('MAG Trident S 5M',      4.6, 16,  1024, 963),  -- MSI
    ('MEG, Trident X2 13NUI', 5.8, 128, 6144, 6633), -- MSI
    ('V3020T-R1308STW',       4.5, 8,   1280, 630),  -- DELL
    ('V3020T-R3718STW',       5.2, 16,  512,  1550); -- DELL

INSERT INTO `Laptop` (`model`, `speed`, `ram`, `hd`, `screen`, `list_price`) VALUES
    ('13-5320-R1808STW', 2.1, 16, 512, 13.3, 1130), -- DELL
    ('G15-5525-R1848ATW', 3.3, 8, 512, 15.6, 1266); -- DELL

INSERT INTO `Product` (`manu_name`, `model`, `style`) VALUES
    ('ASUS', 'H-S500SD-71270015W',      'Intel i7-12700 12C20T'),
    ('ASUS', 'H-S501MD-51240F022W',     'Intel i5-12400F 6C12T'),
    ('ASUS', 'H-S700TA-51040F0010',     'Intel i5-10400F 6C12T'),
    ('ASUS', 'H-S500SD-0G6900011W',     'Intel Celeron G6900 2C2T'),
    ('MSI',  'MAG Trident S 5M',        'AMD R7-5700G 8C16T'),
    ('MSI',  'MEG, Trident X2 13NUI',   'Intel i9-13900KF 24C32T'),
    ('DELL', 'V3020T-R1308STW',         'Intel i3-13100 4C4T'),
    ('DELL', 'V3020T-R3718STW',         'Intel i7-13700F 16C24T'),
    ('DELL', '13-5320-R1808STW',        'Intel i7-1360P 12C16T'),
    ('DELL', 'G15-5525-R1848ATW',       'AMD R7-6800H 8C16T');
