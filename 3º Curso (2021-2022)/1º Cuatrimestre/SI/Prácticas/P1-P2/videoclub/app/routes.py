#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from app import app
from app import database
from flask import render_template, request, url_for, redirect, session, flash
import hashlib
import json
import os
import sys
import random
import requests
from faker import Faker
#from bs4 import BeautifulSoup
limit = 20
limitActors = 10
offset = 0
fake = Faker()
search=None
cart=None
genre=None
#funciones para permitir páginación
@app.route('/next')
def next_movies():
    global offset, genre
    offset+=limit
    if(genre is not None):
        return redirect(url_for('filter', genre_1=genre))
    return redirect(url_for('index'))

@app.route('/previous')
def previous_movies():
    global offset, genre
    if(offset>0):
        offset-=limit
    if(genre is not None):
        return redirect(url_for('filter', genre_1=genre))
    return redirect(url_for('index'))

@app.route('/reset_pagination')
def reset_pagination():
    global offset
    offset=0
    return redirect(url_for('index'))

@app.route('/', methods=['POST', 'GET'])
@app.route('/index', methods=['POST', 'GET'])
def index():
    global genre, offset, search, limitActors
    if request.method == 'POST': #si está intentando buscar algo
        search=request.form['search']
        limitActors=request.form['limitActors']
    maxFilms = database.db_getNum_films(search)
    genre=None
    print (url_for('static', filename='estilo.css'), file=sys.stderr)
    movies = database.db_listOfMoviesPaginated(limit, offset, genre, search)
    genres = database.db_getAllGenres()
    if(offset+limit>maxFilms):
        has_next = False
    else:
        has_next = True
    if(offset>0):
        has_prev = True
    else:
        has_prev = False
    #completeCoverInfo(movies)
    return render_template('index.html', title = "Home", genres=genres, movies=movies, has_prev=has_prev, has_next=has_next, search=search, actors=database.db_getTopActor("Action", limitActors), limitActors=limitActors)

@app.route('/filer/<genre_1>', methods=['POST', 'GET'])
def filter(genre_1):
    global genre, offset, search, limitActors
    if request.method == 'POST': #si está intentando buscar algo
        search=request.form['search']
        limitActors=request.form['limitActors']
    genre=genre_1
    offset=0
    maxFilmsGender = database.db_getNum_filmsGender(genre_1, search)
    movies = database.db_listOfMoviesPaginated(limit, offset, genre, search)
    genres = database.db_getAllGenres()
    if(offset+limit>maxFilmsGender):
        has_next = False
    else:
        has_next = True
    if(offset>0):
        has_prev = True
    else:
        has_prev = False
    #completeCoverInfo(movies)
    return render_template('index.html', title = genre_1, genres=genres, movies=movies, has_prev=has_prev, has_next=has_next, search=search, actors=database.db_getTopActor(genre, limitActors), limitActors=limitActors)

"""
    Está función sirve para obtener el html de la búsqueda y obtner la thumbnail a partir de estos
    def completeCoverInfo(movies):
    for movie in movies:
        titulo = movie["movietitle"]
        titulo = titulo.replace("/", "-")
        url = "https://www.google.com/search?site=&tbm=isch&source=hp&biw=1873&bih=990&q=" + titulo + " imagesize:800x1200"
        r = requests.get(url)
        soup = BeautifulSoup(r.text, "lxml")
        images = soup.find("img", {"class": "yWs4tf"})
        filmCoverDict[movie["movieid"]]=images['src']"""


