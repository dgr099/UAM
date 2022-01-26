%{
    #include "alfa.h"
    #include "y.tab.h"
    #include "sym_t.h"
    #include "sym_info.h"
    #include "generacion.h"

    #include <stdio.h>
    #include <stdlib.h>

    /* Imprime err_msg si no se cumple la condicion cond */
    #define CHECK_ERROR(cond, err_msg) \
        F_BLOCK( \
            if(!(cond)){ \
            fprintf(alfa_utils_T.ferr, "****Error semantico en lin %d[%d]: %s\n", \
                    (alfa_utils_T.line), \
                    (alfa_utils_T.col), \
                    (err_msg)); \
             YYABORT; \
            } \
        )

    #define TAM_ERRMSG 200
    #define INT_TO_CHAR 16
    
    /* Imprime regla gramatical en un fichero de debug */
    #define P_RULE(n, msg) \
        F_BLOCK( \
            fprintf(alfa_utils_T.fdbg, ";R%d:\t%s\n", (n), (msg)); \
        )

    int yyerror(char *s)
    {
        NO_USO(s);
        /* Si imprime un error morfologico, no debe imprimir uno sintactico */
        if (alfa_utils_T.error == ERR_MORFOLOGICO)
            return 0;

        alfa_utils_T.error = ERR_SINTACTICO;
        manage_error(NULL, NULL);
        return 1;
    }

    /* Para declaraciones */
    static Tipo tipo_actual;
    static Categoria clase_actual;

    /* Para vectores */
    static int tamanio_vector_actual = 0;

    /* Etiquetas */
    static int etiqueta = 1;

    /* Funciones */
    static int pos_parametro_actual = UNDEFINED;
    static int num_parametros_actual = 0;
    static int num_variables_locales_actual = 0;
	static int pos_variable_local_actual = 0;
    static Tipo tipo_retorno_actual = UNDEFINED;

    /* 
    Para ver que toda funcion tiene al menos un return
    Y que un return solo puede estar en el cuerpo de una funcion
    */
	static int hay_return = 0;
    static int dentro_de_fun = 0;

    /*
    Para evitar llamadas a funciones como parametros
    */
	static int en_explist = 0;
%}

%union {
    tipo_atributos atributos;
}

/* Palabras reservadas */ 
%token TOK_MAIN               
%token TOK_INT                
%token TOK_BOOLEAN            
%token TOK_ARRAY              
%token TOK_FUNCTION           
%token TOK_IF                 
%token TOK_ELSE               
%token TOK_WHILE              
%token TOK_SCANF              
%token TOK_PRINTF             
%token TOK_RETURN             

          
%token TOK_AND                
%token TOK_OR               
%token TOK_IGUAL              
%token TOK_DISTINTO           
%token TOK_MENORIGUAL         
%token TOK_MAYORIGUAL            

%token <atributos> TOK_IDENTIFICADOR
%token <atributos> TOK_CONSTANTE_ENTERA   
%token TOK_TRUE               
%token TOK_FALSE             

%token TOK_ERROR


%type <atributos> condicional
%type <atributos> comparacion
%type <atributos> elemento_vector
%type <atributos> exp
%type <atributos> constante
%type <atributos> constante_entera
%type <atributos> constante_logica
%type <atributos> identificador_new identificador_use idpf funcion fn_name fn_declaration
%type <atributos> llamada_funcion
%type <atributos> lista_expresiones resto_lista_expresiones

%type <atributos> if_exp if_sentencias
%type <atributos> bucle
%type <atributos> bucle_exp bucle_tok

%left '+' '-' TOK_OR
%left '*' '/' TOK_AND 
%right NEG '!'

%start programa

%%

/* Seccion de reglas */

programa : TOK_MAIN '{' iniciar declaraciones dec_vars funciones wrt_main sentencias final '}' {P_RULE(1,"<programa> ::= main { <declaraciones> <funciones> <sentencias> }");};

iniciar :  {
                sym_t_create();
                escribir_cabecera_presentacion(alfa_utils_T.fasm, alfa_utils_T.fin_name);
                escribir_subseccion_data(alfa_utils_T.fasm);
                escribir_cabecera_bss(alfa_utils_T.fasm);
            }

