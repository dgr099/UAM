create or replace function get_date_in_format(date_to_format timestamp)
returns varchar
as $$
begin
    return to_char(date_to_format, 'YYYYMM');
end; $$
language plpgsql
immutable;


-- Primera Query junto a su explain
explain 
select count(*)
from (select distinct c.city
        from orders natural join customers as c
        where c.creditcardtype = 'VISA' and
            get_date_in_format(orderdate) = '201601'
        ) as q;

-- Creamos indice en customers(customerid)
drop index if exists index_ciudadesdistintas;
create index index_ciudadesdistintas on customers(customerid);

-- Query junto a su explain con index en customers(customerid)
explain 
select count(*)
from (select distinct c.city
        from orders natural join customers as c
        where c.creditcardtype = 'VISA' and
            get_date_in_format(orderdate) = '201601'
        ) as q;

-- Creamos indice en customers(city)
drop index if exists index_ciudadesdistintas;
create index index_ciudadesdistintas on customers(city);

-- Query junto a su explain con index en customers(city)
explain 
select count(*)
from (select distinct c.city
        from orders natural join customers as c
        where c.creditcardtype = 'VISA' and
            get_date_in_format(orderdate) = '201601'
        ) as q;

-- Creamos indice en customers(creditcardtype)
drop index if exists index_ciudadesdistintas;
create index index_ciudadesdistintas on customers(creditcardtype);

-- Query junto a su explain con index en customers(creditcardtype)
explain 
select count(*)
from (select distinct c.city
        from orders natural join customers as c
        where c.creditcardtype = 'VISA' and
            get_date_in_format(orderdate) = '201601'
        ) as q;

-- Creamos indice en orders(orderdate)
drop index if exists index_ciudadesdistintas;
create index index_ciudadesdistintas on orders(orderdate);

-- Query junto a su explain con index en orders(orderdate)
explain 
select count(*)
from (select distinct c.city
        from orders natural join customers as c
        where c.creditcardtype = 'VISA' and
            get_date_in_format(orderdate) = '201601'
        ) as q;

-- Creamos indice en orders(get_date_in_format(orderdate))
drop index if exists index_ciudadesdistintas;
create index index_ciudadesdistintas on orders(get_date_in_format(orderdate));

-- Query junto a su explain con index en get_date_in_format(orderdate)
explain 
select count(*)
from (select distinct c.city
        from orders natural join customers as c
        where c.creditcardtype = 'VISA' and
            get_date_in_format(orderdate) = '201601'
        ) as q;

-- Creamos indice en orders(customerid, get_date_in_format(orderdate))
drop index if exists index_ciudadesdistintas;
create index index_ciudadesdistintas on orders(customerid, get_date_in_format(orderdate));

-- Query junto a su explain con index en (customerid, get_date_in_format(orderdate))
explain 
select count(*)
from (select distinct c.city
        from orders natural join customers as c
        where c.creditcardtype = 'VISA' and
            get_date_in_format(orderdate) = '201601'
        ) as q;
