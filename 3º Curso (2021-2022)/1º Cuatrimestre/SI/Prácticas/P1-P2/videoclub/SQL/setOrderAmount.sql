CREATE OR REPLACE FUNCTION setOrderAmount()
RETURNS VOID
AS $$
BEGIN
    UPDATE orders
    SET netamount = round(q.neto, 2),
        totalamount = round(q.neto * (1 + tax/100), 2)
    FROM (SELECT orderid, sum(price * quantity) as neto
            FROM orderdetail
            GROUP BY orderid) as q
    WHERE orders.orderid = q.orderid and netamount IS NULL;
END; $$
LANGUAGE plpgsql;
