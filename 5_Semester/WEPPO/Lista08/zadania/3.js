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

async function fetchAll() {
  let result = await client.query('SELECT * FROM Person');
  console.log(result.rows);
};

async function insertPerson(person) {
  let result = await client.query(`
  INSERT INTO Person (name, surname, sex, birthday)
  VALUES ($1, $2, $3, $4)
  RETURNING id `,
    [person.name, person.surname, person.sex, person.birthday]);

  console.log("person added to db, with id: " + result.rows[0].id);
};

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
    await fetchAll();
    await insertPerson({
      name: "Robert",
      surname: "Lewandowski",
      sex: 'm',
      birthday: '1988-08-21'
    });

    await updatePerson();
    await deletePerson();
  }
  catch (err) {
    console.log(err);
  }

})();