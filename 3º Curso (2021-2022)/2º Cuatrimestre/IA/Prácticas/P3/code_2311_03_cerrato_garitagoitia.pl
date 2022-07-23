/***************
* EJERCICIO 2. sum_pot_prod/4
*
*	ENTRADA:
*		X: Vector de entrada de numeros de valor real.
*		Y: Vector de entrada de numeros de valor real.
*		Potencia: Numero de valor entero, potencia.
*	SALIDA:
*		Resultado: Numero de valor real resultado de la operacion sum_pot_prod. 
*
****************/
sum_pot_prod(_, _, P, _) :-
    P < 0, writeln('ERROR 1.1 Potencia'), !, fail.
sum_pot_prod([_|_], [], _, _) :-
    writeln('ERROR 1.2 Longitud'), !, fail.
sum_pot_prod([], [_|_], _, _) :-
    writeln('ERROR 1.2 Longitud'), !, fail.
    
sum_pot_prod([A], [B], P, R) :-
    Mul is A*B, R is Mul^P.
sum_pot_prod([A|L1], [B|L2], P, R) :-
    Mul is A*B, Pot is Mul^P, sum_pot_prod(L1, L2, P, Res), R is Res+Pot.
    

/***************
* EJERCICIO 3. segundo_penultimo/3
*
*       ENTRADA:
*               L: Lista de entrada de numeros de valor real.
*       SALIDA:
*               X : Numero de valor real. Segundo elemento.
*		Y : Numero de valor real. Penultimo elemento.
*
****************/
segundo_penultimo([_], _, _) :-
    writeln('ERROR 2.1 Longitud'), fail.
    
segundo_penultimo([A|[B]], B, A).
segundo_penultimo([A|[_]], _, Pen) :-
    Pen is A.
segundo_penultimo([_|[A|L1]], Seg, Pen) :-
    Seg is A, segundo_penultimo([A|L1], _, Pen).
    

/***************
* EJERCICIO 4. sublista/5
*
*       ENTRADA:
*		L: Lista de entrada de cadenas de texto.
*		Menor: Numero de valor entero, indice inferior.
*		Mayor: Numero de valor entero, indice superior.
*		E: Elemento, cadena de texto.
*       SALIDA:
*		Sublista: Sublista de salida de cadenas de texto.
*
****************/
sublista(L1, Menor, Mayor, _, _) :-
	(Menor > Mayor; Menor < 1; not(longitud_lista(L1, Mayor))),
	writeln('ERROR 3.2 Indices'), !, fail.
sublista(L, Menor, Mayor, E, SubL) :-
    generate(L, Menor, Mayor, SubL, E, 0).

longitud_lista([], Long) :-
    Long =< 0.
longitud_lista([_|L1], Long) :-
    Long2 is Long-1, longitud_lista(L1, Long2).

generate(_, 1, 0, [], _, 0) :-
	writeln('ERROR 3.1 Elemento'), !, fail.
generate(_, 1, 0, [], _, 1).

generate([A|L1], 1, Mayor, [A|L2], A, 0) :-
    Y is Mayor-1, Y > 0, generate(L1, 1, Y, L2, 0, 1).
generate([A|L1], 1, Mayor, [A|L2], E, Enc) :-
    Y is Mayor-1, Y >= 0, generate(L1, 1, Y, L2, E, Enc).
generate([_|L1], Menor, Mayor, L2, E, Enc) :-
    X is Menor-1, Y is Mayor-1, generate(L1, X, Y, L2, E, Enc).
    
    
/***************
* EJERCICIO 5. espacio_lineal/4
*
*       ENTRADA:
*               Menor: Numero de valor entero, valor inferior del intervalo.
*               Mayor: Numero de valor entero, valor superior del intervalo.
*               Numero_elementos: Numero de valor entero, numero de valores de la rejilla.
*       SALIDA:
*               Rejilla: Vector de numeros de valor real resultante con la rejilla.
*
****************/
espacio_lineal(Menor, Mayor, _, _) :-
    Menor > Mayor, writeln('ERROR 4.1 Indices'), !, fail.
espacio_lineal(Menor, Mayor, NumElems, [Menor|L]) :-
    Dif is Mayor-Menor, ElemsRest is NumElems-1, Incr is Dif/ElemsRest,
    MenorSig is Menor+Incr, espacio_lineal_aux(MenorSig, ElemsRest, Incr, L, Mayor).

