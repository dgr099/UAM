# -*- coding: utf-8 -*-

import os
import sys, traceback
from sqlalchemy import create_engine
from sqlalchemy import Table, Column, Integer, String, MetaData, ForeignKey, text
from sqlalchemy.sql import select

# configurar el motor de sqlalchemy
db_engine = create_engine("postgresql://alumnodb:alumnodb@localhost/si1", echo=False)
db_meta = MetaData(bind=db_engine)
# cargar una tabla
db_table_movies = Table('imdb_movies', db_meta, autoload=True, autoload_with=db_engine)

def db_listOfMovies1949():
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
        
        # Seleccionar las peliculas del anno 1949
        db_movies_1949 = select([db_table_movies]).where(text("year = '1949'"))
        db_result = db_conn.execute(db_movies_1949)
        #db_result = db_conn.execute("Select * from imdb_movies where year = '1949'")
        
        db_conn.close()
        
        return  list(db_result)
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_listOfMovies():
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
        
        # Seleccionar las peliculas del anno 1949
        db_result = db_conn.execute("Select * from imdb_movies")
        
        db_conn.close()
        
        return  list(db_result)
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_listOfActors():
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
        
        # Seleccionar las peliculas del anno 1949
        db_result = db_conn.execute("Select * from imdb_actors")
        
        db_conn.close()
        
        return  list(db_result)
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_listOfMoviesPaginated(limit, offset, genre, search):
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
        query="Select * from imdb_movies m"
        if(genre is not None): #si estás con algún filtro
            query="Select m.movieid, m.movietitle, m.movierelease, m.movietype, m.year, m.issuspended from imdb_movies m, imdb_moviegenres m1 where m.movieid=m1.movieid and m1.genre='"+ str(genre) + "'"
            # Seleccionar las peliculas del anno 1949
            if(search):
                query+=" and m.movietitle iLIKE '%" + str(search) + "%'"
        else:
            if(search):
                query+=" where m.movietitle iLIKE '%" + str(search) + "%'"
        query+=" limit " + str(limit) + " offset " + str(offset)
        db_result = db_conn.execute(text(query))
        
        db_conn.close()
        result = list(db_result)
        return  result
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_getNum_films(search):
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
        
        query="Select count(*) from imdb_movies m"
        if search:
            query+=" where m.movietitle iLIKE '%" + str(search) + "%'"
        db_result = db_conn.execute(text(query))
        db_conn.close()
        result = list(db_result)
        print(result[0]['count'])
        return result[0]['count']
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_getFilm(id):
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
        
        # Seleccionar las peliculas del anno 1949
        db_result = db_conn.execute("Select * from imdb_movies where movieid=" + str(id))
        db_conn.close()
        result = list(db_result)
        return result[0]
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_getActorsOfFilm(movie):
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
        
        # Seleccionar las peliculas del anno 1949
        db_result = db_conn.execute("Select a.actorname, c.character from imdb_movies m, imdb_actormovies c, imdb_actors a where m.movieid=" + str(movie['movieid']) + " and m.movieid=c.movieid and c.actorid=a.actorid")
        db_conn.close()
        result = list(db_result)
        return result
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_getUser(username, password):
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
        if(list(db_conn.execute("Select * from customers where username='" + str(username) +"' limit 1"))):
            db_result = db_conn.execute("Select * from customers where username='" + str(username) + "' and password='" + str(password)+"'")
            db_conn.close()
            result = list(db_result)
            if result:
                return result[0]
            return -2
        return -1
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_getProductsOfFilm(movie):
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
            
        # Seleccionar las peliculas del anno 1949
        db_result = db_conn.execute("Select p.prod_id, p.price, p.description from products p, imdb_movies m where m.movieid=p.movieid and m.movieid=" + str(movie['movieid']))
        db_conn.close()
        result = list(db_result)
        return result
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'


def db_getcolumnsUserNullable():
    query = """
    SELECT
    column_name,
    data_type,
    character_maximum_length
    FROM
        information_schema.columns
    WHERE
        table_name = 'customers' and 
        is_nullable='YES';
    """

    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
            
        # Seleccionar las peliculas del anno 1949
        db_result = db_conn.execute(query)
        db_conn.close()
        result = list(db_result)
        return result
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

def db_getcolumnsUserNotNullableNoComprobadas():
    query = """
    SELECT
    column_name,
    data_type,
    character_maximum_length
    FROM
        information_schema.columns
    WHERE
        table_name = 'customers' and 
        is_nullable='NO' and
        column_name NOT IN ('customerid', 'username', 'email', 'password', 'creditcard', 'address1');
    """

    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
            
        # Seleccionar las peliculas del anno 1949
        db_result = db_conn.execute(query)
        db_conn.close()
        result = list(db_result)
        return result
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)


