DROP TABLE    IF EXISTS Person           CASCADE;
DROP SEQUENCE IF EXISTS person_seq       CASCADE;
DROP TABLE    IF EXISTS Workplace        CASCADE;
DROP TABLE    IF EXISTS Workplace_Person CASCADE;

CREATE TABLE Workplace (
  workplace_id 	 SERIAL  PRIMARY KEY,
  workplace_name VARCHAR NOT NULL UNIQUE
);

CREATE TABLE Person (
  person_id   SERIAL 	    PRIMARY KEY, -- surrogate key (automatycznie zwiększająca się kolumna 1->++)
  person_name VARCHAR     NOT NULL,    -- VARCHAR is the same as NVARCHAR for SQLServer
  surname     VARCHAR     NOT NULL,
  sex         CHAR(1)     NOT NULL,    -- 'm' (male) vs 'f' (female)
  birthday    DATE        NOT NULL
);

CREATE TABLE Workplace_Person (
  workplace_id INT NOT NULL REFERENCES Workplace (workplace_id) ON UPDATE CASCADE ON DELETE SET NULL,
  person_id    INT NOT NULL REFERENCES Person (person_id) ON UPDATE CASCADE,
  CONSTRAINT workplace_person_pkey PRIMARY KEY (workplace_id, person_id)
);

INSERT INTO Workplace
  VALUES (DEFAULT, 'Alphabet'),
         (DEFAULT, 'Meta'),
         (DEFAULT, 'Microsoft'),
         (DEFAULT, 'Amazon');


INSERT INTO Person
  VALUES (DEFAULT, 'Adam', 'Kowalski', 'm', '2000-07-21'),
         (DEFAULT, 'Andrzej', 'Strzępiński', 'm', '2002-03-25'),
         (DEFAULT, 'Agata', 'Krajewska', 'f', '2001-06-05'),
         (DEFAULT, 'Olaf', 'Wróblewski', 'm', '1999-04-25'),
         (DEFAULT, 'Dawid', 'Krupa', 'm', '1996-02-28'),
		     (DEFAULT, 'Ilona', 'Nowakowska', 'f', '1996-12-01');

--SELECT * FROM Person;
--SELECT * FROM Workplace;