espacio_lineal_aux(_, 1,_,[Mayor], Mayor).
espacio_lineal_aux(Menor, NumElems, Incr, [Menor|L], Mayor) :- 
    ElemsRest is NumElems-1, MenorSig is Menor+Incr,
    espacio_lineal_aux(MenorSig, ElemsRest, Incr, L, Mayor).


/***************
* EJERCICIO 6. normalizar/2
*
*       ENTRADA:
*		Distribucion_sin_normalizar: Vector de numeros reales de entrada. Distribucion sin normalizar.
*       SALIDA:
*		Distribucion: Vector de numeros reales de salida. Distribucion normalizada.
*
****************/
normalizar(DistrSinNorm, DistrNorm) :- 
    suma_elementos(DistrSinNorm, Total), normalizador(DistrSinNorm, Total, DistrNorm).
    
normalizador([A|_], _, _) :-
    A < 0,  writeln('ERROR 5.1. Negativos.'), !, fail.
    
normalizador([], _, []).
normalizador([A|L1], Total, [ANorm|L2]) :-
    ANorm is A/Total, normalizador(L1, Total, L2).

suma_elementos([A|L], Total) :-
    suma_elementos(L, Suma), Total is A+Suma.
suma_elementos([], Total) :-
    Total is 0.
    

/***************
* EJERCICIO 7. divergencia_kl/3
*
*       ENTRADA:
*		D1: Vector de numeros de valor real. Distribucion.
*		D2: Vector de numeros de valor real. Distribucion.
*       SALIDA:
*		KL: Numero de valor real. Divergencia KL.
*
****************/
divergencia_kl(D1, D2, _) :-
    es_distribucion(D1, Total1, D2, Total2), (Total1 \= 1.0; Total2 \= 1.0),
    writeln('ERROR 6.2. Divergencia KL definida solo para distribuciones'), !, fail.
divergencia_kl(D1, D2, KL) :-
    divergencia_kl_aux(D1, D2, KL).
    
es_distribucion([], Total1, [], Total2) :-
    Total1 is 0.0, Total2 is 0.0.
es_distribucion([A|L1], Total1, [B|L2], Total2) :-
    es_distribucion(L1, Suma1, L2, Suma2), Total1 is A+Suma1, Total2 is B+Suma2.
    
divergencia_kl_aux([A|_], [B|_], _) :-
    (A = 0.0; B = 0.0), writeln('ERROR 6.1. Divergencia KL no definida.'), !, fail. 

divergencia_kl_aux([A|L1], [B|L2], TotalKL) :-
    divergencia_kl_aux(L1, L2, KL), X is A/B,  Y is log(X), Z is A*Y, TotalKL is KL+Z.
divergencia_kl_aux([], [], TotalKL) :-
    TotalKL is 0.0.
    
    
/***************
* EJERCICIO 8. producto_kronecker/3
*
*       ENTRADA:
*		Matriz_A: Matriz de numeros de valor real.
*		Matriz_B: Matriz de numeros de valor real.
*       SALIDA:
*		Matriz_bloques: Matriz de bloques (matriz de matrices) de numeros reales.
*
****************/
producto_kronecker([], _, []).
producto_kronecker([FilaA|RestoMatrizA], MatrizB, [FilaBloques|RestoMatrizBloques]) :-
    recorrer_fila_A(FilaA, MatrizB, FilaBloques),
    producto_kronecker(RestoMatrizA, MatrizB, RestoMatrizBloques).

recorrer_fila_A([], _, []).
recorrer_fila_A([A|_], _, _) :-
    A < 0, writeln('ERROR 7.1 Elemento menor que cero'), !, fail.
recorrer_fila_A([A|L1], MatrizB, [Bloque|RestoBloques]) :-
    recorrer_matriz_B(A, MatrizB, Bloque), recorrer_fila_A(L1, MatrizB, RestoBloques).

recorrer_matriz_B(_, [], []).
recorrer_matriz_B(A, [FilaB|RestoMatrizB], [FilaBloque|RestoFilasBloque]) :-
    producto_A_fila_B(A, FilaB, FilaBloque), recorrer_matriz_B(A, RestoMatrizB, RestoFilasBloque).

