CREATE OR REPLACE FUNCTION getTopSales(year1 INT, year2 INT,
    OUT Year INT, OUT Film CHAR, OUT sales BIGINT)
RETURNS SETOF RECORD
AS $$
DECLARE
    tupla RECORD;
BEGIN
    CREATE TEMPORARY TABLE salesPerYear AS
        (SELECT movieid, sum(q.salesperyear) as salesperyear,
            q.yearofsale
        FROM (SELECT od.prod_id, sum(quantity) as salesperyear,
                extract(YEAR FROM orderdate) as yearOfSale
                FROM orderdetail as od natural join orders
                GROUP BY yearOfSale, od.prod_id) as q natural join
            products
        GROUP BY movieid, yearofsale);
    CREATE TEMPORARY TABLE topSales AS
        (SELECT q.year, m.movietitle, q.maxsales
        FROM (SELECT s2.yearofsale as year,
                min(s1.movieid) as movieid, s2.maxsales
                FROM salesPerYear as s1,
                    (SELECT max(s.salesperyear) as maxsales,
                        s.yearofsale
                    FROM salesPerYear as s
                    GROUP BY s.yearofsale) as s2
                WHERE s2.maxsales = s1.salesperyear and
                        s2.yearofsale = s1.yearofsale
                GROUP BY year, s2.maxsales) as q
            JOIN imdb_movies as m ON m.movieid = q.movieid
        WHERE q.year >= year1 and q.year <= year2
        ORDER BY q.maxsales DESC);
    FOR tupla IN SELECT * FROM topSales LOOP
        Year := tupla.year;
        Film := tupla.movietitle;
        sales := tupla.maxsales;
        RETURN NEXT;
    END LOOP;
    DROP TABLE salesPerYear;
    DROP TABLE topSales;
    RETURN;
END; $$
LANGUAGE plpgsql;
