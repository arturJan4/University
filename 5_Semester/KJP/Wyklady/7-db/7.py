# I - storing objects
# pickle package
# serialization + deserialization
# native for python

import pickle

# for example:
# save weights for a ML model
obj1 = {'uno': [1], 'duo': [2, 3]}

# serialize
with open('7-db/object.store', 'wb') as fh:
    pickle.dump(obj1, fh)

# deserialize
with open('7-db/object.store', 'rb') as fh:
    obj2 = pickle.load(fh)

print(obj2)

# we can save Bools, Numbers, Lists, Tuples, Dicts, Classes, Objects

# json
import json
with open('7-db/jsonobj', 'w') as fh:
    json.dump(obj1, fh)

# caution
# 6(!) variants of serialization in Python dependant on lang version
# susceptible to attacks
# compression can be used

# shelve package
# useful to store a lot of objects as a dict
# key is always a string
# value is serialized object using pickle
# it uses unix's "dbm"

import shelve

with shelve.open("7-db/shelve") as db:
    for i in range(3):
        db[f"lista{i}"] = [1,2,3, i]
    db.sync()
    for k in db:
        print(f"{k}: {db[k]}")

# we can sync often
# no multiple access
# not all operations change sth
# db['list'].append(x), does not append x
# but if we use a temp, append and then db['list'] = temp
# then it does change

# real-world use-case
# caching SQL queries
# first time take from SQL db
# then cache it in shelve

# II - relational databases
# SQL engines:
# Oracle, DB/2, MySQL, PostgreSQL, MSSQL etc.
# many interfaces -> solution: Python Database API Specification
# unified API (current 2.0)

# connect(parametrs..) (returns Connection object)
# parameters: host, db, user, passwd etc.
# .fetch, .cursor, .execute etc.
# result -> description ,rowcount etc.
# standard exceptions: Warning, DatabaseError, NotSupportedError
# but orgs don't always follow Python DB API to the t ://

# SQLite -> 'file' database without outside server
# package: sqlite3
# DB API 2.0 with extensions
# sqlite.connect(':memory')

# III - ORM - SQLAlchemy
# using only ORM we can create (using only Python):
# tables in database
# CRUD operations
# laziness/eagerness, transactional, multi-access etc.

# SQLAlchemy
# examples -> slides
# sessions

# IV - other
# NOSQL in Python
# Document-oriented
# MongoDB
# Graph databases
# KeyValue stores (BigTable, Hadoop, BerkeleyDB, dbm)
# pydoop.pipes -> map/reduce example
