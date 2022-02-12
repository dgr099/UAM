-- Borramos el indice por precaucion
drop index if exists countStatus;

-- Query 1
explain
select count(*)
from orders
where status is null;

-- Query 2
explain
select count(*)
from orders
where status = 'Shipped';

-- Creamos el indice sobre la columna status de orders
create index countStatus on orders(status);

-- Query 1 con indice
explain
select count(*)
from orders
where status is null;
 
-- Query 2 con indice
explain
select count(*)
from orders
where status = 'Shipped';

-- Eliminamos el indice
drop index if exists countStatus;

-- Generamos el análisis
analyze;

-- Query 1 sin indice y tras analyze
explain
select count(*)
from orders
where status is null;
 
-- Query 2 sin indice y tras analyze
explain
select count(*)
from orders
where status = 'Shipped';

-- Volvemos a crear el indice
create index countStatus on orders(status);

-- Generamos de nuevo el análisis
analyze;

-- Query 1 con indice y tras analyze
explain
select count(*)
from orders
where status is null;
 
-- Query 2 con indice y tras analyze
explain
select count(*)
from orders
where status = 'Shipped';

-- Eliminamos el indice de nuevo 
drop index if exists countStatus;

-- Query 3
explain
select count(*)
from orders
where status = 'Paid';

-- Query 4
explain
select count(*)
from orders
where status = 'Processed';

-- Recuperamos el indice de nuevo
create index countStatus on orders(status);

-- Query 3 con indice
explain
select count(*)
from orders
where status = 'Paid';

-- Query 4 con indice
explain
select count(*)
from orders
where status = 'Processed';

-- Eliminamos de nuevo el indice y generamos el analisis
drop index if exists countStatus;
analyze;

-- Query 3 sin indice y tras analisis
explain
select count(*)
from orders
where status = 'Paid';

-- Query 4 sin indice y tras analisis
explain
select count(*)
from orders
where status = 'Processed';

-- Finalmente, recuperamos el indice y volvemos a analizar
create index countStatus on orders(status);
analyze;

-- Query 3 con indice y tras analisis
explain
select count(*)
from orders
where status = 'Paid';

-- Query 4 con indice y tras analisis
explain
select count(*)
from orders
where status = 'Processed';