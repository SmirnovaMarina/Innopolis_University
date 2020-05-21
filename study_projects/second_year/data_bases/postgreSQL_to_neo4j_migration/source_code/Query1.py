from py2neo import Graph


def run_first_query(graph: Graph):
    results = graph.run('''MATCH (rental:Rental) WITH max(rental.rental_date) AS r_max
                            MATCH (c:Customer)-[:ordered]-(r:Rental)-[:ordered_inventory_is]-(i:Inventory)-[:contains_film]-(f:Film)-[:is_of_category]-(category:Category)
                            WHERE r.rental_date.year>=r_max.year
                            WITH c, count(DISTINCT category) AS Categories 
                            WHERE Categories > 1
                            RETURN DISTINCT c.first_name AS First_Name, c.last_name AS Last_Name, Categories''')
    print(results.to_data_frame())