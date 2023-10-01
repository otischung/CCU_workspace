USE `donation_record`;

SELECT `government`.`name`
FROM `government`, `donation`
WHERE
    `government`.`name` = `donation`.`name`
    AND (
        `rank` = 'minister'
        OR
        `amount` >= 100000
    );

-- Empty set
