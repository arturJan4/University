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
  INSERT INTO Person (person_name, surname, sex, birthday)
  VALUES ($1, $2, $3, $4)
  RETURNING person_id`,
    [person.name, person.surname, person.sex, person.birthday]);

  console.log("person added to db, with id: " + result.rows[0].person_id);
  return result.rows[0].person_id;
};

async function insertWorkplace(name) {
  let found = await client.query(`SELECT workplace_id FROM Workplace WHERE workplace_name = $1`, [name]);

  if (found.rows[0]) {
    let existing_id = found.rows[0].workplace_id;
    console.log("workplace already exists with id: " + existing_id);
    return existing_id;
  }

  let result = await client.query(`
    INSERT INTO Workplace (workplace_name)
    VALUES ($1)
    RETURNING workplace_id`,
    [name]);

  console.log("workplace added to db, with id: " + result.rows[0].workplace_id);
  return result.rows[0].workplace_id;
};

async function assignWorkplace(person_id, workplace_id) {
  client.query(`
    INSERT INTO Workplace_Person(person_id, workplace_id)
    VALUES ($1, $2)`,
    [person_id, workplace_id],
    (err, res) => {
      if (err != null) {
        console.log("client.query: ", err);
      } else {
        console.log('Assigned ' + person_id + ' to ' + workplace_id);
      }
    });
}

async function addPerson(person, workplace_name) {
  let workplace_id = await insertWorkplace(workplace_name);
  let person_id = await insertPerson(person);
  await assignWorkplace(person_id, workplace_id);

  return [person_id, workplace_id];
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
    person = {
      name: "Robert",
      surname: "Lewandowski",
      sex: 'm',
      birthday: '1988-08-21',
    };

    person2 = {
      name: 'Anna',
      surname: 'Nowak',
      sex: 'f',
      birthday: '1995-02-13'
    };

    let [person_id, amazon_id] = await addPerson(person, "Amazon");
    let allegro_id = await insertWorkplace('Allegro');
    let netflix_id = await insertWorkplace('Netflix');

    await assignWorkplace(person_id, allegro_id);
    await assignWorkplace(person_id, netflix_id);

    await addPerson(person2, "Netflix");
  }
  catch (err) {
    console.log(err);
  }
})();