final :    {
                sym_t_free();
                escribir_fin(alfa_utils_T.fasm);
            }

dec_vars:   {
                char** simbolos = sym_t_getGlobalSymbols();
                int i = 0;
                sym_info* sym = NULL;
                for (i = 0; simbolos[i] != NULL; i++) {
                    sym = sym_t_get_symb(simbolos[i]);
                    if (sym && VARIABLE == sym->elem)
                        declarar_variable(alfa_utils_T.fasm, sym->lexema, sym->tipo, sym->size);
                }
                escribir_segmento_codigo(alfa_utils_T.fasm);
            }

wrt_main:   {   escribir_inicio_main(alfa_utils_T.fasm);}

declaraciones : declaracion {P_RULE(2,"<declaraciones> ::= <declaracion>");}
              |   declaracion declaraciones {P_RULE(3,"<declaraciones> ::= <declaracion> <declaraciones>");};

declaracion : clase identificadores ';' {P_RULE(4,"<declaracion> ::= <clase> <identificadores> ;");};

clase : clase_escalar {
            P_RULE(5,"<clase> ::= <clase_escalar>");
            clase_actual = ESCALAR;
        }
      | clase_vector {
          P_RULE(7,"<clase> ::= <clase_vector>");
          clase_actual = VECTOR;
        };

clase_escalar : tipo {P_RULE(9,"<clase_escalar> ::= <tipo>");};

tipo : TOK_INT {
            P_RULE(10,"<tipo> ::= int"); 
            tipo_actual = INT;
        }
     | TOK_BOOLEAN {
            P_RULE(11,"<tipo> ::= boolean");
            tipo_actual = BOOLEAN;
        };

clase_vector : TOK_ARRAY tipo '[' TOK_CONSTANTE_ENTERA ']' {
        P_RULE(15,"<clase_vector> ::= array <tipo> [ constante_entera ]");
        tamanio_vector_actual = $4.valor_entero;
        CHECK_ERROR(tamanio_vector_actual >= 1, "El tamanyo del vector excede los limites permitidos (1,64)");
        CHECK_ERROR(tamanio_vector_actual <= MAX_LONG_VECTOR, "El tamanyo del vector excede los limites permitidos (1,64)");
        CHECK_ERROR(dentro_de_fun == 0, "Variable local de tipo no escalar");
    };

identificadores : identificador_new {P_RULE(18,"<identificadores> ::= <identificador>");}
                | identificador_new ',' identificadores {P_RULE(19,"<identificadores> ::= <identificador> , <identificadores>");};

funciones : funcion funciones {P_RULE(20,"<funciones> ::= <funcion> <funciones>");}
          | /* lambda */ {P_RULE(21,"<funciones> ::=");};

funcion : fn_declaration sentencias '}' {
            char err_msg[TAM_ERRMSG] = "";
            P_RULE(22,"<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }");

            /* Cerrar ambito actual */
            close_scope();
            dentro_de_fun = 0;

            sprintf(err_msg, "Funcion [%s] sin sentencia de retorno", $1.lexema);
            /* Comprobar si hay al menos un retorno */
            CHECK_ERROR(hay_return != 0, err_msg);
        };

fn_declaration : fn_name '(' parametros_funcion ')' '{' declaraciones_funcion {
                    sym_info *sym = sym_t_get_symb($1.lexema);
                    
                    sym->num_params = num_parametros_actual;
                    sym->num_vars_loc = num_variables_locales_actual;
                    $$ = $1;
                    declararFuncion(alfa_utils_T.fasm, $1.lexema, num_variables_locales_actual);
                };

fn_name : TOK_FUNCTION tipo identificador_use {
            sym_info *sym = sym_t_get_symb($3.lexema);
            CHECK_ERROR(sym == NULL, "Funcion declarada previamente");

            /* Abrimos un nuevo ambito */
            open_scope($3.lexema, UNDEFINED, tipo_actual);
            
            /* Inicializar variables globales */
            num_variables_locales_actual = 0;
            pos_variable_local_actual = 0;
            num_parametros_actual = 0;
            pos_parametro_actual = 0;
            tipo_retorno_actual = tipo_actual;

            $$ = $3;
            dentro_de_fun = 1;
            hay_return = 0;
        };