@app.route('/login', methods=['GET', 'POST'])
def login():
    
    # doc sobre request object en http://flask.pocoo.org/docs/1.0/api/#incoming-request-data
    if 'username' in request.form:
        username = request.form['username']
        password = request.form['password']
        # aqui se deberia validar con fichero .dat del usuario
        result= database.db_getUser(username, password)
        if(isinstance(result, int) and result<0): #si no hay usuario con los datos introducidos
            if(result==-1):
                flash('Username not found')
            if(result==-2):
                flash('Password incorrect')
            return render_template('login.html', title="Sign In")
        if('shop' in session): #si tenía un carrito anterior
            session.pop('shop', None)#de momento lo quitamos pero lo suyo sería añadirlo al nuevo no sé
        
        session['usuario'] = {}
        session['usuario']['customerid'] = result['customerid']
        session['usuario']['username'] = result['username']
        session['usuario']['balance'] = result['balance']
        session['usuario']['cart'] = database.db_getShoppingCart(result['customerid'])
        session.modified=True  
        # se puede usar request.referrer para volver a la pagina desde la que se hizo login
        if session['url_origen'] != url_for('register') and session['url_origen'] != url_for('index'):
            return redirect(session['url_origen'])
        return redirect(url_for('index'))
    else:
        # se puede guardar la pagina desde la que se invoca 
        session['url_origen']=request.referrer
        session.modified=True        
        # print a error.log de Apache si se ejecuta bajo mod_wsgi
        print (request.referrer, file=sys.stderr)
        return render_template('login.html', title = "Sign In")


@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        #no es necesaria está comprobación porque ya se comprueba en el propio insert
        """if(isinstance(database.db_getUser(request.form['username'], request.form['password']),int)==False): #si devuelve un resultado, ya hay alguien con esos credenciales
            flash('Values already in use')
            columnasNecesarias = database.db_getcolumnsUserNotNullableNoComprobadas()
            return render_template('register.html', title = "Register", columnasNecesarias=columnasNecesarias)"""
        result = database.db_insertUser(request.form) #insertamos el usuario con los datos
        if(isinstance(result, int) and result>=0): #si la operación salió correctamente debería devolver el nuevo id
            """dic = {}
            for key in request.form.keys():
                dic[key] = request.form[key]
            print(dic)"""
            #si esos campos no están en uso, se crea un usuario con los valores guardados
            return redirect(url_for('login'))
        else:
            flash('This user already exists')
            columnasNecesarias = database.db_getcolumnsUserNotNullableNoComprobadas()
            return render_template('register.html', title = "Register", columnasNecesarias=columnasNecesarias)
    else:
        columnasNecesarias = database.db_getcolumnsUserNotNullableNoComprobadas()
        return render_template('register.html', title = "Register", columnasNecesarias=columnasNecesarias)

@app.route('/logout', methods=['GET', 'POST'])
def logout():
    session.pop('usuario', None) #simplemente popeamos el usuario
    session.modified=True #ponemos como modificada la sesión para que se guarden los cambios
    return redirect(url_for('index'))

@app.route('/movie/<id>', methods=["GET", "POST"])
def movie_detail(id):
    
    if request.method == 'POST': #si pretende añadir una película
        product = request.form['product'] #solicito el id del product
        if 'usuario' not in session: #si no está logeado, se emplea la sesión
            if('shop' not in session): #si no se había creado la sesión de la compra la creamos
                session['shop'] = {}
            if(product in session['shop'].keys()): #si aún no habiamos añadido esa peli
                session['shop'][product] +=1 #+1 a las veces que compra ese producto
            else:
                session['shop'][product] = 1 #1º vez que compra esa peli"""
            session.modified=True
        else: #si estoy logeado
            database.db_addToCart(product, session['usuario']['cart']) #introduzco el pedido en el carro
        
            
    #se muestra la página de movie detail
    movie = database.db_getFilm(id)
    actors = database.db_getActorsOfFilm(movie)
    #get desc from wikipedia, opcional
    """response = requests.get(
	url="https://en.wikipedia.org/wiki/" + movie["movietitle"],
    )
    desc="No se encontro descripción"
    if(response.status_code==200):
        soup = BeautifulSoup(response.content, 'html.parser')
        title = soup.find(id="Plot")
        text = title.findNext('p')
        desc = text.get_text()"""
    desc=fake.text(2000)
    products = database.db_getProductsOfFilm(movie)
    return render_template('movie_detail.html', title = "Detail", movie = movie, actors=actors, products=products, desc=desc)

