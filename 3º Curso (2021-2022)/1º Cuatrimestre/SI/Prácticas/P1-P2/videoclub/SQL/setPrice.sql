update orderdetail
-- 2. Actualizamos el campo price con los precios originales
set price = q.newPrice
from	(select od.orderid, od.prod_id,
			-- 1. Con la diferencia de años conseguimos saber las veces
			-- que se ha aplicado el aumento de precio a cada producto.
			-- Al elevar 1.02 a este numero, conseguimos el aumento de
			-- precio en porcentaje.
			-- La division con price nos da el precio original
			(p.price / power(1.02, extract(year from now()) - extract(year from o.orderdate))) as newPrice 
		from products as p, orders as o, orderdetail as od
		where od.prod_id = p.prod_id and o.orderid = od.orderid) as q 
where q.orderid = orderdetail.orderid and q.prod_id = orderdetail.prod_id;
