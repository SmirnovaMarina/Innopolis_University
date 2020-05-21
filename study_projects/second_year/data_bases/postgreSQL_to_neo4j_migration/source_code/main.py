import psycopg2
from py2neo import Database
from Export_Import import execute_export
from Match_Nodes import *
from Neo4j_Query_Runner import *

""" Connection to Postgres Database """
connection = psycopg2.connect(host="localhost",
                              database="dvdrental",
                              user="postgres",
                              password="69215")
cursor = connection.cursor()

""" Connection to Neo4j Database """
uri = "bolt://localhost:7687"
db = Database(uri)
graph = Graph(password='neo4j15')
tx = graph.begin(autocommit=False)


def creat_db():
    execute_export(cursor, tx, graph)
    execute_matching(cursor, graph)


def execute_query():
    while True:
        query = input('Choose a query: ')
        choose_query(query, graph)
        print()


"""First of all, you need to drop and create a Neo4j Database by uncommenting line create_db().
    Then you can execute queries by uncommenting line execute_query()."""
creat_db()
execute_query()

cursor.close()
connection.close()