parametros_funcion : parametro_funcion resto_parametros_funcion {P_RULE(23,"<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>");}
                   | /* lambda */ {P_RULE(24,"<parametros_funcion> ::=");};

resto_parametros_funcion : ';' parametro_funcion resto_parametros_funcion {P_RULE(25,"<resto_parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>");}
                         | /* lambda */ {P_RULE(26,"<resto_parametros_funcion> ::=");};

idpf : identificador_use {
        $$ = $1;
        clase_actual = ESCALAR;
     };

parametro_funcion : tipo idpf {
            P_RULE(27,"<parametro_funcion> ::= <tipo> <identificador>");
            
            sym_info *sym = sym_t_check($2.lexema);
            CHECK_ERROR(sym == NULL, "Parametro declarado previamente");

            sym = sym_info_create($2.lexema, PARAMETRO, tipo_actual, clase_actual, 0, pos_parametro_actual);
            CHECK_ERROR(sym, "Sin memoria");
            
            sym_t_add_symb(sym);

            pos_parametro_actual++;
            num_parametros_actual++;
        };

declaraciones_funcion : declaraciones {P_RULE(28,"<declaraciones_funcion> ::= <declaraciones>");}
                      | /* lambda */ {P_RULE(29,"<declaraciones_funcion> ::=");};

sentencias : sentencia {P_RULE(30,"<sentencias> ::= <sentencia>");}
           | sentencia sentencias {P_RULE(31,"<sentencias> ::= <sentencia> <sentencias>");};

sentencia : sentencia_simple ';' {P_RULE(32,"<sentencia> ::= <sentencia_simple> ;");}
          | bloque {P_RULE(33,"<sentencia> ::= <bloque>");};

sentencia_simple : asignacion {P_RULE(34,"<sentencia_simple> ::= <asignacion>");}
                 | lectura {P_RULE(35,"<sentencia_simple> ::= <lectura>");}
                 | escritura {P_RULE(36,"<sentencia_simple> ::= <escritura>");}
                 | retorno_funcion {P_RULE(38,"<sentencia_simple> ::= <retorno_funcion>");};

bloque : condicional {P_RULE(40,"<bloque> ::= <condicional>");}
       | bucle {P_RULE(41,"<bloque> ::= <bucle>");};

asignacion  : identificador_use '=' exp {
                char err_msg[TAM_ERRMSG] = "";
                sym_info* sym = NULL;

                P_RULE(43,"<asignacion> ::= identificador = <exp>");

                /* Comprueba que exista el identificador */
                sprintf(err_msg, "Identificador [%s] inexistente", $1.lexema);
                sym = sym_t_get_symb($1.lexema);
                CHECK_ERROR(sym != NULL, err_msg);

                /* Comprueba que no sea ni FUNCION ni VECTOR */
                sprintf(err_msg, "Identificador [%s] no es variable", $1.lexema);
                CHECK_ERROR(sym->catg != VECTOR, err_msg);
                CHECK_ERROR(sym->elem != FUNCION, err_msg);

                /* Comprueba que el tipo sea el mismo */
                CHECK_ERROR($3.tipo == sym->tipo, "Asignacion incompatible");

                /* Asignar */
                if (sym->is_var_loc == UNDEFINED) { /*comprueba si es variable local */
                    asignar(alfa_utils_T.fasm, $1.lexema, $3.es_direccion);

                } else if (sym->elem == PARAMETRO) {
                    asignarParametro(alfa_utils_T.fasm, $3.es_direccion, sym->pos_param, num_parametros_actual);
                } else {
                    asignarVariableLocal(alfa_utils_T.fasm, $3.es_direccion, sym->pos_var_loc);
                }
            }
            | elemento_vector '=' exp {
                sym_info* sym = NULL;
                P_RULE(44,"<asignacion> ::= <elemento_vector> = <exp>");

                sym = sym_t_get_symb($1.lexema);
                CHECK_ERROR(sym != NULL, "Identificador inexistente");
                /* Comprueba que el tipo sea el mismo */
                CHECK_ERROR($3.tipo == sym->tipo, "Asignacion incompatible");

                escribir_elemento_vector(alfa_utils_T.fasm, $3.lexema, sym->size, sym->elem);
            };

