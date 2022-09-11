const res = require('express/lib/response');
const pg = require('pg');
const { Client } = require('pg');

const client = new Client({
  host: 'localhost',
  port: '5432',
  database: 'weppo8',
  user: 'postgres',
  password: 'root'
});

async function fetchAllPerson() {
  let result = await client.query('SELECT * FROM Person');
  console.log(result.rows);
};

async function fetchAllWorkplace() {
  let result = await client.query('SELECT * FROM Workplace');
  console.log(result.rows);
};

async function insertPerson(person) {
  let result = await client.query(`
  INSERT INTO Person (name, surname, sex, birthday, id_workplace)
  VALUES ($1, $2, $3, $4, $5)
  RETURNING id`,
    [person.name, person.surname, person.sex, person.birthday, person.id_workplace]);

  console.log("person added to db, with id: " + result.rows[0].id);
  return result.rows[0].id;
};

async function insertWorkplace(name) {
  let found = await client.query(`SELECT id FROM Workplace WHERE name = $1`, [name]);

  /* RETURNING returns id only on INSERT statements in Postgres
  let result = await client.query(`
  INSERT INTO Workplace (name)
  VALUES ($1)
  ON CONFLICT (name) DO NOTHING
  RETURNING id`,
    [name]);
  */

  if (found.rows[0]) {
    let existing_id = found.rows[0].id;
    console.log("workplace already exists with id: " + existing_id);
    return existing_id;
  }

  let result = await client.query(`
    INSERT INTO Workplace (name)
    VALUES ($1)
    RETURNING id`,
    [name]);
    
  console.log("workplace added to db, with id: " + result.rows[0].id);
  return result.rows[0].id;
};

async function addPerson(person, workplace_name) {
  let id = await insertWorkplace(workplace_name);
  person["id_workplace"] = id;
  await insertPerson(person);
}

async function updatePerson() {
  client.query(`
    UPDATE Person 
    SET birthday = '1988-08-22'
    WHERE name = 'Robert' AND surname = 'Lewandowski'`,
    (err, res) => {
      if (err != null) {
        console.log("client.query: ", err);
      } else {
        console.log("Total updated rows: ", res.rowCount);
      }
    });
};

async function deletePerson() {
  client.query(`
    DELETE FROM Person
    WHERE ctid IN (
      SELECT ctid
      FROM Person
      WHERE name = 'Robert' AND surname = 'Lewandowski'
      ORDER BY birthday
      LIMIT 2
    )`,
    (err, res) => {
      if (err != null) {
        console.log("client.query: ", err);
      } else {
        console.log("Total deleted rows: ", res.rowCount);
      }
    });
};

(async function main() {
  await client.connect();

  try {
    person = {
      name: "Robert",
      surname: "Lewandowski",
      sex: 'm',
      birthday: '1988-08-21',
    }
    
    await addPerson(person, "Amazon");
    person["name"] = "Marcin"
    await addPerson(person, "Nokia");
  }
  catch (err) {
    console.log(err);
  }

})();