def db_pay(order_id):
    query = """
    UPDATE orders
    SET status = 'Paid'
    WHERE orderid = """ + str(order_id) + """;
    """

    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
            
        # Poner el status del orderid a paid
        db_result = db_conn.execute(query)
        db_conn.close()
        result = list(db_result)
        return result
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

def db_usePoints(user_id, order_id, points, new_price):
    query1 = """
    UPDATE customers
    SET loyalty = loyalty - """ + str(points) + """
    WHERE customerid = """ + str(user_id) + """;
    """
    query2 = """
    UPDATE orders
    SET totalamount = """ + str(new_price) + """
    WHERE orderid = """ + str(order_id) + """;
    """

    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
            
        # Quitar cantidad de puntos usados y actualizar totalamount
        db_conn.execute(query1)
        db_conn.execute(query2)
        db_conn.close()
        return
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)


def db_getUserField(user_id, field):
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
            
        # Seleccionar campo pasado por argumento
        db_result = db_conn.execute("Select " + field + " from customers where customerid=" + str(user_id) + ";")
        db_conn.close()
        result = list(db_result)
        return result[0][0]
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_getFilmsOfProducts(products):
    try:
        # conexion a la base de datos
        if(len(products)==0): #si no hay productos no ejecutes la query
            return () #devuelve una lista vacia
        db_conn = None
        db_conn = db_engine.connect()
            
        # Conseguir orderid en base al user
        query ="Select movieid from products where prod_id IN ("
        for product in products:
            id = str(product['prod_id'])
            query += id +","
        query = query[:-1] + ")" #quitamos la , del final para poner el )
        db_result = db_conn.execute("Select * from imdb_movies where movieid IN (" + query + ')')
        result=list(db_result)
        return result
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_getProductsFromCart(user):
    try:
        db_conn = None
        db_conn = db_engine.connect()
        
        db_result = db_conn.execute("Select p.prod_id, p.movieid, p.price, p.description from products p, orders o, orderdetail o1 where o.status is NULL and o.orderid=o1.orderid and o1.prod_id=p.prod_id and o.customerid=" + str(user))
        result=list(db_result)
        return result
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_getProducts(products):
    try:
        # conexion a la base de datos
        if(len(products)==0): #si no hay productos no ejecutes la query
            return () #devuelve una lista vacia
        db_conn = None
        db_conn = db_engine.connect()
        
        # Conseguir orderid en base al user
        query ="""
            Select * from products where prod_id IN (
        """
        for product in products:
            query +=product +" ,"
        query = query[:-1] + ")" #quitamos la , del final para poner el )
        db_result = db_conn.execute(query)
        result=list(db_result)
        return result
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_getShoppingCart(user_id):
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
            
        # Conseguir orderid en base al user
        #primero comprobamos si existía un carrito anterior
        db_result = db_conn.execute("Select * from orders where customerid=" + str(user_id) + " and Status is NULL")
        result = list(db_result)
        if result:
            db_conn.close()
            return result[0]['orderid'] #retornamos su orderid
        db_result1 = db_conn.execute("Select max(orderid) from orders;")
        max_orderid = list(db_result1)[0][0]
        max_orderid += 1
        #en caso de no existir, creamos uno nuevo
        db_conn.execute("insert into orders values(" + str(max_orderid) + ", current_date, " + str(user_id) + ", 0, 0, 0, null)")
        return max_orderid
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_insertUser(user):
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
        query ="""INSERT INTO Customers ("""
        query2 = "Select customerid from customers where "
        values =" VALUES ("
        db_result1 = db_conn.execute("Select max(customerid) from customers;")
        #sacamos el max de customer id para crear el nuevo customer id
        max_cid = list(db_result1)[0][0]
        max_cid += 1
        query +="customerid, "
        values+= " '" + str(max_cid) + "', "
        listaKeys = list(user.keys())
        #quitamos el campo de confirmación
        listaKeys.remove('confirm')
        for key in listaKeys:
            query+=key + ','
            values+="'" + user[key] + "',"
            query2+=key+"='"+user[key] + "' and "

        query= query[:-1] + ')' #quitamos la última , y ponemos el )
        values= values[:-1] + ')' #same aquí
        query+=values + ";"
        query2=query2[:-4] + ';'
        db_result=db_conn.execute(query2)
        if(len(list(db_result))>0):
            return -1
        db_result = db_conn.execute(query)
        db_conn.close()
        return max_cid

    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'


