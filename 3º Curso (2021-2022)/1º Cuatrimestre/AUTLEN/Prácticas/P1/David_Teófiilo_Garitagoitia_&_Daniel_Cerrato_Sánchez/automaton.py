"""Automaton implementation."""
from typing import Collection, Set, List

from automata.interfaces import (
    AbstractFiniteAutomaton,
    AbstractState,
    AbstractTransition,
)

class State(AbstractState):
    """State of an automaton."""

    # You can add new attributes and methods that you think that make your
    # task easier, but you cannot change the constructor interface.


class Transition(AbstractTransition[State]):
    """Transition of an automaton."""

    # You can add new attributes and methods that you think that make your
    # task easier, but you cannot change the constructor interface.


class FiniteAutomaton(
    AbstractFiniteAutomaton[State, Transition],
):
    """Automaton."""

    def __init__(
        self,
        *,
        initial_state: State,
        states: Collection[State],
        symbols: Collection[str],
        transitions: Collection[Transition],
    ) -> None:
        super().__init__(
            initial_state=initial_state,
            states=states,
            symbols=symbols,
            transitions=transitions,
        )

        # Add here additional initialization code.
        # Do not change the constructor interface.

    def to_deterministic(
        self,
    ) -> "FiniteAutomaton":
        from automata.automaton_evaluator import FiniteAutomatonEvaluator

        set_sets: List[Set[State]] = []    #Lista de conjuntos de estados
        transitions: List[List[int]] = [] #Tabla de tranisiciones (en las pos 00 se indica el nº del estado al que transita el estado 0 con el simbolo 0)
        set_states: Set[State] = set() #estados contenidos en el estado a evaluar
        indice = 0 #indica la posicion en la tabla del último estado evaluado
        aut = FiniteAutomatonEvaluator(self) #Evaluator para uso de sus funciones

        set_states.add(self.initial_state) #le añadimos el estado inicial
        aut._complete_lambdas(set_states) #completamos con los lambdas
        set_sets.append((set_states)) #añadimos el set de estados a los set que teniamos

        while(indice!= len(set_sets)):
            transitionsState = []
            for symbol in aut.automaton.symbols: #por cada simbolo rellenamos la tabla de transiciones
                aut.current_states = set_sets[indice] #los estados iniciales los inicializamos a los estados que queremos evaluar
                aut.process_symbol(symbol) #procesamos el simbolo. en current states están lo nuevos estados tras procesar el símbolo
                if len(aut.current_states) == 0:
                    transitionsState.append(-1)
                else:
                    try:
                        index_of_set = set_sets.index((aut.current_states)) #cogemos la posición de la tabla donde se encuentra el current states
                    except ValueError:
                        index_of_set = -1
                    #a la lista de transiciones de la posición indice se la añade el indice de la tabla de transiciones a la que pasa al recibir el simbolo
                    if index_of_set == -1: #en caso de que no estuviera
                        set_sets.append((aut.current_states)) #se añade el nuevo estado
                        transitionsState.append(len(set_sets)-1) #por tanto la transición va a la última posición de la tabla
                    else:
                        transitionsState.append(index_of_set) #en cambio si estaba ya ese estado, la transición va a al estado
            transitions.append(transitionsState)    
            indice+=1 #aumentamos el indice para analizar el siguiente estado
        
        initial_state: State
        states: Set[State] = set()
        symbols: Set[str] = set()
        trans: Set[Transition] = set()

        dict_states = {} #diccionario de estados para que sea más rápido su acceso

        initial_state = State(name="0", is_final=False) #creamos el estado inicial (que corresponde al estado de la pos 0 de set_sets)
        
        for state in set_sets[0]: #comprobamos si este estado inicial es final
            if state.is_final:
                initial_state.is_final = True
                break
        
        states.add(initial_state)
        dict_states.update({0:initial_state})
        trashState = State(name="Trash", is_final=False)
        dict_states.update({-1:trashState})
        for i in range(1, len(set_sets)):
            newState = State(name=str(i), is_final=False)
            for state in set_sets[i]:
                if state.is_final == True:
                    newState.is_final = True
                    break
            states.add(newState)
            dict_states.update({i:newState})

        for i in range(len(set_sets)):
            for PoSymbol in range(len(aut.automaton.symbols)):
                    trans.add(Transition(dict_states[i], aut.automaton.symbols[PoSymbol], dict_states[transitions[i][PoSymbol]]))
                    if(dict_states[transitions[i][PoSymbol]] == trashState): #si esa transición va al trash
                        states.add(trashState) #entonces si añadimos el trash

        if(trashState in states): #si se añadió el trashSate añadimos las transiciones del trash state
            for PoSymbol in range(len(aut.automaton.symbols)):
                trans.add(Transition(trashState, aut.automaton.symbols[PoSymbol], trashState))

        return FiniteAutomaton(
            initial_state=initial_state,
            states=states,
            symbols=self.symbols,
            transitions=trans,
            )                


        
    def to_minimized(
        self,
    ) -> "FiniteAutomaton":
        from automata.automaton_evaluator import FiniteAutomatonEvaluator

        visited_states: List[State] = [] # Lista de estados visitados
        visited_states.append(self.initial_state)
        #creamos un automaton evaluator apartir del automaton para trabajar sobre el sin alterar el propio automata
        aut = FiniteAutomatonEvaluator(FiniteAutomaton(
            initial_state=self.initial_state,
            states=self.states,
            symbols=self.symbols,
            transitions=self.transitions,
        ))

        i=0
        #quitamos los estados a los que no somos capaces de acceder desde estados iniciales
        while i < len(visited_states):
            current: Set[State] = set()
            current.add(visited_states[i])
            for symbol in aut.automaton.symbols:
                aut.current_states = current
                aut.process_symbol(symbol)
                visited = aut.current_states.pop()
                if visited not in visited_states:
                    visited_states.append(visited)
            i+=1

        aut.automaton.states = visited_states #le ponemos al estado como estados los que hemos podido alcanzar
        newTransitions = [] #creas una lista con las nuevas transiciones inicializada a 0
        for transition in aut.automaton.transitions:
            if transition.initial_state in aut.automaton.states: #añades a las transiciones todas las originales que vengan de un estado accesible
                newTransitions.append(transition)
        aut.automaton.transitions = tuple(newTransitions) #actualizas las transiciones a las nuevas

        matrix: List[List[bool]] = []
        #inicializamos la matriz de estados poniendo a true los estados finales
        for i in range(len(aut.automaton.states)):
            auxiliarList: List[bool] = []
            for j in range(i+1):
                if(aut.automaton.states[i].is_final or aut.automaton.states[j].is_final): #si se trata de una fila o columna de un estado inicial se pone a true
                    if(i!=j and not (aut.automaton.states[i].is_final and aut.automaton.states[j].is_final)):
                        auxiliarList.append(True)
                    else:
                        auxiliarList.append(False)
                else:
                    auxiliarList.append(False)
            matrix.append(auxiliarList)
        
        changes = True
        while changes==True: #mientrás aún existan cambios
            #recorremos la matriz buscando huecos para ver si tacharlos
            changes=False
            for i in range(len(aut.automaton.states)):
                for j in range(i):
                    if(matrix[i][j]==False): #si no está marcada, vemos si la podemos marcar
                        for symbol in aut.automaton.symbols: #para cada uno de los símbolos vemos las parejas de estados
                            trans_a :State
                            trans_b :State
                            t_a = False
                            t_b = False
                            for transition in aut.automaton.transitions:
                                if t_a != False and t_b != False: #si ya hemos encontrado las 2 trans pasamos
                                    break
                                if transition.initial_state == aut.automaton.states[i] and transition.symbol == symbol:
                                    trans_a = transition.final_state
                                    t_a = True
                                
                                if transition.initial_state == aut.automaton.states[j] and transition.symbol == symbol:
                                    trans_b = transition.final_state
                                    t_b = True

                            #cogemos la transición para ese simbolo
                            index_1 = aut.automaton.states.index(trans_a)
                            index_2 = aut.automaton.states.index(trans_b)
                            if(index_1>index_2):
                                if(matrix[index_1][index_2]==True):
                                    matrix[i][j]=True
                                    changes=True
                                    break #si encuentras que para uno de los símbolos va a una marcada, marcamos y dejamos de mirar símbolos
                            else:
                                if(matrix[index_2][index_1]==True):
                                    matrix[i][j]=True
                                    changes=True
                                    break #si encuentras que para uno de los símbolos va a una marcada, marcamos y dejamos de mirar símbolos

        set_sets: List[List[State]] = []    #Lista de conjuntos de estados
        trans: Set[Transition] = set() #para crear el autómata a retornar
        states: List[State] = [] #para crear el autómata a retornar
        #interpretamos la matriz
        for i in range(len(aut.automaton.states)):
            final = False
            auxiliarSates: List[State] = []
            for j in range(i,len(aut.automaton.states)): 
                if(matrix[j][i]==False): #si no estaba marcada
                    matrix[j][i]=True #la marcamos
                    matrix[j][j]=True #ponemos a true para que no la use en ningún otro momento
                    auxiliarSates.append(aut.automaton.states[j]) #añadimos el estado
                    if(aut.automaton.states[j].is_final==True): #si tiene algún estado que fuese final, el nuevo estado también lo es
                        final=True
            if(len(auxiliarSates)>0): #si el nuevo conjunto a añadir no es vacio
                set_sets.append(auxiliarSates) #añadimos el nuevo estado a la lista de estados
                states.append(State(name=str(i), is_final=final)) #añadimos el nuevo estado

        #creamos las transiciones
        for i in range(len(set_sets)):
            for symbol in aut.automaton.symbols:
                for transition in aut.automaton.transitions:
                    if transition.initial_state == set_sets[i][0] and transition.symbol == symbol: #si la transicion le corresponde al estado evaluado
                        trans_a = transition.final_state #se coge el estado final
                        for j in range(len(set_sets)): #se comprueba a que estado corresponde ese "subestado" final
                            if(trans_a in set_sets[j]):
                                trans.add(Transition(states[i], symbol, states[j])) #se añade la transición entre estados
                                break
                        break

        #ponemos el estado inicial del automata original al pasarlo al reducido
        for i in range(len(set_sets)):
            if aut.automaton.initial_state in set_sets[i]:
                initial_state = states[i]
                break
        return FiniteAutomaton(
            initial_state=initial_state,
            states=set(states),
            symbols=aut.automaton.symbols,
            transitions=trans,
        )    


