%{
    #include "alfa.h"
    #include "y.tab.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    /* Imprime token en un fichero de debug */
    #define SHIFT() fprintf(alfa_utils_T.fdbg, ";D:\t%s\n", yytext)

    /* Antes de cada regla, avanzamos el contador de columna */
    #define YY_USER_ACTION { alfa_utils_T.col += yyleng; }
%}

/* SECCION DE DEFINICIONES */
%option noyywrap 
DIGITO [0-9]
LETRA [a-zA-Z]  
%%
    /* SECCION DE REGLAS */
    /* Define la creacion de tokens */

("//".*)    {  }    /* Comentarios */
[ ]         {  }    /* Espacio */
[\t]        {  }    /* Tabulador */
[\n]        { alfa_utils_T.line++; alfa_utils_T.col = 1; }    /* Saltos de linea */

    /* Palabras reservadas */ 
main        { SHIFT(); return TOK_MAIN; }
int         { SHIFT(); return TOK_INT; }
boolean     { SHIFT(); return TOK_BOOLEAN; }
array       { SHIFT(); return TOK_ARRAY; }
function    { SHIFT(); return TOK_FUNCTION; }
if          { SHIFT(); return TOK_IF; }
else        { SHIFT(); return TOK_ELSE; }
while       { SHIFT(); return TOK_WHILE; }
scanf       { SHIFT(); return TOK_SCANF; }
printf      { SHIFT(); return TOK_PRINTF; }
return      { SHIFT(); return TOK_RETURN; }

    /* Simbolos */ 
;       { SHIFT(); return yytext[0]; }
,       { SHIFT(); return yytext[0]; }
"("     { SHIFT(); return yytext[0]; }
")"     { SHIFT(); return yytext[0]; }
"["     { SHIFT(); return yytext[0]; }
"]"     { SHIFT(); return yytext[0]; }
"{"     { SHIFT(); return yytext[0]; } 
"}"     { SHIFT(); return yytext[0]; }
"="     { SHIFT(); return yytext[0]; }
"+"     { SHIFT(); return yytext[0]; }
"-"     { SHIFT(); return yytext[0]; }
"/"     { SHIFT(); return yytext[0]; }
"*"     { SHIFT(); return yytext[0]; }
"&&"    { SHIFT(); return TOK_AND; }
"||"    { SHIFT(); return TOK_OR; }
"!"     { SHIFT(); return yytext[0]; }
"=="    { SHIFT(); return TOK_IGUAL; }
"!="    { SHIFT(); return TOK_DISTINTO; }
"<="    { SHIFT(); return TOK_MENORIGUAL; }
">="    { SHIFT(); return TOK_MAYORIGUAL; }
"<"     { SHIFT(); return yytext[0]; }
">"     { SHIFT(); return yytext[0]; }

    /* Constantes */
true        { SHIFT(); return TOK_TRUE; }
false       { SHIFT(); return TOK_FALSE; }
{DIGITO}+   { 
                #include "alfa.h"
                SHIFT(); yylval.atributos.valor_entero = atoi(yytext); 
                return TOK_CONSTANTE_ENTERA; 
            }   

    /* Identificadores */
{LETRA}({DIGITO}|{LETRA})*  {
                                SHIFT();
                                /* Error de longitud */
                                if (yyleng > MAX_LONG_ID) {
                                    alfa_utils_T.col -= yyleng;
                                    alfa_utils_T.error = ERR_MORFOLOGICO;
                                    manage_error("identificador con longitud superior a 100", NULL);
                                    return TOK_ERROR;
                                }
                                strcpy(yylval.atributos.lexema, yytext);
                                return TOK_IDENTIFICADOR; 
                            }

    /* Error de simbolos no permitidos */
.         { alfa_utils_T.col -= 1; alfa_utils_T.error = ERR_MORFOLOGICO; manage_error("simbolo no permitido", yytext); return TOK_ERROR; }

%%
