# zad 2
Mając gotowe prototypy:
• określić operacje, które będą w ramach danego widoku realizowane,
• ustalić dane, które będą do tych operacji potrzebne oraz te niezbędne, aby widok wygenerować.

W efekcie należy utworzyć:
• tabelę o kolumnach: typ widoku (np. show product details), operację (np. show), obiekty informacji (np.
product, product category, user info),
• roboczą wersję klas (np. wspomniane product, product category, user info) z uwzględnieniem operacji i
właściwości, które będą wspierać oczekiwania zdefiniowane przez utworzoną tabelkę; klasy można utworzyć
w dowolnej formie, np. używając docelowego języka programowania, UMLa czy nawet jako tabelę.

## widoki i operacje

| typ widoku           | operacja | obiekty informacji                      |
| -------------------- | -------- | --------------------------------------- |
| show main page       | show     | product, cart, article                  |
| show all products    | show     | product, cart                           |
| show product details | show     | product, cart, product_category, review |
| show cart            | show     | product, cart, shipment_details         |
| show orders          | show     | order, product, shipment_details, user  |
| login user           | get      | user                                    |
| register user        | add      | user                                    |
| add item             | add      | product, product_category               |


## Klasy
### Product
| zmienna           | typ               |
| ----------------- | ----------------- |
| product_name      | string            |
| price             | int               |
| short_description | string            |
| long_description  | string            |
| product_category  | int (ID)          |
| picture           | string (URL link) |
| ammount           | int               |
| reviews           | listof(Review)    |

operacje:
- pobranie listy produktów
- pobranie listy produktów dla danej kategorii
- wyszukiwanie produktu po nazwie
- pobranie pól konkretnego produktu
- dodanie nowego produktu
- usunięcie produktu
- zmiana któregoś z pól
- policzenie średniej oceny dla danego produktu

### Product_category
| zmienna         | typ                       |
| --------------- | ------------------------- |
| category_name   | string                    |
| parent_category | int (ID, default == NULL) |

operacje:
- dodanie nowej kategorii
- pobranie kategorii dla danego produktu
- zmiana nazwy kategorii
- pobranie nazwy kategorii-rodzica

### Cart
| zmienna  | typ                        |
| -------- | -------------------------- |
| products | listof([product, ammount]) |
| total    | int (wyliczany)            |
| user     | int (ID)                   |

operacje:
- dodanie nowego produktu
- usunięcie danego produktu
- pobranie ceny

### Article
| zmienna    | typ    |
| ---------- | ------ |
| title      | string |
| content    | string |
| created_at | date   |

operacje:
- dodanie/usunięcie artykułu
- zmiana treści/tytułu

### User
| zmienna  | typ             |
| -------- | --------------- |
| created_at | date   |
| email    | string (unique) |
| password | string(hashed)  |
| salt     | string          |
| permission_level | INT (0-regular user, 1-admin) |

operacje:
- dodanie/usunięcie użytkownika
- wyszukiwanie użytkownika po nazwie
- sprawdzenie hasła (dla logowania)
- zmiana hasła
- przypomnienie hasła

### Review
| zmienna    | typ                         |
| ---------- | --------------------------- |
| user_id    | int (ID, null -> anonymous) |
| created_at | date                        |
| content    | string                      |
| product_id | int (ID)                    |
| stars      | int [1..5]                  |

operacje:
- dodanie/usunięcie recenzji
- pobranie recenzji dokonanych przez danego użytkownika

### Order
| zmienna | typ |
| ------- | --- |
| products | listof([product, ammount]) |
| total | int |
| payment_status | enum (NOT_PAID, PROCESSING, PAID) |
| created_at | date   |
| updated_at | date   |
| predicted_delivery_at | date   |
| delivered_at | date   |
| user | int (ID) |
| delivery_status | enum (ORDERED, ACCEPTED, REJECTED, PACKING, TRAVELLING, AT_POST_OFFICE DELIVERED, RETURNED) |
| shipment_details | int (ID) |

operacje:
- dodanie/usunięcie zamówienia
- zmiana statusu dostawy
- zmiana statusu płatności

### Shipment_details
| zmienna | typ |
| ------- | --- |
| user_id | int (ID)  |
| deliver_type | enum (?)  |
| deliver_price | int  |
| address | Address type (City, Street, Postcode, House/Flat number)  |

operacje:
- dodanie/zmiana/usunięcie adresu

