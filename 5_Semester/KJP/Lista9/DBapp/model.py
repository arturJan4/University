import re
import re
import sys
from datetime import date

from sqlalchemy import create_engine, Column, Integer, String, ForeignKey, exc
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship

# attach file (engine) and create sesion maker (factory)
Base = declarative_base()
engine = create_engine('sqlite:///books.db', echo=False)
Session = sessionmaker(bind=engine)


# Note:
# book to borrow is one to one (single book can only be borrowed once)
# friend to borrow is one to many (one friend can have multiple borrowed books)


class Book(Base):
    """
    represents one physical copy of a book
    """
    __tablename__ = 'book'

    id = Column('id', Integer, primary_key=True)
    title = Column('title', String, unique=True, nullable=False)
    author = Column('author', String, unique=False, nullable=False)
    publisher = Column('publisher', String, unique=False, nullable=True)
    isbn = Column('isbn', String, unique=False, nullable=True)
    release_year = Column('release', Integer, unique=False, nullable=False)

    # specify one-to-one (because of uselist=False) relationship with borrow table
    borrow = relationship("Borrow", back_populates="book", uselist=False)

    # used for easier printing
    def __repr__(self):
        return f"Book (id={self.id}, title={self.title}, " \
               f"author={self.author}, publisher={self.publisher}, isbn={self.isbn}, release_year={self.release_year})"


class Friend(Base):
    """
    represents one friend
    """
    __tablename__ = 'friend'

    id = Column('id', Integer, primary_key=True)
    name = Column('name', String, unique=False, nullable=False)
    email = Column('email', String, unique=True, nullable=False)

    # specify one-to-many relationship with borrow table
    borrowed = relationship("Borrow", back_populates="friend")

    def __repr__(self):
        return f"Friend (id={self.id}, name={self.name}, email={self.email})"


class Borrow(Base):
    """
    lists borrowed books (and associated id of the book and id of the borrower)
    """
    __tablename__ = 'borrow'

    id = Column('id', Integer, primary_key=True)

    book_id = Column(Integer, ForeignKey("book.id"))
    book = relationship("Book", back_populates="borrow")

    friend_id = Column(Integer, ForeignKey("friend.id"))
    friend = relationship("Friend", back_populates="borrowed")

    def __repr__(self):
        return f"Borrow (id={self.id}, friend={self.friend.name}, book={self.book.title})"


# str to reference e.g. "Book" -> Book
def str_to_class(classname):
    return getattr(sys.modules[__name__], classname)


# print table given in args.table as class reference
def print_obj(args):
    with Session() as session:
        results = session.query(str_to_class(args.table)).all()
        if not results:
            print("Table is empty!")
            return

        for obj in results:
            try:
                print(obj)
            except exc.SQLAlchemyError as e:
                print(e)
        # session.close() automatically


# https://www.geeksforgeeks.org/check-if-email-address-valid-or-not-in-python/
def check_mail(email):
    regex = r'\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b'
    if re.fullmatch(regex, email):
        return True
    else:
        return False


# https://stackoverflow.com/questions/4047511/checking-if-an-isbn-number-is-correct
def check_isbn(isbn):
    """ isbn-10 format """
    isbn = isbn.replace("-", "").replace(" ", "").upper()
    match = re.search(r'^(\d{9})(\d|X)$', isbn)
    if not match:
        return False

    digits = match.group(1)
    check_digit = 10 if match.group(2) == 'X' else int(match.group(2))

    result = sum((i + 1) * int(digit) for i, digit in enumerate(digits))
    return (result % 11) == check_digit


def add_book(title, author, year, isbn, publisher):
    """add a valid book or raise exception"""
    with Session() as session:
        # title must be unique (querying by id instead of whole row speeds up search)
        exists_title = session.query(
            session.query(Book.id).filter_by(title=title).exists()
        ).scalar()
        if exists_title:
            raise RuntimeError(f"title ({title}) already exists")

        # isbn must be unique
        if isbn is not None:
            exists_isbn = session.query(
                session.query(Book.id).filter_by(title=isbn).exists()
            ).scalar()
            if exists_isbn:
                raise RuntimeError(f"isbn ({isbn}) already exists")

            if not check_isbn(isbn):
                raise RuntimeError(f"invalid isbn (ISBN-10 format: {isbn})")

        # year must make sense
        today_date = date.today()
        min_year = -2000  # arbitrary BC date
        max_year = today_date.year + 1  # +1 for special cases

        if not (min_year <= int(year) <= max_year):
            raise RuntimeError(f"invalid year {year}")

        book = Book(title=title,
                    author=author,
                    release_year=year,
                    isbn=isbn,
                    publisher=publisher
                    )

        session.add(book)
        try:  # wrap in generic try/catch just in case (for production usage I would have to be more specific)
            session.commit()
        except exc.SQLAlchemyError as e:
            print(e)

        print("Added a book!")


def update_book(real_id, title, author, publisher, isbn, year):
    """update book based on selected id"""
    # TODO: stricter error checking
    with Session() as session:

        session.query(Book).filter(Book.id == real_id).update({
            "title": title,
            "author": author,
            "publisher": year,
            "isbn": isbn,
            "release_year": publisher,
        })

    session.commit()


def delete_book(real_id):
    """delete book based on selected id"""
    # TODO: stricter error checking
    with Session() as session:
        # book specified by name instead of id
        book = session.query(Book).get(real_id)

        if book is None:
            raise LookupError(f"book id/name doesn't exist ({real_id})")

        try:
            session.delete(book)
            session.commit()
        except exc.SQLAlchemyError as e:
            print(e)


def get_books():
    """get all books as an array of objects"""
    with Session() as session:
        books = session.query(Book).all()

        return books

# TODO: Add Borrow and Friends methods when needed (they must be modified slightly compared to previous exerxcise)


# if database is not created -> create it
Base.metadata.create_all(bind=engine)
