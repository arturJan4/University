DROP TABLE    IF EXISTS Person           CASCADE;
DROP SEQUENCE IF EXISTS person_seq       CASCADE;
DROP TABLE    IF EXISTS Workplace        CASCADE;
DROP TABLE    IF EXISTS Workplace_Person CASCADE;

CREATE TABLE Person (
  id SERIAL PRIMARY KEY,          -- surrogate key (automatycznie zwiększająca się kolumna 1->++)
  name      VARCHAR     NOT NULL, -- VARCHAR is the same as NVARCHAR for SQLServer
  surname   VARCHAR     NOT NULL,
  sex       CHAR(1)     NOT NULL, -- 'm' (male) vs 'f' (female)
  birthday  DATE        NOT NULL
);

INSERT INTO Person
  VALUES (DEFAULT, 'Adam', 'Kowalski', 'm', '2000-07-21'),
         (DEFAULT, 'Andrzej', 'Strzępiński', 'm', '2002-03-25'),
         (DEFAULT, 'Agata', 'Krajewska', 'f', '2001-06-05'),
         (DEFAULT, 'Olaf', 'Wróblewski', 'm', '1999-04-25'),
         (DEFAULT, 'Dawid', 'Krupa', 'm', '1996-02-28'),
		     (DEFAULT, 'Ilona', 'Nowakowska', 'f', '1996-12-01');

SELECT * FROM Person;

-- SELECT surname FROM Person;
-- SELECT * FROM Person WHERE sex = 'f';
-- SELECT (name, surname) FROM Person WHERE sex = 'f';
-- SELECT DISTINCT name FROM Person WHERE sex = 'f';
-- SELECT * FROM Person WHERE like(surname, 'K%');
-- SELECT * FROM Person WHERE like(surname, 'K%') AND sex = 'm';
-- SELECT COUNT(*) FROM Person
/*
SELECT name, birthday 
FROM Person 
GROUP BY name, birthday 
ORDER BY birthday ASC
*/