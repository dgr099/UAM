CREATE OR REPLACE FUNCTION getTopActors(genre CHAR, OUT Actor CHAR,
	OUT Num INT, OUT Debut INT, OUT Film CHAR, OUT Director CHAR)
RETURNS SETOF RECORD
AS $$
DECLARE
	tupla RECORD;
BEGIN
	CREATE TEMPORARY TABLE genreMovies
	AS (SELECT movieid, movietitle, year
		FROM imdb_moviegenres as mg NATURAL JOIN imdb_movies
		WHERE mg.genre LIKE $1);
	CREATE TEMPORARY TABLE actorsGenreDebut
	AS (SELECT actorid, actorname, count(actorid) as genreMovies,
		min(year) as genreDebut
		FROM genreMovies NATURAL JOIN
			imdb_actormovies NATURAL JOIN
			imdb_actors
		GROUP BY actorid, actorname
		HAVING count(actorid) > 4);
	CREATE TEMPORARY TABLE topActors
	AS (SELECT q.actorname, q.genreMovies, q.genreDebut,
		q.movietitle, directorname
		FROM (SELECT q.actorname, q.genreMovies, q.genreDebut,
                m.movieid, m.movietitle
                FROM actorsGenreDebut as q NATURAL JOIN
    			imdb_actormovies NATURAL JOIN
	    		genreMovies as m
        		WHERE q.genreDebut = m.year) as q NATURAL JOIN
            imdb_directormovies NATURAL JOIN imdb_directors
		ORDER BY q.genreMovies DESC);
	FOR tupla IN SELECT * FROM topActors LOOP
		Actor := tupla.actorName;
		Num := tupla.genreMovies;
		Debut := tupla.genreDebut;
		Film := tupla.movieTitle;
		Director := tupla.directorName;
		RETURN NEXT;
	END LOOP;
	DROP TABLE genreMovies;
	DROP TABLE actorsGenreDebut;
	DROP TABLE topActors;
	RETURN;
END; $$
LANGUAGE plpgsql;
