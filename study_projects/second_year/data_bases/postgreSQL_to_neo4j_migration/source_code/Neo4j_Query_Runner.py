from py2neo import Graph

from Query1 import run_first_query
from Query2 import run_second_query
from Query3 import run_third_query
from Query4 import run_forth_query
from Query5 import run_fifth_query


def choose_query(query, graph: Graph):

    if int(query) == 1:
        run_first_query(graph)
    if int(query) == 2:
        run_second_query(graph)
    if int(query) == 3:
        customer_id = input('Enter a customer_id: ')
        run_third_query(graph, customer_id)
    if int(query) == 4:
        customer_id = input('Enter a customer_id: ')
        run_forth_query(graph, customer_id)
    if int(query) == 5:
        actor_id = int(input('Enter an actor_id: '))
        if actor_id != 1:
            run_fifth_query(graph, 1, actor_id)
        if actor_id == 1:
            print("The degree of separation between a node and itself is 0.")