elemento_vector : identificador_use '[' exp ']' {
                    sym_info* info = NULL;
                    char err_msg[TAM_ERRMSG] = "";
                    P_RULE(48,"<elemento_vector> ::= identificador [ <exp> ]");
                    
                    sprintf(err_msg, "Identificador [%s] inexistente", $1.lexema);
                    info = sym_t_get_symb($1.lexema);
                    CHECK_ERROR(info != NULL, err_msg); 
                    CHECK_ERROR(info->catg == VECTOR, "Intento de indexacion de una variable que no es de tipo vector");
                    CHECK_ERROR($3.tipo == INT, "El indice en una operacion de indexacion tiene que ser de tipo entero");

                    comprobar_indice_vector(alfa_utils_T.fasm, $1.lexema, $3.es_direccion, info->size);

                    $$.tipo = info->tipo;
                    $$.es_direccion = 1;
                };

condicional : if_sentencias {
                /* IF THEN, ELSE VACIO */
                P_RULE(50,"<condicional> ::= if ( <exp> ) { <sentencias> }");
                ifthenelse_fin(alfa_utils_T.fasm, $1.etiqueta);
            }
            | if_sentencias TOK_ELSE '{' sentencias '}'{
                /* IF THEN, ELSE CON COSAS */
                P_RULE(51,"<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }");
                ifthenelse_fin(alfa_utils_T.fasm, $1.etiqueta);
            };

if_sentencias : if_exp sentencias '}' {
                    $$.etiqueta = $1.etiqueta;
                    ifthenelse_fin_then(alfa_utils_T.fasm, $$.etiqueta);
                }

if_exp  :   TOK_IF '(' exp ')' '{' {
                CHECK_ERROR($3.tipo == BOOLEAN, "Condicional con condicion de tipo int");
                $$.etiqueta = etiqueta++;
                ifthen_inicio(alfa_utils_T.fasm, $3.es_direccion, $$.etiqueta);
            }

bucle : bucle_exp sentencias '}' {
            P_RULE(52,"<bucle> ::= while ( <exp> ) { <sentencias> }");
            while_fin(alfa_utils_T.fasm, $1.etiqueta);
        };

bucle_exp : bucle_tok '(' exp ')' '{' {
            CHECK_ERROR($3.tipo == BOOLEAN, "Bucle con condicion de tipo int");
            while_exp_pila(alfa_utils_T.fasm, $3.es_direccion, $$.etiqueta);
          }

bucle_tok : TOK_WHILE {
            $$.etiqueta = etiqueta++;
            while_inicio(alfa_utils_T.fasm, $$.etiqueta);
          }

lectura : TOK_SCANF identificador_use {
            char err_msg[TAM_ERRMSG] = "";
            P_RULE(54,"<lectura> ::= scanf identificador"); 

            sprintf(err_msg, "Identificador [%s] no existe", $2.lexema);
            sym_info* info = sym_t_check($2.lexema);
            CHECK_ERROR(info, err_msg);
            CHECK_ERROR((info->elem != FUNCION), "scanf no admite funciones como entrada");
            CHECK_ERROR((info->catg != VECTOR), "scanf no admite vectores como entrada");

            if (info->is_var_loc == UNDEFINED) {
                leer(alfa_utils_T.fasm, info->lexema, info->tipo, 1);
            }
            else if (info->elem == PARAMETRO) {
                escribirParametro(alfa_utils_T.fasm, 1, info->pos_param, num_parametros_actual);
                leer(alfa_utils_T.fasm, info->lexema, info->tipo, 0);
            } else if (info->elem == VARIABLE && info->is_var_loc == 1) {
                escribirVariableLocal(alfa_utils_T.fasm, 1, info->pos_var_loc);
                leer(alfa_utils_T.fasm, info->lexema, info->tipo, 0);
            }
        };

escritura : TOK_PRINTF exp {
                P_RULE(56,"<escritura> ::= printf <exp>");
                escribir(alfa_utils_T.fasm, $2.es_direccion, $2.tipo);
          };