producto_A_fila_B(_, [], []).
producto_A_fila_B(_, [B|_], _) :-
    B < 0, writeln('ERROR 7.1 Elemento menor que cero'), !, fail.
producto_A_fila_B(A, [B|L2], [C|LBloque]) :-
    C is A*B, producto_A_fila_B(A, L2, LBloque). 


/***************
* EJERCICIO 9a. distancia_euclidea/3
*
*       ENTRADA:
*               X1: Vector de numeros de valor real. 
*               X2: Vector de numeros de valor real.
*       SALIDA:
*               D: Numero de valor real. Distancia euclidea.
*
****************/
distancia_euclidea(V1, V2, DistEuc) :-
    suma(V1, V2, Total), DistEuc is (Total)^(1/2).

suma([], [], 0.0).
suma([A|L1], [B|L2], Total) :-
    X is (A-B)^2, suma(L1, L2, Suma), Total is Suma+X.
    

/***************
* EJERCICIO 9b. calcular_distancias/3
*
*       ENTRADA:
*               X_entrenamiento: Matriz de numeros de valor real donde cada fila es una instancia representada por un vector.
*               X_test: Matriz de numeros de valor real donde cada fila es una instancia representada por un vector. Instancias sin etiquetar.
*       SALIDA:
*               Matriz_resultados: Matriz de numeros de valor real donde cada fila es un vector con la distancia de un punto de test al conjunto de entrenamiento X_entrenamiento.
*
****************/
calcular_distancias(_, [], []).
calcular_distancias(VectoresEntrena, [VectorTest|RestVectTest], [VectorResult|RestVectResult]) :-
    calcular_distancias_aux(VectoresEntrena, VectorTest, VectorResult),
    calcular_distancias(VectoresEntrena, RestVectTest, RestVectResult).

calcular_distancias_aux([], _, []).
calcular_distancias_aux([VectorEntrena|RestVectEntrena], VectorTest, [Dist|RestDists]) :-
    distancia_euclidea(VectorEntrena, VectorTest, Dist),
    calcular_distancias_aux(RestVectEntrena, VectorTest, RestDists).


/***************
* EJERCICIO 9c. predecir_etiquetas/4
*
*       ENTRADA:
*               Y_entrenamiento: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_entrenamiento.
*               K: Numero de valor entero.
*               Matriz_resultados: Matriz de numeros de valor real donde cada fila es un vector con la distancia de un punto de test al conjunto de entrenamiento X_entrenamiento.
*       SALIDA:
*               Y_test: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_test.
*
****************/
predecir_etiquetas(_, _, [], []).
predecir_etiquetas(Y_entrenamiento, K, [VDist|RestoVsDist], [Etiqueta|RestoEtiquetas]) :-
    predecir_etiquetas(Y_entrenamiento, K, RestoVsDist, RestoEtiquetas),
    predecir_etiqueta(Y_entrenamiento, K, VDist, Etiqueta).


/***************
* EJERCICIO 9d. predecir_etiqueta/4
*
*       ENTRADA:
*               Y_entrenamiento: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_entrenamiento.
*               K: Numero de valor entero.
*               Vec_distancias: Vector de valores reales correspondiente a una fila de Matriz_resultados.
*       SALIDA:
*               Etiqueta: Elemento de valor alfanumerico.
*
****************/
predecir_etiqueta(Y_entrenamiento, K, Vec_distancias, Etiqueta) :-
    calcular_K_etiquetas_mas_relevantes(Y_entrenamiento, K, Vec_distancias, Etiquetas),
    calcular_etiqueta_mas_relevante(Etiquetas, Etiqueta).


/***************
* EJERCICIO 9e. calcular_K_etiquetas_mas_relevantes/4
*
*       ENTRADA:
*               Y_entrenamiento: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_entrenamiento.
*               K: Numero de valor entero.
*               Vec_distancias: Vector de valores reales correspondiente a una fila de Matriz_resultados.
*       SALIDA:
*		K_etiquetas: Vector de valores alfanumericos de una distribucion categorica.
*
****************/
calcular_K_etiquetas_mas_relevantes(Y_entrenamiento, K, Vec_distancias, Etiquetas) :-
    insertar_ordenados(Vec_distancias, _, Y_entrenamiento, Aux2),
    reducir(Aux2, K, Etiquetas).

