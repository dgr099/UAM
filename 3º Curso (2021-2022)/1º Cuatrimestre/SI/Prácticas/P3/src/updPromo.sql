ALTER TABLE customers ADD COLUMN IF NOT EXISTS promo REAL;

CREATE OR REPLACE FUNCTION updPromo_trigger()
RETURNS TRIGGER
AS $$
BEGIN
    UPDATE orderdetail as od
    SET price = round((price * (1 - NEW.promo/100))::NUMERIC, 2)
    FROM (SELECT od.orderid, od.prod_id
        FROM orders natural join orderdetail as od
        WHERE customerid = NEW.customerid and status IS NULL) as q
    WHERE q.prod_id = od.prod_id and q.orderid = od.orderid;
    PERFORM pg_sleep(10.5);
    UPDATE orders as o
    SET netamount = round(q.neto, 2),
        totalamount = round(q.neto * (1 + tax/100), 2)
    FROM (SELECT od.orderid, sum(price * quantity) as neto
            FROM orders natural join orderdetail as od
            WHERE NEW.customerid = customerid and status is NULL
            GROUP BY od.orderid) as q
    WHERE o.orderid = q.orderid;
    RETURN NEW;
END; $$
LANGUAGE plpgsql;

DROP TRIGGER updPromo ON customers;

CREATE TRIGGER updPromo
BEFORE UPDATE
OF promo ON customers
FOR EACH ROW
EXECUTE PROCEDURE updPromo_trigger();

-- Usuario 1 (U: shad, C: naples)
UPDATE orders SET status = NULL WHERE orderid = 103;

-- Usuario 2 (U: laxity, C: cesar)
UPDATE orders SET status = NULL WHERE orderid = 109;

-- Usuario 3 (U: flax, C: goat)
UPDATE orders SET status = NULL WHERE orderid = 116;

-- Usuario 4 (U: share, C: honor)
UPDATE orders SET status = NULL WHERE orderid = 124;