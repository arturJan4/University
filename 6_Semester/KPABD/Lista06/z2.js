db.runCommand( {
   collMod: "Ksiazki",
   validator: { $jsonSchema: {
      bsonType: "object",
      required: [ "ISBN", "Tytul", "Autor", "RokWydania" ],
      properties: {
		 ISBN: {
			bsonType: "string",
            description: "is required and must be string"
		 },
         Tytul: {
            bsonType: "string",
            description: "is required and must be string"
         },
         Autor: {
            bsonType: "string",
            description: "is required and must be string"
         },
         RokWydania: {
            bsonType: "int",
			minimum: 0,
			maximum: 2100,
            description: "is required and must be INT"
         },
         Egzemplarze: {
             bsonType: ["array"],
             minItems: 0,
             uniqueItems: true,
             items: {
                bsonType: ["object"],
                required: ["Sygnatura"],
                properties: {
					Sygnatura: {
					bsonType: "string",
					pattern : "@S\\d{4,}$",
					description: "is required and must be string and match regular expression"
                    }
                }
			}
		}
	}
}}})

db.runCommand(
{
    collMod: "Czytelnicy",
    validator: { $jsonSchema: {
        bsonType: "object",
        required: ["PESEL", "Nazwisko", "Miasto", "DataUrodzenia"],
        properties: {
            PESEL: {
                bsonType: "string",
                pattern: "^[0-9]{11}$",
				description: "is required and must be string and match regular expression"
            },
            Nazwisko: {
                bsonType: "string",
                description: "is required and must be string"
            },
            Miasto: {
                bsonType: "string",
                description: "is required and must be string"
            },
            DataUrodzenia: {
                bsonType: "date",
                description: "is required and must be date"
            },
            OstatnieWypozyczenie: {
                bsonType: "date",
                description: "is not required and must be date"
            },
            Wypozyczenia:{
                bsonType: "array",
                minItems: 0,
                uniqueItems: true,
                items: {
                    bsonType: ["object"],
                    required: ["Sygnatura", "Data", "LiczbaDni"],
                    properties: {
                        Sygnatura: {
                            bsonType: "string"
                        },
                        Data: {
                            bsonType: "date"
                        },
                        LiczbaDni: {
                            bsonType: "int"
                        }
                    }
                }
            }
        }
    }}
})