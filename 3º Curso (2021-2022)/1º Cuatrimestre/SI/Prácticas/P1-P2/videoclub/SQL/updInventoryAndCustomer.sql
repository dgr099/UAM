CREATE OR REPLACE FUNCTION updInventoryAndCustomer_trigger()
RETURNS TRIGGER
AS $$
DECLARE
	datetime TIMESTAMP;
	p_id INTEGER;

BEGIN
	IF NEW.status = 'Paid' THEN

        -- Actualizamos orders
		datetime := now()::TIMESTAMP;
        UPDATE orders SET orderdate = datetime::DATE
		WHERE NEW.orderid = orderid;

        -- Creamos tabla temporal para guardar los productos comprados
        CREATE TEMPORARY TABLE newStocks
        AS (SELECT od.prod_id, od.quantity
            FROM orderdetail as od
            WHERE od.orderid = NEW.orderid);

        -- Actualizamos el inventario
		UPDATE inventory
		SET stock = stock - q.quantity,
			sales = sales + q.quantity
		FROM newStocks as q
		WHERE inventory.prod_id = q.prod_id;

        -- Guardamos en alerts en caso de stock = 0
		FOR p_id IN SELECT q.prod_id
				FROM newStocks as q NATURAL JOIN
					inventory as i
				WHERE i.stock = 0
		LOOP
			INSERT INTO alerts
			VALUES (p_id, datetime::DATE, datetime::TIME);
		END LOOP;
		DROP TABLE newStocks;

        -- Pagar puntos de fidelizacion y descontar precio de balance
        UPDATE customers
        SET loyalty = floor(
            	loyalty + round(0.05 * NEW.totalamount, 2)),
            balance = balance - NEW.totalamount;

	END IF;
	RETURN NEW;
END; $$
LANGUAGE plpgsql;

CREATE TRIGGER updInventoryAndCustomer
AFTER UPDATE OF status ON orders
FOR EACH ROW
EXECUTE PROCEDURE updInventoryAndCustomer_trigger()
