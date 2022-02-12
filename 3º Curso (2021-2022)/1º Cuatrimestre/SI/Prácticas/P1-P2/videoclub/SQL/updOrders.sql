CREATE OR REPLACE FUNCTION updOrders_trigger()
RETURNS TRIGGER
AS $$
DECLARE
	oid INTEGER; -- Orderid del cambio
BEGIN
	IF TG_OP = 'INSERT' or TG_OP = 'UPDATE' THEN
		oid := NEW.orderid;
	ELSE
		oid := OLD.orderid;
	END IF;
	UPDATE orders
	SET netamount = round(q.neto, 2),
        totalamount = round(q.neto * (1 + tax/100), 2)
	FROM (SELECT sum(price * quantity) as neto
		FROM orderdetail
		WHERE orderid = oid) as q;
	RETURN NEW;
END; $$
LANGUAGE plpgsql;

CREATE TRIGGER updOrders
AFTER INSERT OR UPDATE OR DELETE ON orderdetail
FOR EACH ROW
EXECUTE PROCEDURE updOrders_trigger();
