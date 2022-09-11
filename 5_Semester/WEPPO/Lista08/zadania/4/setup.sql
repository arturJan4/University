DROP TABLE    IF EXISTS Person           CASCADE;
DROP SEQUENCE IF EXISTS person_seq       CASCADE;
DROP TABLE    IF EXISTS Workplace        CASCADE;
DROP TABLE    IF EXISTS Workplace_Person CASCADE;

CREATE TABLE Workplace (
  id SERIAL PRIMARY KEY,
  name      VARCHAR     NOT NULL UNIQUE
);

CREATE TABLE Person (
  id SERIAL PRIMARY KEY,          -- surrogate key (automatycznie zwiększająca się kolumna 1->++)
  name      VARCHAR     NOT NULL, -- VARCHAR is the same as NVARCHAR for SQLServer
  surname   VARCHAR     NOT NULL,
  sex       CHAR(1)     NOT NULL, -- 'm' (male) vs 'f' (female)
  birthday  DATE        NOT NULL,
  id_workplace INT,
  CONSTRAINT fk_workplace
    FOREIGN KEY(id_workplace)
      REFERENCES Workplace(id)
      ON DELETE SET NULL
);

INSERT INTO Workplace
  VALUES (DEFAULT, 'Alphabet'),
         (DEFAULT, 'Meta'),
         (DEFAULT, 'Microsoft'),
         (DEFAULT, 'Amazon');


INSERT INTO Person
  VALUES (DEFAULT, 'Adam', 'Kowalski', 'm', '2000-07-21', 1),
         (DEFAULT, 'Andrzej', 'Strzępiński', 'm', '2002-03-25', 2),
         (DEFAULT, 'Agata', 'Krajewska', 'f', '2001-06-05', 3),
         (DEFAULT, 'Olaf', 'Wróblewski', 'm', '1999-04-25', 4),
         (DEFAULT, 'Dawid', 'Krupa', 'm', '1996-02-28', 3),
		     (DEFAULT, 'Ilona', 'Nowakowska', 'f', '1996-12-01', 2);

--SELECT * FROM Person;
--SELECT * FROM Workplace;