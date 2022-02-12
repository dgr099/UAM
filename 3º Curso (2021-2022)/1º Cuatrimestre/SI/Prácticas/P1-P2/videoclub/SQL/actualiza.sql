-- Tabla alerts, aumenta cuando un stock llega a 0 tras el trigger
CREATE TABLE IF NOT EXISTS alerts(
    prod_id INTEGER NOT NULL,
    date    DATE    NOT NULL,
    time    TIME    NOT NULL,
    PRIMARY KEY (prod_id, date, time),
    FOREIGN KEY (prod_id)
        REFERENCES products (prod_id)
);

-- Funcion que se ejecuta por defecto en el campo balance de customers
CREATE FUNCTION setCustomersBalance(IN initialBalance BIGINT)
    RETURNS REAL AS $$
BEGIN
    RETURN floor(random() * (initialBalance + 1));
END;
$$ LANGUAGE 'plpgsql';

-- Nuevo campo "loyalty" inicializado a 0
ALTER TABLE customers ADD COLUMN IF NOT EXISTS loyalty INTEGER default 0;
-- Nuevo campo "balance" inicializado con valor random entre 0 y 100
ALTER TABLE customers ADD COLUMN IF NOT EXISTS balance REAL default setCustomersBalance(100);

-- Cambios necesarios en la base de datos
ALTER TABLE imdb_actormovies ADD PRIMARY KEY (actorid, movieid, character);
ALTER TABLE imdb_directormovies DROP CONSTRAINT imdb_directormovies_pkey;
ALTER TABLE imdb_directormovies ADD PRIMARY KEY(directorid, movieid);
ALTER TABLE orders ADD FOREIGN KEY(customerid) REFERENCES customers(customerid);
ALTER TABLE customers ADD CONSTRAINT UQ_username_password UNIQUE(username, password);

-- Cambio de atributos multivaluados a entidades que se relacionan
CREATE TABLE IF NOT EXISTS country(
    country VARCHAR NOT NULL,
    PRIMARY KEY (country)
);
INSERT INTO country(country) SELECT DISTINCT country FROM imdb_moviecountries;
ALTER TABLE imdb_moviecountries ADD FOREIGN KEY(country) REFERENCES country(country);

CREATE TABLE IF NOT EXISTS language(
    language VARCHAR NOT NULL,
    PRIMARY KEY (language)
);
INSERT INTO language(language) SELECT DISTINCT language FROM imdb_movielanguages;
ALTER TABLE imdb_movielanguages ADD FOREIGN KEY(language) REFERENCES language(language);

CREATE TABLE IF NOT EXISTS genre(
    genre VARCHAR NOT NULL,
    PRIMARY KEY (genre)
);
INSERT INTO genre(genre) SELECT DISTINCT genre FROM imdb_moviegenres;
ALTER TABLE imdb_moviegenres ADD FOREIGN KEY(genre) REFERENCES genre(genre);

-- Mas cambios necesarios, orderdetail contenía tuplas con
-- datos repetidos en campos que deberían ser Primary Key
CREATE TABLE auxiliar AS SELECT orderid, prod_id, price, sum(quantity) AS quantity FROM orderdetail GROUP BY orderid, prod_id, price;
DROP TABLE orderdetail;
ALTER TABLE auxiliar RENAME TO orderdetail;
ALTER TABLE orderdetail ADD FOREIGN KEY(orderid) REFERENCES orders(orderid);
ALTER TABLE orderdetail ADD FOREIGN KEY(prod_id) REFERENCES products(prod_id);
ALTER TABLE orderdetail ADD PRIMARY KEY(orderid, prod_id);
