/*
databases

1) hierarchical databases
basically trees (e.g. XML)
relation restrictions

2) relational databases
relations: one-to-many, many-to-many etc.
object can be both uniquely identified and in relation
standardized (SQL)
db can be a file or db server
transaction mechanism

3) object databases 
class object as row
not popular because of lack of standarization
Query Object Langugage, Query By Example

4) graph databases
optimize for relations
no one query language
neo4j

5) NoSQL db
usally scale easier, easier to implement
no one standard query language
hard to version
hard to model complex relations

MongoDB
CouchDB
MemcacheDB

PostgreSQL
SQL Server
dbeaver/azure data studio
tcp/ip connection to db
parent/child

datatypes: 
char(size) vs varchar(size) - store explicite vs pointer
nvarchar(size) - 16 bytes chars -> utf
null values?

Surrogate key (ID column)

dbo -> schema (namespace)
select ID, ParentName from Parent
insert into Parent (ParentName) values ('parent1'), ('parent2')
delete * from Child

comments: 
single-line: --
multi-line: obvious

version control: migrations

select * from Child
where ChildName like '%2'
order by Childname desc;

update Parent set ParentName='parent22' where ID=1

types: queries, clausules, aggregating functions, paging
paging: OFFSET N ROWS FETCH NEXT M ROWS ONLY (given an order)

aggregating functions: count, AVG, MIN, MAX
select min(ID) from Parent

select * from Child join Parent on Child.ID_Parent = Parent.ID

full outer joiner, inner join etc.
1:20 -> not needed yet
*/