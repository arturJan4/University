DROP TABLE    IF EXISTS Person           CASCADE;
DROP SEQUENCE IF EXISTS person_seq       CASCADE;
DROP TABLE    IF EXISTS Workplace        CASCADE;
DROP TABLE    IF EXISTS Workplace_Person CASCADE;

CREATE SEQUENCE person_seq
  AS INT
  START WITH 1
  INCREMENT BY 1;

CREATE TABLE Person (
  id INTEGER PRIMARY KEY,
  name       VARCHAR     NOT NULL, -- VARCHAR is the same as NVARCHAR for SQLServer
  surname    VARCHAR     NOT NULL,
  sex        CHAR(1)     NOT NULL, -- 'm' (male) vs 'f' (female)
  birthday   DATE        NOT NULL
);

INSERT INTO Person
  VALUES (nextval('person_seq'), 'Adam', 'Kowalski', 'm', '2000-07-21'),
         (nextval('person_seq'), 'Andrzej', 'Strzępiński', 'm', '2002-03-25'),
         (nextval('person_seq'), 'Agata', 'Krajewska', 'f', '2001-06-05'),
         (nextval('person_seq'), 'Olaf', 'Wróblewski', 'm', '1999-04-25'),
         (nextval('person_seq'), 'Dawid', 'Krupa', 'm', '1996-02-28'),
         (nextval('person_seq'), 'Ilona', 'Cieślak', 'f', '1995-12-01'),
		     (nextval('person_seq'), 'Ilona', 'Nowakowska', 'f', '1996-12-01');

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