from py2neo import Graph, Node
from Drop_Delete import delete_nodes_indexes


def create_indexes(graph: Graph):
    graph.run("CREATE INDEX actor_id FOR (n:Actor) ON (n.actor_id)")
    graph.run("CREATE INDEX address_id FOR (n:Address) ON (n.address_id)")
    graph.run("CREATE INDEX category_id FOR (n:Category) ON (n.category_id)")
    graph.run("CREATE INDEX city_id FOR (n:City) ON (n.city_id)")
    graph.run("CREATE INDEX country_id FOR (n:Country) ON (n.country_id)")
    graph.run("CREATE INDEX customer_id FOR (n:Customer) ON (n.customer_id)")
    graph.run("CREATE INDEX film_id FOR (n:Film) ON (n.film_id)")
    graph.run("CREATE INDEX inventory_id FOR (n:Inventory) ON (n.inventory_id)")
    graph.run("CREATE INDEX language_id FOR (n:Language) ON (n.language_id)")
    graph.run("CREATE INDEX payment_id FOR (n:Payment) ON (n.payment_id)")
    graph.run("CREATE INDEX rental_id FOR (n:Rental) ON (n.rental_id)")
    graph.run("CREATE INDEX staff_id FOR (n:Staff) ON (n.staff_id)")
    graph.run("CREATE INDEX store_id FOR (n:Store) ON (n.store_id)")

    #graph.run("CREATE INDEX rental_date_index FOR (n:Rental) ON (n.rental_date)")


def create_actor_nodes(tx, cursor):
    query = "SELECT * FROM actor;"
    cursor.execute(query)
    for row in cursor:
        node = Node("Actor", actor_id=row[0], first_name=row[1], last_name=row[2], last_update=row[3])
        tx.create(node)
        tx.merge(node, "Actor", "actor_id")


def create_address_nodes(tx, cursor):
    query = "SELECT * FROM address;"
    cursor.execute(query)
    for row in cursor:
        node = Node("Address", address_id=row[0], address=row[1], address2=row[2], district=row[3], city_id=row[4],
                    postal_code=row[5], phone=[6], last_update=row[7])
        tx.create(node)
        tx.merge(node, "Address", "address_id")


def create_category_nodes(tx, cursor):
    query = "SELECT * FROM category;"
    cursor.execute(query)
    for row in cursor:
        node = Node("Category", category_id=row[0], name=row[1], last_update=row[2])
        tx.create(node)
        tx.merge(node, "Category", "category_id")


def create_city_nodes(tx, cursor):
    query = "SELECT * FROM city;"
    cursor.execute(query)
    for row in cursor:
        node = Node("City", city_id=row[0], city=row[1], country_id=row[2], last_update=row[3])
        tx.create(node)
        tx.merge(node, "City", "city_id")


def create_country_nodes(tx, cursor):
    query = "SELECT * FROM country;"
    cursor.execute(query)
    for row in cursor:
        node = Node("Country", country_id=row[0], country=row[1], last_update=row[2])
        tx.create(node)
        tx.merge(node, "Country", "country_id")


def create_customer_nodes(tx, cursor):
    query = "SELECT * FROM customer;"
    cursor.execute(query)
    for row in cursor:
        node = Node("Customer", customer_id=row[0], store_id=row[1], first_name=row[2], last_name=row[3],
                    email=row[4], address_id=row[5], activebool=row[6], create_date=row[7], last_update=row[8], active=row[9])
        tx.create(node)
        tx.merge(node, "Customer", "customer_id")


def create_film_nodes(tx, cursor):
    query = "SELECT * FROM film;"
    cursor.execute(query)
    for row in cursor:
        node = Node("Film", film_id=row[0], title=row[1], description=row[2], release_year=row[3], language_id=row[4],
                    rental_duration=row[5], rental_rate=float(row[6]), length=row[7], replacement_cost=float(row[8]), rating=row[9],
                    last_update=row[10], special_features=row[11], fulltext=row[12])
        tx.create(node)
        tx.merge(node, "Film", "film_id")


def create_inventory_nodes(tx, cursor):
    query = "SELECT * FROM inventory;"
    cursor.execute(query)
    for row in cursor:
        node = Node("Inventory", inventory_id=row[0], film_id=row[1], store_name=row[2], last_update=row[3])
        tx.create(node)
        tx.merge(node, "Inventory", "inventory_id")

def create_language_nodes(tx, cursor):
    query = "SELECT * FROM language;"
    cursor.execute(query)
    for row in cursor:
        node = Node("Language", language_id=row[0], name=row[1], last_update=row[2])
        tx.create(node)
        tx.merge(node, "Language", "language_id")


def create_payment_nodes(tx, cursor):
    query = "SELECT * FROM payment;"
    cursor.execute(query)
    for row in cursor:
        node = Node("Payment", payment_id=row[0], customer_id=row[1], stuff_id=row[2], rental_id=row[3], amount=float(row[4]),
                    payment_date=row[5])
        tx.create(node)
        tx.merge(node, "Payment", "payment_id")


def create_rental_nodes(tx, cursor):
    query = "SELECT * FROM rental;"
    cursor.execute(query)
    for row in cursor:
        node = Node("Rental", rental_id=row[0], rental_date=row[1], inventory_id=row[2], customer_id=row[3],
                    return_date=row[4], staff_id=row[5], last_update=row[6])
        tx.create(node)
        tx.merge(node, "Rental", "rental_id")


def create_staff_nodes(tx, cursor):
    query = "SELECT * FROM staff;"
    cursor.execute(query)
    for row in cursor:
        try:
            pic = row[10].hex()
        except Exception:
            pic = 'null'

        node = Node("Staff", staff_id=row[0], first_name=row[1], last_name=row[2], address_id=row[3], email=row[4],
                    store_id=row[5], active=row[6], username=row[7], password=row[8], last_update=row[9], picture=pic)
        tx.create(node)
        tx.merge(node, "Staff", "staff_id")


def create_store_nodes(tx, cursor):
    query = "SELECT * FROM store;"
    cursor.execute(query)
    for row in cursor:
        node = Node("Store", store_id=row[0], manager_staff_id=row[1], address_id=row[2], last_update=row[3])
        tx.create(node)
        tx.merge(node, "Store", "store_id")


def create_all_nodes(tx, cursor):
    create_actor_nodes(tx, cursor)
    create_address_nodes(tx, cursor)
    create_category_nodes(tx, cursor)
    create_city_nodes(tx, cursor)
    create_country_nodes(tx, cursor)
    create_customer_nodes(tx, cursor)
    create_film_nodes(tx, cursor)
    create_inventory_nodes(tx, cursor)
    create_language_nodes(tx, cursor)
    create_payment_nodes(tx, cursor)
    create_rental_nodes(tx, cursor)
    create_staff_nodes(tx, cursor)
    create_store_nodes(tx, cursor)


def execute_export(cursor, tx, graph: Graph):
    delete_nodes_indexes(graph)
    create_indexes(graph)
    create_all_nodes(tx, cursor)
    tx.commit()


