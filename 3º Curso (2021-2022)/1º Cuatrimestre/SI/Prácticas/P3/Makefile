.SILENT:

all: restart drop create inicializar
	echo "\nInstalling packages..."
	pip3 install psycopg2 > /dev/null;
	pip3 install sqlalchemy	> /dev/null;

restart:
	echo "\nRestarting postgresql: Write your host password"
	sudo systemctl restart postgresql;

drop:
	echo "\nDropping the database..."
	PGPASSWORD=alumnodb dropdb -U alumnodb si1;

create:
	echo "\nCreating the database..."
	PGPASSWORD=alumnodb createdb -U alumnodb si1;

inicializar: starting

starting:
	echo "\nInitializing the database..."
	gunzip -c *.gz | PGPASSWORD=alumnodb psql -U alumnodb si1 > /dev/null;

createMongo:
	echo "\nExecuting createMongoDBFromPostgreSQLDB.py";
	python3 src/createMongoDBFromPostgreSQLDB.py > /dev/null;

ciudadesDistintas:
	echo "\nExecuting ciudadesDistintas.sql";
	PGPASSWORD=alumnodb psql -U alumnodb si1 -f src/ciudadesDistintas.sql > txt/ciudadesDistintas.txt;

countStatus:
	echo "\nExecuting countStatus.sql";
	PGPASSWORD=alumnodb psql -U alumnodb si1 -f src/countStatus.sql > txt/countStatus.txt;

updPromo:
	echo "\nExecuting updPromo.sql";
	PGPASSWORD=alumnodb psql -U alumnodb si1 -f src/updPromo.sql > txt/updPromo.txt;

entrar:
	echo "\nEntering into de database...";
	PGPASSWORD=alumnodb psql -U alumnodb si1;

reset_db: drop create inicializar

server:
	python3 -m app
