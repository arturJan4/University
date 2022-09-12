import argparse
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
    isbn = Column('isbn', String, unique=True, nullable=True)
    release_year = Column('release', Integer, unique=False, nullable=False)

    # specify one-to-one (because of uselist=False) relationship with borrow table
    borrow = relationship("Borrow", back_populates="book", uselist=False)

    # used for easier printing
    def __repr__(self):
        return f"Book (id={self.id}, title={self.title}, author={self.author}, publisher={self.publisher}, isbn={self.isbn}, release_year={self.release_year})"


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


def add_book(args):
    """add a valid book or raise exception"""
    with Session() as session:
        # title must be unique (querying by id instead of whole row speeds up search)
        exists_title = session.query(
            session.query(Book.id).filter_by(title=args.title).exists()
        ).scalar()
        if exists_title:
            raise RuntimeError(f"title ({args.title}) already exists")

        # isbn must be unique
        if args.isbn is not None:
            exists_isbn = session.query(
                session.query(Book.id).filter_by(title=args.title).exists()
            ).scalar()
            if exists_isbn:
                raise RuntimeError(f"isbn ({args.isbn}) already exists")

            if not check_isbn(args.isbn):
                raise RuntimeError(f"invalid isbn (ISBN-10 format: {args.isbn})")

        # year must make sense
        today_date = date.today()
        min_year = -2000  # arbitrary BC date
        max_year = today_date.year + 1  # +1 for special cases

        if not (min_year <= args.year <= max_year):
            raise RuntimeError(f"invalid year {args.year}")

        book = Book(title=args.title,
                    author=args.author,
                    release_year=args.year,
                    isbn=args.isbn,
                    publisher=args.publisher
                    )

        session.add(book)
        try:  # wrap in generic try/catch just in case (for production usage I would have to be more specific)
            session.commit()
        except exc.SQLAlchemyError as e:
            print(e)

        print("Added a book!")


def add_friend(args):
    """add a valid friend or raise exception"""
    with Session() as session:
        if not check_mail(args.email):
            raise RuntimeError("Invalid email")

        exists_email = session.query(
            session.query(Friend.id).filter_by(email=args.email).exists()
        ).scalar()

        if exists_email:
            raise RuntimeError(f"friend with mail ({args.email}) already exists")

        friend = Friend(name=args.name, email=args.email)
        session.add(friend)
        try:
            session.commit()
        except exc.SQLAlchemyError as e:
            print(e)

        print("Added a friend!")


def borrow_book(args):
    """
    borrow a book if it is not borrowed already
    """
    with Session() as session:
        # book specified by name instead of id
        if args.book_id is None:
            book = session.query(Book).filter_by(title=args.book_name).scalar()
        else:
            book = session.query(Book).get(args.book_id)

        # friend specified by email instead of id
        if args.friend_id is None:
            friend = session.query(Friend).filter_by(email=args.friend_email).scalar()
        else:
            friend = session.query(Friend).get(args.friend_id)

        if book is None:
            raise LookupError(f"book id/name doesn't exist ({args.book_id} | {args.book_name})")
        elif friend is None:
            raise LookupError(f"friend id/email doesn't exist ({args.friend_id} | {args.friend_email})")

        exists_borrow = session.query(
            session.query(Borrow.id).filter_by(id=book.id).exists()
        ).scalar()
        if exists_borrow:
            raise RuntimeError("Book is already borrowed!")

        borrow = Borrow(book=book, friend=friend)
        session.add(borrow)

        try:
            session.commit()
        except exc.SQLAlchemyError as e:
            print(e)
        # session.close() automatically

        print("Borrowed book!")


def return_book(args):
    """return borrowed book"""
    with Session() as session:
        # book specified by name instead of id
        if args.book_id is None:
            book = session.query(Book).filter_by(title=args.book_name).scalar()
        else:
            book = session.query(Book).get(args.book_id)

        if book is None:
            raise LookupError(f"book id/name doesn't exist ({args.book_id} | {args.book_name})")

        try:
            session.query(Borrow).filter(Borrow.book == book).delete()
            session.commit()
        except exc.SQLAlchemyError as e:
            print(e)

        print("Returned book!")


def add(obj):
    """wrapper used by set_defaults and args.func() to easily map subparser to above functions"""
    if obj is Book:
        return add_book
    elif obj is Friend:
        return add_friend
    elif obj is Borrow:
        return borrow_book
    else:
        raise TypeError("wrong add type")


