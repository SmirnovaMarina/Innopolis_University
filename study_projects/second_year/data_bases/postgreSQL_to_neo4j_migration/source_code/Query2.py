from py2neo import Graph
import numpy as np
from tabulate import tabulate


def run_second_query(graph: Graph):
    result = graph.run('''MATCH (actor1:Actor)-[:acts_in]->(films:Film)<-[:acts_in]-(actor2:Actor)
                        WITH actor1, actor2, count(films) AS counter
                        RETURN actor1.actor_id AS actor1_id, actor2.actor_id AS actor2_id, counter''')
    array = np.zeros((200, 201))
    columns = np.array([i for i in range(1, 201)])
    for i in range(0, 200):
        array[i][0] = i+1

    for dictionary in result:
        actor1_id = dictionary['actor1_id']
        actor2_id = dictionary['actor2_id']
        array[actor1_id-1][actor2_id] = dictionary['counter']

    print(tabulate(array, headers=columns, tablefmt="presto"))






