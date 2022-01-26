export PGDATABASE := psi
export PGUSER := alumnodb
export PGPASSWORD := alumnodb
export PGCLIENTENCODING := LATIN9
export PGHOST := localhost
export DJANGOPORT = 8001
# you must update the value of HEROKUHOST
export HEROKUHOST := git:remote protected-bastion-43256
PSQL = psql
CMD = python3 manage.py
HEROKU = heroku run export SQLITE=1 &
# Add applications to APP variable as they are
# added to settings.py file
APP = catalog  orders
#APP = catalog

server:
	$(CMD) runserver $(DJANGOPORT)

reset_db: clear_db update_db create_super_user

clear_db:
	@echo Clear Database
	dropdb --if-exists $(PGDATABASE)
	createdb

shell:
	@echo manage.py  shell
	@$(CMD) shell

dbshell:
	@echo manage.py dbshell
	@$(CMD) dbshell

populate:
	@echo populate database
	rm -rf static/covers/*.png
	python3 ./manage.py populate

static:
	@echo manage.py collectstatic
	python3 ./manage.py collectstatic

update_db:
	$(CMD) makemigrations $(APP)
	$(CMD) migrate

create_super_user:
	$(CMD) shell -c "from django.contrib.auth import get_user_model; User = get_user_model(); User.objects.create_superuser('alumnodb', 'admin@myproject.com', 'alumnodb')"

clear_update_db:
	@echo del migrations and make migrations and migrate
	rm -rf */migrations
	python3 ./manage.py makemigrations $(APP) 
	python3 ./manage.py migrate

test_catalog_datamodel:
	$(CMD) test catalog.tests_models --keepdb

test_catalog_services:
	$(CMD) test catalog.tests_services --keepdb

test_authentication_services:
	$(CMD) test authentication.tests_services --keepdb

test_orders_cart:
	$(CMD) test orders.tests_cart --keepdb

test_orders_services:
	$(CMD) test orders.tests_services --keepdb

test_orders_models:
	$(CMD) test orders.tests_models --keepdb

test_catalog_additional:
	$(CMD) test catalog.tests_additional --keepdb

test_authentication_additional:
	$(CMD) test authentication.tests_additional --keepdb

test:	test_catalog_datamodel	test_catalog_services	test_catalog_additional	test_authentication_additional	test_authentication_services	test_orders_models	test_orders_services	test_orders_cart

# other commands that may be useful but require tuning
#test_heroku:
#	$(HEROKU) $(CMD) test datamodel.tests_models.GameModelTests --keepdb & wait
#	$(HEROKU) $(CMD) test datamodel.tests_models.MoveModelTests --keepdb & wait
#	$(HEROKU) $(CMD) test datamodel.tests_models.my_tests --keepdb & wait
#
#test_query:
#	python3 test_query.py
#
#test_query_heroku:
#	$(HEROKU) python3 test_query.py
#
#config_heroku:
#	heroku login
#	heroku $HEROKUHOST
#
heroku_push:
	git push heroku master

heroku_bash:
	heroku run bash

heroku_dbshell:
	heroku pg:psql
