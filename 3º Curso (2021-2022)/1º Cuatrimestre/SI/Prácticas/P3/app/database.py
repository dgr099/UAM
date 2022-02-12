# -*- coding: utf-8 -*-

import os
import sys, traceback, time

from sqlalchemy import create_engine
from pymongo import MongoClient

# configurar el motor de sqlalchemy
db_engine = create_engine("postgresql://alumnodb:alumnodb@localhost/si1", echo=False, execution_options={"autocommit":False})

# Crea la conexión con MongoDB

def getMongoCollection(mongoDB_client):
    mongo_db = mongoDB_client.si1
    return mongo_db.topUK

def mongoDBCloseConnect(mongoDB_client):
    mongoDB_client.close()

def mongoDBStartconnect():
    return MongoClient("mongodb://localhost:27017/")

def db_Mongo_getFilms19941998():
    mongo_client=mongoDBStartconnect()
    collection = getMongoCollection(mongo_client)
    result = list( collection.find(({"year": {"$gte":"1994", "$lte":"1998" }, "genres" : "Sci-Fi"})) )
    mongoDBCloseConnect(mongo_client)
    return result

#db.topUK.find({"actors": {$all: ["Roberts, Julia", "Baldwin, Alec"]}});
def db_Mongo_getFilmsJuliaRobertsAndAlecBaldwin():
    mongo_client=mongoDBStartconnect()
    collection = getMongoCollection(mongo_client)
    result = list( collection.find(({"actors": {"$all": ["Roberts, Julia", "Baldwin, Alec"]}})) )
    mongoDBCloseConnect(mongo_client)
    return result

def db_Mongo_getFilmsDramas1998The():
    mongo_client=mongoDBStartconnect()
    collection = getMongoCollection(mongo_client)
    result = list( collection.find(({"year":"1998", "genres":"Drama", "title":{'$regex':'The'}})))
    mongoDBCloseConnect(mongo_client)
    return result

def dbConnect():
    return db_engine.connect()

def dbCloseConnect(db_conn):
    db_conn.close()
  
def delCity(city, bFallo, bSQL, duerme, bCommit):
    
    # Array de trazas a mostrar en la página
    dbr=[]

    # TODO: Ejecutar consultas de borrado
    # - ordenar consultas según se desee provocar un error (bFallo True) o no
    # - ejecutar commit intermedio si bCommit es True
    # - usar sentencias SQL ('BEGIN', 'COMMIT', ...) si bSQL es True
    # - suspender la ejecución 'duerme' segundos en el punto adecuado para forzar deadlock
    # - ir guardando trazas mediante dbr.append()
    try:
        db_engine
        db_conn = dbConnect()
        if(bSQL==1): #consultas sql

            #primero empezamos con el begin
            db_conn.execute("BEGIN;")
            dbr.append("BEGIN")

            if (bFallo != True):
                query_in_order(db_conn, city, duerme, bCommit, dbr)
            else:
                query_not_in_order(db_conn, city, duerme, bCommit, dbr)

    except Exception as e:
        db_conn.execute("ROLLBACK;")
        dbr.append("ROLLBACK" + str(e))
        if db_conn is not None:
            db_conn.close()
    else:
        #si llegamos al final guardamos los cambios
        db_conn.execute("COMMIT;")
        dbr.append("COMMIT")
        if db_conn is not None:
            db_conn.close()

    return dbr

def query_in_order(db_conn, city, duerme, bCommit, dbr):

    #empizo obteniendo el id de todos los customer que estén en la city especificada
    query = "select customerID from customers where city='" + str(city) + "';"
    idsC = list(db_conn.execute(query))
    idCustomers = []
    for a in idsC:
        idCustomers.append(a[0])
    dbr.append("LEER CUSTOMERS")
    
    #obtengo las orderID de las orders de los customerid de la ciudad especificados
    query = "select orderID from orders where customerid IN " + str(idCustomers).replace("[", "(").replace("]", ")") + ";"
    idsO = list(db_conn.execute(query))
    idOrders = []
    for a in idsO:
        idOrders.append(a[0])
    dbr.append("LEER PEDIDOS")

    if len(idOrders) != 0:
        #borrar pedidos de orderdetail
        query = "delete from orderdetail where orderid in " + str(idOrders).replace("[", "(").replace("]", ")") + ";"
        db_conn.execute(query)
        dbr.append("BORRAR PRODUCTOS DE PEDIDOS")

    if bCommit == True:
        db_conn.execute("COMMIT;")
        dbr.append("COMMIT")
        db_conn.execute("BEGIN;")
        dbr.append("BEGIN")

    if duerme != 0:
        db_conn.execute("SELECT pg_sleep(" + str(duerme) + ");")
        dbr.append("SLEEP")

    if len(idOrders) != 0:
        #borrar pedidos de orders
        query = "delete from orders where orderid in " + str(idOrders).replace("[", "(").replace("]", ")") + ";"
        db_conn.execute(query)
        dbr.append("BORRAR PEDIDOS")

    if bCommit == True:
        db_conn.execute("COMMIT;")
        dbr.append("COMMIT")
        db_conn.execute("BEGIN;")
        dbr.append("BEGIN")

    if len(idCustomers) != 0:
        #borrar customers
        query = "delete from customers where customerid in " + str(idCustomers).replace("[", "(").replace("]", ")") + ";"
        db_conn.execute(query)
        dbr.append("BORRAR USUARIOS")


def query_not_in_order(db_conn, city, duerme, bCommit, dbr):
    #empizo obteniendo el id de todos los customer que estén en la city especificada
    query = "select customerID from customers where city='" + str(city) + "';"
    idsC = list(db_conn.execute(query))
    idCustomers = []
    for a in idsC:
        idCustomers.append(a[0])
    dbr.append("LEER CUSTOMERS")
    
    #obtengo las orderID de las orders de los customerid de la ciudad especificados
    query = "select orderID from orders where customerid IN " + str(idCustomers).replace("[", "(").replace("]", ")") + ";"
    idsO = list(db_conn.execute(query))
    idOrders = []
    for a in idsO:
        idOrders.append(a[0])
    dbr.append("LEER PEDIDOS")

    if len(idOrders) != 0:
        #borrar pedidos de orderdetail
        query = "delete from orderdetail where orderid in " + str(idOrders).replace("[", "(").replace("]", ")") + ";"
        db_conn.execute(query)
        dbr.append("BORRAR PRODUCTOS DE PEDIDOS")

    if bCommit == True:
        db_conn.execute("COMMIT;")
        dbr.append("COMMIT")
        db_conn.execute("BEGIN;")
        dbr.append("BEGIN")

    if duerme != 0:
        db_conn.execute("SELECT pg_sleep(" + str(duerme) + ");")
        dbr.append("SLEEP")
    
    if len(idCustomers) != 0:
        #borrar customers
        query = "delete from customers where customerid in " + str(idCustomers).replace("[", "(").replace("]", ")") + ";"
        db_conn.execute(query)
        dbr.append("BORRAR USUARIOS")
    
    if bCommit == True:
        db_conn.execute("COMMIT;")
        dbr.append("COMMIT")
        db_conn.execute("BEGIN;")
        dbr.append("BEGIN")

    if len(idOrders) != 0:
        #borrar pedidos de orders
        query = "delete from orders where orderid in " + str(idOrders).replace("[", "(").replace("]", ")") + ";"
        db_conn.execute(query)
        dbr.append("BORRAR PEDIDOS")

    