retorno_funcion : TOK_RETURN exp {
                    P_RULE(61,"<retorno_funcion> ::= return <exp>");
                    
                    CHECK_ERROR(dentro_de_fun == 1, "Sentencia de retorno fuera del cuerpo de una funcion");
                    CHECK_ERROR($2.tipo == tipo_retorno_actual, "Retorno de funcion de tipo incompatible");
                    
                    retornarFuncion(alfa_utils_T.fasm, $2.es_direccion);
                    hay_return++;
                };

exp : exp '+' exp {
        P_RULE(72,"<exp> ::= <exp> + <exp>");
        
        CHECK_ERROR($1.tipo == INT && $3.tipo == INT, "Operacion aritmetica con operandos boolean");
        sumar(alfa_utils_T.fasm, $1.es_direccion, $3.es_direccion);

        $$.tipo = INT;
        $$.es_direccion = 0;
    }
    | exp '-' exp {
        P_RULE(73,"<exp> ::= <exp> - <exp>");

        CHECK_ERROR($1.tipo == INT && $3.tipo == INT, "Operacion aritmetica con operandos boolean");
        restar(alfa_utils_T.fasm, $1.es_direccion, $3.es_direccion);

        $$.tipo = INT;
        $$.es_direccion = 0;
    }
    | exp '/' exp {
        P_RULE(74,"<exp> ::= <exp> / <exp>");
        
        CHECK_ERROR($1.tipo == INT && $3.tipo == INT, "Operacion aritmetica con operandos boolean");
        dividir(alfa_utils_T.fasm, $1.es_direccion, $3.es_direccion);

        $$.tipo = INT;
        $$.es_direccion = 0;
    }
    | exp '*' exp {
        P_RULE(75,"<exp> ::= <exp> * <exp>");
        
        CHECK_ERROR($1.tipo == INT && $3.tipo == INT, "Operacion aritmetica con operandos boolean");
        multiplicar(alfa_utils_T.fasm, $1.es_direccion, $3.es_direccion);

        $$.tipo = INT;
        $$.es_direccion = 0;
    }
    | '-' %prec NEG exp {
        P_RULE(76,"<exp> ::= - <exp>");

        CHECK_ERROR($2.tipo == INT, "Operacion aritmetica con operando boolean");
        /*check*/
        cambiar_signo(alfa_utils_T.fasm, $2.es_direccion);

        $$.tipo = INT;
        $$.es_direccion = 0;    
    }
    | exp TOK_AND exp {
        P_RULE(77,"<exp> ::= <exp> && <exp>");

        CHECK_ERROR($1.tipo == BOOLEAN && $3.tipo == BOOLEAN, "Operacion logica con operandos int");
        y(alfa_utils_T.fasm, $1.es_direccion, $3.es_direccion);

        $$.tipo = BOOLEAN;
        $$.es_direccion = 0; 
    }
    | exp TOK_OR exp {
        P_RULE(78,"<exp> ::= <exp> || <exp>");
        
        CHECK_ERROR($1.tipo == BOOLEAN && $3.tipo == BOOLEAN, "Operacion logica con operandos int");
        o(alfa_utils_T.fasm, $1.es_direccion, $3.es_direccion);

        $$.tipo = BOOLEAN;
        $$.es_direccion = 0;
    }
    | '!' exp {
        P_RULE(79,"<exp> ::= ! <exp>");
        
        CHECK_ERROR($2.tipo == BOOLEAN, "Operacion logica con operando int");
        no(alfa_utils_T.fasm, $2.es_direccion, etiqueta++);

        $$.tipo = BOOLEAN;
        $$.es_direccion = 0;  
    }
    | identificador_use {
        char err_msg[TAM_ERRMSG] = "";
        sym_info* sym = NULL;

        P_RULE(80,"<exp> ::= identificador");

        sym = sym_t_get_symb($1.lexema);
        sprintf(err_msg, "Variable [%s] no declarada", $1.lexema);
        CHECK_ERROR(sym != NULL, err_msg);
        /* Comprueba que no sea ni FUNCION ni VECTOR */
        sprintf(err_msg, "Identificador [%s] no es variable", $1.lexema);
        CHECK_ERROR(sym->catg != VECTOR, err_msg);
        CHECK_ERROR(sym->elem != FUNCION, err_msg);

        $$.tipo = sym->tipo;
        $$.es_direccion = 0;

        /* Variable global */
        if (sym->elem == VARIABLE && sym->is_var_loc == UNDEFINED) {
            escribir_operando(alfa_utils_T.fasm, $1.lexema, 1);
        /* Parametro */
        } else if (sym->elem == PARAMETRO) {
            escribirParametro(alfa_utils_T.fasm, 0, sym->pos_param, num_parametros_actual);
        /* Variable local */
        } else if (sym->elem == VARIABLE && sym->is_var_loc != UNDEFINED) {
            escribirVariableLocal(alfa_utils_T.fasm, 0, sym->pos_var_loc);
        }
    }
    | constante {
            P_RULE(81,"<exp> ::= <constante>");

            $$.tipo = $1.tipo;
            $$.es_direccion = $1.es_direccion;
            
            char valor[INT_TO_CHAR];
            sprintf(valor, "%d", $1.valor_entero);
            escribir_operando(alfa_utils_T.fasm, valor, 0);
    }
    | '(' exp ')' {
            P_RULE(82,"<exp> ::= ( <exp> )");

            $$.tipo = $2.tipo;
            $$.es_direccion = $2.es_direccion;
    }
    | '(' comparacion ')' {
            P_RULE(83,"<exp> ::= ( <comparacion> )");

            $$.tipo = $2.tipo;
            $$.es_direccion = $2.es_direccion;
    }
    | elemento_vector {
            P_RULE(85,"<exp> ::= <elemento_vector>");

            apilar_valor_elemento_vector(alfa_utils_T.fasm);

            $$.tipo = $1.tipo;
            $$.es_direccion = 0;

    }
    | llamada_funcion '(' lista_expresiones ')' {
            sym_info* sym = NULL;

            P_RULE(88,"<identificador> ( <lista_expresiones> )");

            sym = sym_t_check($1.lexema);
            CHECK_ERROR(sym != NULL, "Identificador de funcion no declarada");
            CHECK_ERROR(sym->elem == FUNCION, "No es una funcion");
            CHECK_ERROR($3.num_parametros_llamada_actual == sym->num_params, "Numero incorrecto de parametros en llamada a funcion");
            
            llamarFuncion(alfa_utils_T.fasm, $1.lexema, $3.num_parametros_llamada_actual);
            
            en_explist = 0;

            $$.tipo = sym->tipo;
            $$.es_direccion = 0;
    };