if __name__ == '__main__':
    usage_print = """
    print -> prints Book
    print -t Borrow -> prints borrowed
    print -t Friend -> prints friends"""

    usage_add_book = """
    add_book -t="Henryk Garncarz" -a=J.K -y=2002
    add_book --title="Hooddaughter Crusoe" --author=D.D --year=1719 --isbn 0393964523 --publisher AMZ
    """

    usage_add_friend = """
    add_friend -n David -e test@mail.com
    """

    usage_borrow = """
    borrow -bi 3 -fi 1
    borrow -bn "Henryk Garncarz" -fe test@mail.com
    """

    usage_return = """
    return -bi 2
    return -bn "Henryk Garncarz"
    """

    parser = argparse.ArgumentParser(prog="bookdb")
    subparsers = parser.add_subparsers(title="subcommands", dest='command')

    add_book_parser = subparsers.add_parser("add_book", help="Add new book to database.", usage=usage_add_book)
    add_book_parser.set_defaults(func=add(Book))
    add_book_parser.add_argument('-t',
                                 '--title',
                                 action='store',
                                 required=True,
                                 help="title of the book (unique)")
    add_book_parser.add_argument('-a',
                                 '--author',
                                 action='store',
                                 required=True,
                                 help="author of the book")
    add_book_parser.add_argument('-y',
                                 '--year',
                                 action='store',
                                 required=True,
                                 help="release year of the book",
                                 type=int)
    add_book_parser.add_argument('-i',
                                 '--isbn',
                                 action='store',
                                 help="isbn of the book (unique)")
    add_book_parser.add_argument('-p',
                                 '--publisher',
                                 action='store',
                                 help="publisher of the book")

    add_friend_parser = subparsers.add_parser("add_friend", help="Add new friend to database.", usage=usage_add_friend)
    add_friend_parser.add_argument('-n',
                                   '--name',
                                   action='store',
                                   required=True,
                                   help="name of the friend")
    add_friend_parser.add_argument('-e',
                                   '--email',
                                   action='store',
                                   required=True,
                                   help="email of the friend (unique)")
    add_friend_parser.set_defaults(func=add(Friend))

    # has mutually exclusive required group (meaning must have exactly one from it)
    borrow_parser = subparsers.add_parser("borrow", help="Borrow a specific book to a friend.", usage=usage_borrow)
    book_identifier = borrow_parser.add_mutually_exclusive_group(required=True)
    book_identifier.add_argument('-bi',
                                 '--book_id',
                                 action='store',
                                 help="id of book to borrow")
    book_identifier.add_argument('-bn',
                                 '--book_name',
                                 action='store',
                                 help="name of book to borrow")
    friend_identifier = borrow_parser.add_mutually_exclusive_group(required=True)
    friend_identifier.add_argument('-fi',
                                   '--friend_id',
                                   action='store',
                                   help="id of friend borrowing the book")
    friend_identifier.add_argument('-fe',
                                   '--friend_email',
                                   action='store',
                                   help="email of friend borrowing the book")
    borrow_parser.set_defaults(func=add(Borrow))

    return_parser = subparsers.add_parser("return", help="Return the lent book.", usage=usage_return)
    book_identifier = return_parser.add_mutually_exclusive_group(required=True)
    book_identifier.add_argument('-bi',
                                 '--book_id',
                                 action='store',
                                 help="id of book to return")
    book_identifier.add_argument('-bn',
                                 '--book_name',
                                 action='store',
                                 help="name of book to return")
    return_parser.set_defaults(func=return_book)

    print_parser = subparsers.add_parser("print", help="Print specified table (default=Books).", usage=usage_print)
    print_parser.add_argument('-t',
                              '--table',
                              action='store',
                              required=False,
                              default="Book",
                              type=str.capitalize,
                              choices=["Book", "Friend", "Borrow"],
                              help="which table to print")
    print_parser.set_defaults(func=print_obj)

    if len(sys.argv) < 2:
        print('Pass more arguments to the command line!')
        parser.print_help()

        for subparser in [add_book_parser, add_friend_parser, borrow_parser, return_parser, print_parser]:
            subparser.format_help()
        sys.exit()

    Base.metadata.create_all(bind=engine)

    args = parser.parse_args()
    args.func(args)  # subparser choice -> function
