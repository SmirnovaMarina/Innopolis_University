from py2neo import Graph


def delete_nodes_indexes(graph: Graph):
    graph.delete_all()
    schema = graph.schema
    schema.drop_index("Actor", "actor_id")
    schema.drop_index("Address", "address_id")
    schema.drop_index("Category", "category_id")
    schema.drop_index("City", "city_id")
    schema.drop_index("Country", "country_id")
    schema.drop_index("Customer", "customer_id")
    schema.drop_index("Film", "film_id")
    schema.drop_index("Inventory", "inventory_id")
    schema.drop_index("Language", "language_id")
    schema.drop_index("Payment", "payment_id")
    schema.drop_index("Rental", "rental_id")
    schema.drop_index("Staff", "staff_id")
    schema.drop_index("Store", "store_id")

    #schema.drop_index("Rental", "rental_date_index")