llamada_funcion: identificador_use {
                        /* 
                        Para contorlar que no se invoque a funciones en una
                        lista de paramteros de otra invocacion
                        */
                        CHECK_ERROR(en_explist == 0, "No esta permitido el uso de llamadas a funciones como parametros de otras funciones");
                        en_explist = 1;
                    };

lista_expresiones : exp resto_lista_expresiones {
                        P_RULE(89,"<lista_expresiones> ::= <exp> <resto_lista_expresiones>");
                        $$.num_parametros_llamada_actual = $2.num_parametros_llamada_actual + 1;
                    }
                  | /* lambda */ {
                      P_RULE(90,"<lista_expresiones> ::=");
                      $$.num_parametros_llamada_actual = 0;
                    };

resto_lista_expresiones : ',' exp resto_lista_expresiones {
                        P_RULE(91,"<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>");
                        $$.num_parametros_llamada_actual = $3.num_parametros_llamada_actual + 1;
                    }
                        | /* lambda */ {
                            P_RULE(92,"<resto_lista_expresiones> ::=");
                            $$.num_parametros_llamada_actual = 0;
                        };

comparacion : exp TOK_IGUAL exp {
                P_RULE(93,"<comparacion> ::= <exp> == <exp>");

                CHECK_ERROR($1.tipo == INT && $3.tipo == INT, "Comparacion con operandos boolean");
                igual(alfa_utils_T.fasm, $1.es_direccion, $3.es_direccion, etiqueta++);

                $$.tipo = BOOLEAN;
                $$.es_direccion = 0;
            }
            | exp TOK_DISTINTO exp {
                P_RULE(94,"<comparacion> ::= <exp> != <exp>");
                
                CHECK_ERROR($1.tipo == INT && $3.tipo == INT, "Comparacion con operandos boolean");
                distinto(alfa_utils_T.fasm, $1.es_direccion, $3.es_direccion, etiqueta++);
                
                $$.tipo = BOOLEAN;
                $$.es_direccion = 0;
            }
            | exp TOK_MENORIGUAL exp {
                P_RULE(95,"<comparacion> ::= <exp> <= <exp>");
                
                CHECK_ERROR($1.tipo == INT && $3.tipo == INT, "Comparacion con operandos boolean");
                menor_igual(alfa_utils_T.fasm, $1.es_direccion, $3.es_direccion, etiqueta++);
                
                $$.tipo = BOOLEAN;
                $$.es_direccion = 0;
            }
            | exp TOK_MAYORIGUAL exp {
                P_RULE(96,"<comparacion> ::= <exp> >= <exp>");

                CHECK_ERROR($1.tipo == INT && $3.tipo == INT, "Comparacion con operandos boolean");
                mayor_igual(alfa_utils_T.fasm, $1.es_direccion, $3.es_direccion, etiqueta++);

                $$.tipo = BOOLEAN;
                $$.es_direccion = 0;
            }
            | exp '<' exp {
                P_RULE(97,"<comparacion> ::= <exp> < <exp>");
                
                CHECK_ERROR($1.tipo == INT && $3.tipo == INT, "Comparacion con operandos boolean");
                menor(alfa_utils_T.fasm, $1.es_direccion, $3.es_direccion, etiqueta++);
                
                $$.tipo = BOOLEAN;
                $$.es_direccion = 0;
            }
            | exp '>' exp {
                P_RULE(98,"<comparacion> ::= <exp> > <exp>");

                CHECK_ERROR($1.tipo == INT && $3.tipo == INT, "Comparacion con operandos boolean");
                mayor(alfa_utils_T.fasm, $1.es_direccion, $3.es_direccion, etiqueta++);
                
                $$.tipo = BOOLEAN;
                $$.es_direccion = 0;
            };

