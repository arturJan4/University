-- testing db
-- sudo -iu postgres -> change user to postgres
-- sudo -u postgres psql -> login to psql

CREATE DATABASE todo_db;

-- \c into todo_db;

-- defining schema
-- \dt, \du
-- \l -> list db's

CREATE TABLE todo(
  todo_id SERIAL PRIMARY KEY,
  description VARCHAR(255)
);