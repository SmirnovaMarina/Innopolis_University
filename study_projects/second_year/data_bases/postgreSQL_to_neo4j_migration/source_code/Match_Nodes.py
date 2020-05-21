from py2neo import Graph


def match_film_actor(cursor, graph: Graph):
    query = "SELECT * FROM film_actor;"
    cursor.execute(query)
    for row in cursor:
        graph.run(f"MATCH (a:Actor),(b:Film) WHERE a.actor_id={row[0]} AND b.film_id={row[1]} "
               "CREATE (a)-[rel:acts_in {last_update: "
               f"'{row[2]}'"
               "}]->(b) RETURN rel")


def match_film_category(cursor, graph: Graph):
    query = "SELECT * FROM film_category;"
    cursor.execute(query)
    for row in cursor:
        graph.run(f"MATCH (a:Film),(b:Category) WHERE a.film_id={row[0]} AND b.category_id={row[1]} "
               "CREATE (a)-[rel:is_of_category {last_update: "
               f"'{row[2]}'"
               "}]->(b) RETURN rel")


def match_customer_rental(graph: Graph):
    graph.run("MATCH (r:Rental),(c:Customer) WHERE c.customer_id = r.customer_id "
              "CREATE (c)-[rel:ordered]->(r) RETURN rel")


def match_rental_inventory(graph: Graph):
    graph.run("MATCH (r:Rental),(i:Inventory) WHERE i.inventory_id = r.inventory_id "
              "CREATE (r)-[rel:ordered_inventory_is]->(i) RETURN rel")


def match_inventory_film(graph: Graph):
    graph.run("MATCH (f:Film),(i:Inventory) WHERE f.film_id = i.film_id "
              "CREATE (f)<-[rel:contains_film]-(i) RETURN rel")


def match_customer_film(graph: Graph):
    graph.run("MATCH (f:Film),(c:Customer) WHERE (c)-[*..5]->(f) "
              "CREATE (f)<-[rel:watched]-(c) RETURN rel")


def match_customer_category(graph: Graph):
    graph.run("MATCH (category:Category),(f:Film),(customer:Customer) "
              "WHERE (customer)-[:watched]->(f)-[:is_of_category]->(category) "
              "CREATE (customer)-[rel:likes_category]->(category) RETURN rel")


def execute_matching(cursor, graph: Graph):
    match_film_actor(cursor, graph)
    match_film_category(cursor, graph)

    match_customer_rental(graph)
    match_rental_inventory(graph)
    match_inventory_film(graph)
    match_customer_film(graph)
    match_customer_category(graph)
