# -*- coding: utf-8 -*-

import os
import sys, traceback, time

from sqlalchemy import create_engine
from sqlalchemy import Table, Column, Integer, String, MetaData, ForeignKey, text
from sqlalchemy.sql import select
from pymongo import MongoClient
from time import time

def create_mongoDB():
    db_conn = None
    try:
        start = time()

        myclient = MongoClient("mongodb://localhost:27017/")
        #compruebo si existe la base de datos de pymongo
        if "si1" in myclient.list_database_names():
            print("Removing the old si1 data base")
            myclient.drop_database('si1')
        
        i=0
        j=0
        k=0
        # conexion a la base de datos
        db_engine = create_engine("postgresql://alumnodb:alumnodb@localhost/si1", echo=False)
        db_conn = None
        db_conn = db_engine.connect()
        query="""CREATE TEMPORARY TABLE actualUKMovies
        AS (select m.movieid, movietitle, year from imdb_moviecountries natural join imdb_movies as m where country = 'UK' order by year desc limit 400)
        """
        db_result = db_conn.execute(text(query)) # ejecuto la creación de la tabla 

        query="""select q.movieid, genre from actualukmovies as q natural join imdb_moviegenres order by q.movieid asc"""
        db_result = db_conn.execute(text(query)) # ejecuto la query de genres 
        genres = list(db_result)

        query="""select q.movieid, directorname from actualukmovies as q natural join imdb_directormovies natural join imdb_directors order by q.movieid asc"""
        db_result = db_conn.execute(text(query)) # ejecuto la query de directors
        directors = list(db_result)

        query="""select q.movieid, actorname from actualukmovies as q natural join imdb_actormovies natural join imdb_actors order by q.movieid"""
        db_result = db_conn.execute(text(query)) # ejecuto la query de actors
        actors = list(db_result)

        query="Select movieid, movietitle, year from actualUKMovies ORDER BY movieid asc"
        db_result = db_conn.execute(text(query)) # ejecuto la query de la tabla temporal
        movies = list(db_result)
        films=[]
        for row in movies:
            genre=[]
            actor=[]
            director=[]
            while(i<len(genres) and genres[i]['movieid']==row['movieid']):
                genre.append(genres[i]['genre'])
                i+=1
            while(j<len(actors) and actors[j]['movieid']==row['movieid']):
                actor.append(actors[j]['actorname'])
                j+=1
            while(k<len(directors) and directors[k]['movieid']==row['movieid']):
                director.append(directors[k]['directorname'])
                k+=1
            
            title = row['movietitle'][:row['movietitle'].rfind('(')-1]

            pelicula={
                'title': title,
                'genres': genre,
                'year': row['year'],
                'directors': director,
                'actors': actor,
                'most_related_movies': [],
                'related_movies': []
            }
            films.append(pelicula)
        
        query="""drop table actualukmovies"""
        db_result = db_conn.execute(text(query)) # borrado de tabla temporal
        
        db_conn.close() #cerramos la conexión con la base de datos

        #most related
        num_films = len(films)
        for i in range(num_films):
            for j in range(num_films):
                if i != j:
                    set1 = set(films[i]['genres'])
                    set2 = set(films[j]['genres'])
                    intersection = set1.intersection(set2)
                    if len(intersection) == len(set1):
                        films[i]['most_related_movies'].append(
                            {'title': films[j]['title'],
                            'year': films[j]['year']})
                    elif len(intersection) >= round(len(set1) / 2, 0):
                        films[i]['related_movies'].append(
                            {'title': films[j]['title'],
                            'year': films[j]['year']})
            if len(films[i]['most_related_movies']) > 10:
                films[i]['most_related_movies'] = films[i]['most_related_movies'][:10]
            if len(films[i]['related_movies']) > 10:
                films[i]['related_movies'] = films[i]['related_movies'][:10]

        db_conn.close()    
        """engine = create_engine("mongodb://localhost/si1")
            if not database_exists(engine.url): #create database for mongo
                create_database(engine.url)
            conn = engine.connect()
            factory = sessionmaker(bind=engine)
            session = factory()
        """
        mydb = myclient["si1"]
        mycol = mydb["topUK"]
        mycol.insert_many(films)
        end = time()
        print("Inserted Succesful:")
        print(end - start)
        myclient.close()
        return

    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)
        print("Error en la creación de la base de datos")
        return -1

if __name__ == "__main__":
    create_mongoDB()
