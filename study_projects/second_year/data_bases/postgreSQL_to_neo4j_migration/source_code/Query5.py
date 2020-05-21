from py2neo import Graph


def run_fifth_query(graph: Graph, fixed_actor: int, actor_id: int):

    result = graph.run('''MATCH path=shortestPath(
                            (fixed_actor:Actor {actor_id: %s})-[:acts_in*]-(actor_other:Actor {actor_id: %s}))
                            RETURN path 
                            ''' % (fixed_actor, actor_id))
    node_counter = 0
    for record in result:
        nodes = record["path"].nodes
        for node in nodes:
            node_counter += 1

    print("The degree of separation is "+str((node_counter - 2-1)//2+1))