constante : constante_logica {
                P_RULE(99,"<constante> ::= <constante_logica>");
                $$.tipo = $1.tipo;
                $$.es_direccion = $1.es_direccion;
            }
          | constante_entera {
                P_RULE(100,"<comparacion> ::= <constante_entera>");
                $$.tipo = $1.tipo;
                $$.es_direccion = $1.es_direccion;
            };

constante_logica : TOK_TRUE {
                        P_RULE(102,"<constante_logica> ::= true");
                        $$.tipo = BOOLEAN;
                        $$.es_direccion = 0;
                        $$.valor_entero = 1;
                    }
                 | TOK_FALSE {
                        P_RULE(103,"<constante_logica> ::= false");
                        $$.tipo = BOOLEAN;
                        $$.es_direccion = 0;
                        $$.valor_entero = 0;
                    };

constante_entera : TOK_CONSTANTE_ENTERA {
                        P_RULE(104,"<constante_entera> ::= TOK_CONSTANTE_ENTERA");
                        $$.tipo = INT;
                        $$.es_direccion = 0;
                        $$.valor_entero = $1.valor_entero;
                    };

identificador_use: TOK_IDENTIFICADOR
                {
                    P_RULE(108,"<identificador> ::= TOK_IDENTIFICADOR");
                    $$ = $1;
                }

identificador_new : TOK_IDENTIFICADOR {
        char err_msg[TAM_ERRMSG] = "";
        sym_info* sym = NULL;
        
        P_RULE(108,"<identificador> ::= TOK_IDENTIFICADOR");
        sprintf(err_msg, "Identificador [%s] duplicado", $1.lexema);
        CHECK_ERROR(sym_t_check($1.lexema) == NULL, err_msg);
        
        sym = sym_info_create($1.lexema, VARIABLE, tipo_actual, clase_actual, tamanio_vector_actual, pos_variable_local_actual);
        CHECK_ERROR(sym, "Sin memoria");
        
        sym_t_add_symb(sym);
        if(sym->is_var_loc){
            pos_variable_local_actual++;
            sym->pos_var_loc = pos_variable_local_actual;
            num_variables_locales_actual++;
        }
        tamanio_vector_actual = 0;
    };

%%