@app.route('/shoppingCart')
def shoppingCart():
    total_price=0
    times={}
    products=()
    if('usuario' in session): #si está logeado
        points=database.db_getUserField(session['usuario']['customerid'], 'loyalty')
        products=database.db_getProductsFromCart(session['usuario']['customerid'])
        times=database.db_getTimesProductsCart(products, session['usuario']['cart'])
        total_price=database.db_getPriceCart(session['usuario']['cart'])
        print(total_price)
    else: #si no está logeado
        points="Not Login"
        if('shop' in session): #compruebas si tenía alguna compra
            products = database.db_getProducts(session['shop'].keys()) #coges los productos para obtener sus películas
    films = database.db_getFilmsOfProducts(products)
    film_dict={}
    for film in films: #diccionario para que sea más rápido el acceso
        film_dict[film['movieid']] = film
    return render_template('shopping_cart.html', puntos=points, products=products, films=film_dict, times=times, total_price=total_price)

@app.route('/updateUsers')
def updateUsers():
    return str(random.randint(0, 999999))

@app.route('/Add<id>')
def addId(id):
    
    if('usuario' not in session): #si está logeado
        session['shop'][id]+=1
        session.modified=True
    else:
        database.db_addToCart(id, session['usuario']['cart'])
    return redirect(url_for('shoppingCart'))

@app.route('/Del<id>')
def delId(id):
    
    if('usuario' not in session):
        session['shop'][id]-=1
        if(session['shop'][id]==0):
            session['shop'].pop(id)
        session.modified=True
    else:
        database.db_delFromCart(id, session['usuario']['cart'])
    return redirect(url_for('shoppingCart'))

@app.route('/buy', methods=["GET", "POST"])
def buy():
    if 'usuario' in session and request.method == "POST" and request.form['select'] != "":
        """total_precio = 0
        for id_movie in session['shop']:
            price = session['shop'][id_movie][1] * session['shop'][id_movie][0]['precio']
            total_precio += price
        """
        total_precio = float(request.form['price'])
        #total_precio = database.db_getPriceCart(session['usuario']['cart'])
        metodo_pago = request.form['select']
        if metodo_pago == "Puntos":
            puntosUsed = int(request.form['numPuntos'])
            if puntosUsed > database.db_getUserField(session['usuario']['customerid'], 'loyalty'):
                flash('No tienes esa cantidad de puntos')
                return redirect(url_for('shoppingCart'))
            priceLess = round(puntosUsed / 100, 2)
            if priceLess > total_precio:
                flash('No puedes usar tantos puntos')
                return redirect(url_for('shoppingCart'))
            total_precio -= priceLess
            if total_precio > database.db_getUserField(session['usuario']['customerid'], 'balance'):
                flash('No tienes cantidad de dinero suficiente')
                return redirect(url_for('shoppingCart'))
            database.db_usePoints(session['usuario']['customerid'], session['usuario']['cart'], puntosUsed, total_precio)
        if float(total_precio) <= float(database.db_getUserField(session['usuario']['customerid'], 'balance')):
            database.db_pay(session['usuario']['cart'])  # actualiza el campo status a 'Paid'
            session['usuario']['cart'] = database.db_getShoppingCart(session['usuario']['customerid'])
            session['usuario']['balance'] -= total_precio
            session.modified=True
        else:
            flash('No tienes suficiente cantidad de dinero')
            return redirect(url_for('shoppingCart'))
        return redirect(url_for('index'))
    else:
        flash('Escoge un metodo de pago')
        return redirect(url_for('shoppingCart'))


@app.route('/User_detail', methods=["GET", "POST"])
def userDetail():
    if request.method == 'POST': #si ha pedido añadir dinero
        money = request.form['money']
        newMoney = database.db_addMoney(session['usuario']['customerid'], money)
        if not isinstance(newMoney, str): #si se agrega correctamente (no devuelve un string del error)
            session['usuario']['balance']=newMoney
            session.modified=True
    proucts = ()
    pelis = {}
    #obtengo los productos
    products = database.db_getProductsFromUser(session['usuario']['customerid'])
    films = database.db_getFilmsOfProducts(products) #obtengo las películas para esos producto
    film_dict={}
    for film in films: #diccionario para que sea más rápido el acceso
        film_dict[film['movieid']] = (film, database.db_getGenres(film))
    genres = database.db_getAllGenres()
    return render_template('user_detail.html', title = session['usuario']['username'], products=products, films=film_dict, genres=genres)




