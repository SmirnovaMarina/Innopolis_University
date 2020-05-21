from py2neo import Graph
from tabulate import tabulate
import numpy as np


def run_third_query(graph: Graph, cust_id: int):
    result = graph.run('''MATCH (customer:Customer {customer_id: %s}),
                        p=((customer)-[*2..4]->(film:Film)), 
                        (film)-[is_of_category]->(category:Category) 
                        WITH customer, film, category, count(p) AS counter
                        RETURN film.title AS title, category.name AS category, 
                        counter AS rental_times''' % cust_id)

    columns = np.array(['title', 'category', 'rental times'], dtype="object")
    row = [[d['title'], d['category'], d['rental_times']] for d in result]
    print(tabulate(row, headers=columns))


