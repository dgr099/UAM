#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from app import app
from app import database
from flask import render_template, request, url_for
import os
import sys
import time

@app.route('/', methods=['POST','GET'])
@app.route('/index', methods=['POST','GET'])
def index():
    return render_template('index.html')


@app.route('/borraCiudad', methods=['POST','GET'])
def borraCiudad():
    #recibe la ciudad de los clientes a borrar por formulario
    if 'city' in request.form:
        city    = request.form["city"]
        #1->Transacción vía sentencias SQL
        #2->Transacción vía funciones SQLAlchemy
        bSQL    = request.form["txnSQL"]
        bCommit = "bCommit" in request.form
        bFallo  = "bFallo"  in request.form
        duerme  = request.form["duerme"]
        print(city, bSQL, bCommit, bFallo, duerme)
        dbr = database.delCity(city, bFallo, bSQL=='1', int(duerme), bCommit)
        return render_template('borraCiudad.html', dbr=dbr)
    else:
        return render_template('borraCiudad.html')

    
@app.route('/topUK', methods=['POST','GET'])
def topUK():
    # TODO: consultas a MongoDB ...
    movies=[[],[],[]]
    movies[0] = database.db_Mongo_getFilms19941998()
    movies[1] = database.db_Mongo_getFilmsDramas1998The()
    movies[2] = database.db_Mongo_getFilmsJuliaRobertsAndAlecBaldwin()
    return render_template('topUK.html', movies=movies)