% reducir simplemente se encarga de cortar en el número k de vecinos que serán las etiquetas
reducir(_, 0, []).
reducir([A|L1], K, [A|L2]) :-
    KSig is K-1, reducir(L1, KSig, L2).

% insertar_ordenados sirve para insertar las apariciones en orden,
% guardando en Aux2 la lista de los tags en ese orden
insertar_ordenados([], [], [], []).

%en aux2 tienes una lista ordenada hasta B, toca insertar A
%lo mismo con las letras
insertar_ordenados([A|B], Aux, [C|D], Aux3) :-
    insertar_ordenados(B, Aux2, D, Aux4), insertar(Aux, A, Aux2, Aux3, C, Aux4).

%en aux copias aux2 insertando a
%mientras a sea mayor sigues copiando
insert([A|B], D, [A|C], [E|F], H, [E|I]):-
    D > A, insert(B, D, C, F, H, I).

%en el momento que sea igual o menor copias la a entre medias
insert([B|C], B, C, [D|E], D, E).

%cuando hemos recorrido toda la anterior lista
%y es un elemento mayor, lo ponemos al final
insert([A], A, [], [B], B, []).



/***************
* EJERCICIO 9f. calcular_etiqueta_mas_relevante/2
*
*       ENTRADA:
*               K_etiquetas: Vector de valores alfanumericos de una distribucion categorica.
*       SALIDA:
*               Etiqueta: Elemento de valor alfanumerico.
*
****************/
calcular_etiqueta_mas_relevante(K_etiquetas, E) :-
    calcular_etiqueta_mas_relevante_aux(k_etiquetas, Temp2), max(Temp2, _, E).


calcular_etiqueta_mas_relevante_aux([], []).
calcular_etiqueta_mas_relevante_aux([A|B], Temp2) :-
    calcular_etiqueta_mas_relevante_aux(B, Temp), incrementar(Temp, A, Temp2). 

% max(lista, nº apariciones del mayor, elemento del mayor)
max([], C, _):- C is 0.

% Si es mayor que el último máximo, cambiamos los máximos
max([[E|F]|B], C, D) :-
    max(B, G, H), (F > G -> C is F, D = E; F =< G -> C is G, D = H).  	

% Si hemos recorrido toda la lista sin encontrarlo, lo insertamos con 1
incrementar([], E, [[E,1]]).

% Si encontramos el elemento en la lista antigua, la nueva lista tendrá la apariencia más una
incrementar([[H,C]|T], H, [[H,C1]|T]) :-
    C1 is C + 1.

% Mientras no la encontremos, vamos copiando lo de la lista anterior en la nueva lista
incrementar([[H,C]|T], E, [[H,C]|R]) :-
    incrementar(T, E, R).


/***************
* EJERCICIO 9g. k_vecinos_proximos/5
*
*       ENTRADA:
*		X_entrenamiento: Matriz de numeros de valor real donde cada fila es una instancia representada por un vector.
*		Y_entrenamiento: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_entrenamiento.
*		K: Numero de valor entero.
*		X_test: Matriz de numeros de valor real donde cada fila es una instancia representada por un vector. Instancias sin etiquetar.
*       SALIDA:
*		Y_test: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_test.
*
****************/
k_vecinos_proximos(X_entrenamiento, Y_entrenamiento, K, X_test, Y_test) :-
    calcular_distancias(X_entrenamiento, X_test, Matriz),
    predecir_etiquetas(Y_entrenamiento, K, Matriz, Y_test).


/***************
* EJERCICIO 9h. clasifica_patrones/4
*
*       ENTRADA:
*		iris_patrones.csv: Fichero con los patrones a clasificar, disponible en Moodle.
*		iris_etiquetas.csv: Fichero con las etiquetas de los patrones a clasificar, disponible en Moodle.
*		K: Numero de valor entero.
*       SALIDA:
*		tasa_aciertos: Tasa de acierto promediada sobre las iteraciones leave-one-out
*
****************/
clasifica_patrones('iris_patrones.csv','iris_etiquetas.csv',K,Tasa_aciertos) :-
    print('Error. Este ejercicio no esta implementado todavia.'), !, fail.