def db_addToCart(idproduct, cart):
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
        # comprobamos si ya había algun orderdetail para ese producto en el carro
        db_result = db_conn.execute("Select o1.quantity from orderdetail o1, orders o where o.orderid=o1.orderid and o.orderid="+str(cart) + " and o1.prod_id=" + str(idproduct))
        result = list(db_result)
        if(len(result)<=0): #si no había creamos un orderdetail para el carrito con toda la info
            price = list(db_conn.execute("select price from products where prod_id= " + str(idproduct)))[0][0]
            db_conn.execute("Insert into orderdetail values (" + str(cart) + ", " + str(idproduct) + ", " + str(price) + ", 1)")
            return
        else:
            times = result[0]['quantity'] + 1
            query = """
            UPDATE orderdetail
            SET quantity = """ + str(times) + """
            WHERE  prod_id= """ + str(idproduct) + """
            and orderid=""" + str(cart) 
            db_result = db_conn.execute(query)
            return
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_getTimesProductsCart(products, cart):
    try:
        result={}
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
        # Conseguir orderid en base al user
        #primero comprobamos si existía un carrito anterior
        for product in products:
            query="Select quantity from orderdetail o1 where o1.orderid=" + str(cart) + " and o1.prod_id=" + str(product['prod_id'])
            db_result = db_conn.execute(query)
            result[product['prod_id']]=list(db_result)[0]['quantity']
        return result
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'


def db_delFromCart(idproduct, cart):
    try:
        db_conn = None
        db_conn = db_engine.connect()
        db_result = db_conn.execute("Select o1.quantity from orderdetail o1, orders o where o.orderid=o1.orderid and o.orderid="+str(cart) + " and o1.prod_id=" + str(idproduct))
        result = list(db_result)[0]['quantity']
        if(result>1): #si es mayor que uno simplemente quito 1
            times =result - 1
            query = """
            UPDATE orderdetail
            SET quantity = """ + str(times) + """
            WHERE  prod_id= """ + str(idproduct) + """
            and orderid=""" + str(cart) 
            db_result = db_conn.execute(query)
        else: #si era cero borro directamente el orderdetail
            query = """
                DELETE FROM orderdetail WHERE  prod_id= """ + str(idproduct) + """
                and orderid=""" + str(cart)
            db_result = db_conn.execute(query)
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_getProductsFromUser(user):
    try:
        db_conn = None
        db_conn = db_engine.connect()
        
        db_result = db_conn.execute("Select p.prod_id, p.movieid, p.price, p.description from products p, orders o, orderdetail o1 where o.status is NOT NULL and o.orderid=o1.orderid and o1.prod_id=p.prod_id and o.customerid=" + str(user))
        result=list(db_result)
        return result
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_getGenres(film):
    try:
        db_conn = None
        db_conn = db_engine.connect()
        
        db_result = db_conn.execute("Select genre from imdb_moviegenres where movieid=" + str(film['movieid']))
        result=list(db_result)
        return result
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_getAllGenres():
    try:
        db_conn = None
        db_conn = db_engine.connect()
        
        db_result = db_conn.execute("Select * from genre")
        result=list(db_result)
        return result
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_getNum_filmsGender(genre,search):
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
        
        # Seleccionar las peliculas del anno 1949
        query="Select count(*) from imdb_movies m, imdb_moviegenres m1 where m.movieid=m1.movieid and m1.genre='" + str(genre) +"'"

        if(search):
            query+=" and m.movietitle iLIKE '%" + str(search) + "%'"
        db_result = db_conn.execute(text(query))
        db_conn.close()
        return list(db_result)[0][0]
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_addMoney(user, money):
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
        # comprobamos si ya había algun orderdetail para ese producto en el carro
        db_result = db_conn.execute("Select balance from customers where customerid="+ str(user))
        result = list(db_result)
        moneyUpdate = result[0]['balance'] + float(money)
        query = """
        UPDATE customers
        SET balance = """ + str(moneyUpdate) + """
        WHERE  customerid= """ + str(user)
        db_result = db_conn.execute(query)
        return moneyUpdate
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_getTopActor(genre, limit):
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
        # comprobamos si ya había algun orderdetail para ese producto en el carro
        query = "Select * from getTopActors('"+ str(genre) + "') limit " + str(limit)
        db_result = db_conn.execute(text(query))
        result = list(db_result)
        return result
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

def db_getPriceCart(cart):
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
        # comprobamos si ya había algun orderdetail para ese producto en el carro
        query = "Select totalamount from orders where orderid="+ str(cart)
        db_result = db_conn.execute(text(query))
        result = list(db_result)
        return result[0]['totalamount']
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'

