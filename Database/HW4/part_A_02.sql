USE `courses`;

-- Which pairs of students live at the same address? It is enough to return the names of such students pairs.
SELECT s1.`PID`, s1.`Name`, s2.`PID`, s2.`Name`
FROM `Students` s1
INNER JOIN `Students` s2 ON s1.`Address` = s2.`Address`
WHERE s1.`PID` < s2.`PID`;
