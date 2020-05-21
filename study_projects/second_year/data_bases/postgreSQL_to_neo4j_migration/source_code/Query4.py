from py2neo import Graph
from tabulate import tabulate


def run_forth_query(graph: Graph, cust_id: int):

    result = graph.run('''MATCH p=((c1:Customer {customer_id: %s})-[:likes_category]->(cat:Category))
                            WITH cat, count(p) AS counter  RETURN cat.name AS category, counter 
                            ORDER BY counter DESC LIMIT 3''' % cust_id)

    array = [d['category'] for d in result]
    print(array)

    for category in array:
        print("For category " + category + " recommended films are" + ":")
        result2 = graph.run('''MATCH (c1:Customer{customer_id: %s}), 
                            (cat:Category{name: "%s"})<-[:is_of_category]-(film:Film)<-[:watched]-(c2:Customer) 
                            WHERE NOT EXISTS ((c1)-[:watched]->(film)) 
                            RETURN DISTINCT film.title AS title LIMIT 10''' % (cust_id, category))

        film_titles = [[d['title']] for d in result2]
        print(tabulate(film_titles))
        print()
