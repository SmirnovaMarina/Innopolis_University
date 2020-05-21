--Query 1:
create index rental_last_upd_sort_desc on rental(last_update DESC);
create index rental_id_include on rental(rental_id) include (customer_id, staff_id, last_update);

--Query 2:

--Query 3:
create index payment_rental_id_hash on payment using hash(rental_id);
create index rental_inventory_id_hash on rental using hash(inventory_id);
create index rental_customer_id_hash on rental using hash(customer_id);

create index inventory_film_id on inventory(film_id);

create index film_actor_film_id_hash on film_actor using hash(film_id);

create index film_id on film using hash(film_id);