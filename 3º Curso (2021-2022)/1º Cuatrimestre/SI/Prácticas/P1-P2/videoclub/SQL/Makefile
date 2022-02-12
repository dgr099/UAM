.SILENT:

all: restart drop create inicializar entrar

restart:
	echo "\nRestarting postgresql: Write your host password"
	sudo systemctl restart postgresql;

drop:
	echo "\nDropping the database..."
	PGPASSWORD=alumnodb dropdb --if-exists -U alumnodb si1;

create:
	echo "\nCreating the database..."
	PGPASSWORD=alumnodb createdb -U alumnodb si1;

inicializar: starting actualiza sets gets upds

starting:
	echo "\nInitializing the database..."
	gunzip -c *.gz | PGPASSWORD=alumnodb psql -U alumnodb si1 > /dev/null;

actualiza:
	echo "\nUpdating the database..."
	PGPASSWORD=alumnodb psql -U alumnodb si1 -a -f ./actualiza.sql > /dev/null;

sets:
	echo "\nExecuting setPrice.sql and setOrderAmount.sql...";
	PGPASSWORD=alumnodb psql -U alumnodb si1 -a -f ./setPrice.sql -f ./setOrderAmount.sql > /dev/null;
	echo "\nExecuting function setOrderAmount()...";
	PGPASSWORD=alumnodb psql -U alumnodb si1 -c "select setorderamount();" > /dev/null;

gets:
	echo "\nExecuting getTopSales.sql and getTopActors.sql...";
	PGPASSWORD=alumnodb psql -U alumnodb si1 -a -f ./getTopSales.sql -f ./getTopActors.sql > /dev/null;

upds:
	echo "\nExecuting updOrders.sql and updInventoryAndCustomer.sql...";
	PGPASSWORD=alumnodb psql -U alumnodb si1 -a -f ./updOrders.sql -f ./updInventoryAndCustomer.sql > /dev/null;

entrar:
	echo "\nEntering into de database...";
	PGPASSWORD=alumnodb psql -U alumnodb si1;
