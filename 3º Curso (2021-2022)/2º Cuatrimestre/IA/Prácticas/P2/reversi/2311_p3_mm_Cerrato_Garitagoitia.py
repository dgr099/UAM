import time
from game import (
    TwoPlayerGameState,
)
from tournament import (
    StudentHeuristic,
)
"""
Coin Difference
Apparently, for a player, the more coins he has (and the fewer coins his opponent has), the better.

start

But note that the weight assigned to this heuristic should not be heavy, because the difference in coins fluctuates intensely and frequently, due to the nature of the game, and only in the very end does the difference in coins matters.

Choice Difference
This heuristic aims to increase one's flexibility in terms of choices and constrain the opponent's choices of valid moves.

start

Corner Difference
From the experience of playing the game, we learned that corners are crucial because once a corner is captured, it cannot be flipped. Furthermore, a player can build up stable coins around the corner. This is how one usually wins. Thus, this heuristic should receive a heavy weighting.
https://github.com/JRChow/Reversi
https://www.diva-portal.org/smash/get/diva2:1121059/FULLTEXT01.pdf

"""

class Solution1(StudentHeuristic):
    def get_name(self) -> str:
        return "VivaCristoRey"

    def evaluation_function(self, state: TwoPlayerGameState) -> float:
      values = [[100, 2,  5,    3,    3,   5,   2, 100],
                [2,   -60, -1,   -1,   -1,  -1, -60,  2],
                [5,   -1,   1,  -10,  -10,   1,  -1,  5],
                [3,   -1, -10,  -10,  -10, -10,  -1,  3],
                [3,   -1, -10,  -10,  -10, -10,  -1,  3],
                [5,   -1,   1,  -10,  -10,   1,  -1,  5],
                [2,   -60, -1,   -1,   -1,  -1,  -60, 2],
                [100,  2,  5,    3,    3,   5,    2, 100]]
      value2=0
      value1=0
      fm1=0
      fm2=0
      c1=0
      c2=0
      cc1=0
      cc2=0
      diri = [0, 0, 1, -1, 1, -1, 1, -1]
      dirj = [1, -1, 1, 1, 0, 0, -1, -1]
      esqi = [0, 7, 0, 7] #esq inf d, inf i, sup d, sup i
      esqj = [0, 0, 7, 7]
      for i in range(8):
        for j in range(8):
          pos = state.board.get((i+1, j+1), '_',) #cojo lo que hay en esa casilla
          if(pos == state.player1.label):
            value1 = value1 + values[i][j] #si está el jugador 1 le sumas el valor de esa pos para el player 1
          elif (pos == state.player2.label):
            value2 = value2 + values[i][j] #si está el jugador 2 le sumas el valor de esa pos para el player 2
          
          else: #posición vacía (comprobar discos frontera) arriba, abajo, d a der, d a izq, der, izq, d ab der, d ab izq
            for aux in range(8): #comprobamos las 8 esquinas
                pos = state.board.get((i+1 + diri[aux], j+1 + dirj[aux]), '_',) #vemos que estaba adyacente a ese espacio vacio
                if(pos == state.player1.label):
                  fm1+=1 #si es de jugador 1, el jugador 1 tiene una ficha frontera más
                elif (pos == state.player2.label):
                  fm2+=1 #si es de jugador 2, el jugador 2 tiene una ficha frontera más
            continue

          if(i in esqi and j in esqj): #si estamos en una esquina
            if(pos == state.player1.label): #si en esa esquina esta el jugador 1
              c1 = c1+1 #sumamos 1 a las esquinas de jugador 1
            elif (pos == state.player2.label): #si en esa esquina esta el jugador 2
              c2 = c2+1 #sumamos 1 a las esquinas de jugador 2
            #si no hay nadie en esa esquina aprovechamos para coger los corners closeness
            else:
              for aux in range(8): #comprobamos las 8 esquinas
                pos = state.board.get((i+1 + diri[aux], j+1 + dirj[aux]), '_',) #cogemos el adyacente a esa esquina (corners closeness)
                if(pos == state.player1.label):
                  cc1 = cc1+1
                elif (pos == state.player2.label):
                  cc2 = cc2+1
      n1=state.scores[0]
      n2=state.scores[1]
      d=value1-value2
      mov1 = len(state.game._get_valid_moves(state.board,state.player1.label))
      mov2 = len(state.game._get_valid_moves(state.board,state.player2.label))
      if(state.is_player_max(state.player1)==False): #rotamos las pos de las variables
        cc1, cc2 = cc2, cc1
        c1, c2 = c2, c1
        value1, value2 = value2, value1
        fm1, fm2 = fm2, fm1
        n1, n2 = n2, n1
        mov1, mov2 = mov2, mov1
        d = -1 * d

      if(n1 > n2):
        p = (100.0 * n1)/(n1 + n2)
      elif(n1 < n2):
        p = -(100.0 * n2)/(n1 + n2)
      else:
        p=0
      
      if(fm1 > fm2):
        f = -(100.0 * fm1)/(fm1 + fm2)
      elif(fm1 < fm2):
        f = (100.0 * fm2)/(fm1 + fm2)
      else: 
        f = 0

      c = 25 * (c1 - c2)

      l = -12.5 * (cc1 - cc2)

      if(mov1 > mov2):
        m = (100.0 * mov1)/(mov1 + mov2)
      elif(mov1 < mov2):
        m = -(100.0 * mov2)/(mov1 + mov2)
      else:
        m = 0

      return (10 * p) + (801.724 * c) + (382.026 * l) + (78.922 * m) + (74.396 * f) + (10 * d)


class Solution2(StudentHeuristic):
  def get_name(self) -> str:
    return "1pa1SinCamiseta"
  def evaluation_function(self, state: TwoPlayerGameState) -> float:
    esqj = [0, 0, 7, 7]
    esqi = [0, 7, 0, 7] #esq inf d, inf i, sup d, sup i
    c1=0
    c2=0
    #comprobamos si el juego ya ha terminado
    if state.end_of_game:
            if state.is_player_max(state.player1):
                return 1000
            return -1000
          
    for i in esqi:
      for j in esqj:
          pos = state.board.get((i+1, j+1), '_',)
          if(pos == state.player1.label): #si en esa esquina esta el jugador 1
            c1 = c1+1 #sumamos 1 a las esquinas de jugador 1
          elif (pos == state.player2.label): #si en esa esquina esta el jugador 2
            c2 = c2+1 #sumamos 1 a las esquinas de jugador 2
          #si no hay nadie en esa esquina aprovechamos para coger los corners closeness
    mov1 = len(state.game._get_valid_moves(state.board,state.player1.label))
    mov2 = len(state.game._get_valid_moves(state.board,state.player2.label))
    p1 = state.scores[0]
    p2 = state.scores[1]
    if state.is_player_max(state.player1)==False:
      c1, c2 = c2, c1
      mov1, mov2 = mov2, mov1
      p1, p2 = p2, p1
    result=0
    if(c1+c2!=0):
      result=result + (70/100) * ((c1-c2)/(c1+c2)*100)
    if(mov1+mov2!=0):
      result=result + (15/100) *((mov1-mov2)/(mov1+mov2)*100)
    if(p1+p2!=0):
      result+=result + (15/100) *((p1-p2)/(p1+p2)*100) 

    return result 




#https://github.com/kartikkukreja/blog-codes/blob/master/src/Heuristic%20Function%20for%20Reversi%20(Othello).cpp
#https://kartikkukreja.wordpress.com/2013/03/30/heuristic-function-for-reversiothello/
#https://documentation.help/Reversi-Rules/strategy.htm
"""
importante tener en cuenta:
->discos estables: son los de las esquinas
->discos c y x (dejan accesibles las esquinas)
->movilidad (limitar los movimientos del contrario)
->discos frontera Un disco de frontera es uno que está adyacente a un cuadrado vacío
"""
class Solution3(StudentHeuristic):
  def get_name(self) -> str:
    return "CathyVipi"

  def evaluation_function(self, state: TwoPlayerGameState) -> float:
      values = [[100, -2,  3,  2,  2, 3, -2, 100],
               [-2,  -10, -1, -1, -1, -1, -10,  -2],
               [3,   -1,  2,  1,  1,  2, -1,   3],
               [2,   -1,  1,  1,  1,  1, -1,   2],
               [2,   -1,  1,  1,  1,  1, -1,   2],
               [3,   -1,  2,  1,  1,  2, -1,   3],
               [-2,  -10, -1, -1, -1, -1, -10,  -2],
               [100, -2,  3,  2,  2,  3, -2, 100]]
      value2=0
      value1=0
      fm1=0
      fm2=0
      c1=0
      c2=0
      cc1=0
      cc2=0
      diri = [0, 0, 1, -1, 1, -1, 1, -1]
      dirj = [1, -1, 1, 1, 0, 0, -1, -1]
      esqi = [0, 7, 0, 7] #esq inf d, inf i, sup d, sup i
      esqj = [0, 0, 7, 7]
      for i in range(8):
        for j in range(8):
          pos = state.board.get((i+1, j+1), '_',) #cojo lo que hay en esa casilla
          if(pos == state.player1.label):
            value1 = value1 + values[i][j] #si está el jugador 1 le sumas el valor de esa pos para el player 1
          elif (pos == state.player2.label):
            value2 = value2 + values[i][j] #si está el jugador 2 le sumas el valor de esa pos para el player 2
          
          else: #posición vacía (comprobar discos frontera) arriba, abajo, d a der, d a izq, der, izq, d ab der, d ab izq
            for aux in range(8): #comprobamos las 8 esquinas
                pos = state.board.get((i+1 + diri[aux], j+1 + dirj[aux]), '_',) #vemos que estaba adyacente a ese espacio vacio
                if(pos == state.player1.label):
                  fm1+=1 #si es de jugador 1, el jugador 1 tiene una ficha frontera más
                elif (pos == state.player2.label):
                  fm2+=1 #si es de jugador 2, el jugador 2 tiene una ficha frontera más
            continue

          if(i in esqi and j in esqj): #si estamos en una esquina
            if(pos == state.player1.label): #si en esa esquina esta el jugador 1
              c1 = c1+1 #sumamos 1 a las esquinas de jugador 1
            elif (pos == state.player2.label): #si en esa esquina esta el jugador 2
              c2 = c2+1 #sumamos 1 a las esquinas de jugador 2
            #si no hay nadie en esa esquina aprovechamos para coger los corners closeness
            else:
              for aux in range(8): #comprobamos las 8 esquinas
                pos = state.board.get((i+1 + diri[aux], j+1 + dirj[aux]), '_',) #cogemos el adyacente a esa esquina (corners closeness)
                if(pos == state.player1.label):
                  cc1 = cc1+1
                elif (pos == state.player2.label):
                  cc2 = cc2+1
      n1=state.scores[0]
      n2=state.scores[1]
      d=value1-value2
      mov1 = len(state.game._get_valid_moves(state.board,state.player1.label))
      mov2 = len(state.game._get_valid_moves(state.board,state.player2.label))
      if(state.is_player_max(state.player1)==False): #rotamos las pos de las variables
        cc1, cc2 = cc2, cc1
        c1, c2 = c2, c1
        value1, value2 = value2, value1
        fm1, fm2 = fm2, fm1
        n1, n2 = n2, n1
        mov1, mov2 = mov2, mov1
        d = -1 * d

      if(n1 > n2):
        p = (100.0 * n1)/(n1 + n2)
      elif(n1 < n2):
        p = -(100.0 * n2)/(n1 + n2)
      else:
        p=0
      
      if(fm1 > fm2):
        f = -(100.0 * fm1)/(fm1 + fm2)
      elif(fm1 < fm2):
        f = (100.0 * fm2)/(fm1 + fm2)
      else: 
        f = 0

      c = 25 * (c1 - c2)

      l = -12.5 * (cc1 - cc2)

      if(mov1 > mov2):
        m = (100.0 * mov1)/(mov1 + mov2)
      elif(mov1 < mov2):
        m = -(100.0 * mov2)/(mov1 + mov2)
      else:
        m = 0

      return (10 * p) + (801.724 * c) + (382.026 * l) + (78.922 * m) + (74.396 * f) + (10 * d)
  """def evaluation_function(self, state: TwoPlayerGameState) -> float:
    esqi = [0, 7, 0, 7] #esq inf d, inf i, sup d, sup i
    esqj = [0, 0, 7, 7]
    c2=0
    c1=0
    values = [[100, -2,  3,  2,  2, 3, -2, 100],
               [-2,  -10, -1, -1, -1, -1, -10,  -2],
               [3,   -1,  2,  1,  1,  2, -1,   3],
               [2,   -1,  1,  1,  1,  1, -1,   2],
               [2,   -1,  1,  1,  1,  1, -1,   2],
               [3,   -1,  2,  1,  1,  2, -1,   3],
               [-2,  -10, -1, -1, -1, -1, -10,  -2],
               [100, -2,  3,  2,  2,  3, -2, 100]]
    #comprobamos si el juego ya ha terminado
    if state.end_of_game:
            if state.is_player_max(state.player1):
                return 1000
            return -1000
    value1=0
    value2=0
    for i in range(8):
        for j in range(8):
          pos = state.board.get((i+1, j+1), '_',) #cojo lo que hay en esa casilla
          if(pos == state.player1.label):
            value1 = value1 + values[i][j] #si está el jugador 1 le sumas el valor de esa pos para el player 1
          elif (pos == state.player2.label):
            value2 = value2 + values[i][j] #si está el jugador 2 le sumas el valor de esa pos para el player 2

          if(i in esqi and j in esqj):
            if(pos == state.player1.label): #si en esa esquina esta el jugador 1
              c1 = c1+1 #sumamos 1 a las esquinas de jugador 1
            elif (pos == state.player2.label): #si en esa esquina esta el jugador 2
              c2 = c2+1 #sumamos 1 a las esquinas de jugador 2
            #si no hay nadie en esa esquina aprovechamos para coger los corners closeness
    mov1 = len(state.game._get_valid_moves(state.board,state.player1.label))
    mov2 = len(state.game._get_valid_moves(state.board,state.player2.label))
    p1 = state.scores[0]
    p2 = state.scores[1]
    if state.is_player_max(state.player1)==False:
      c1, c2 = c2, c1
      mov1, mov2 = mov2, mov1
      p1, p2 = p2, p1
      value1, value2 = value2, value1
    result=0
    if(c1+c2!=0):
      result=result + (70/100) * ((c1-c2)/(c1+c2)*100)
    if(mov1+mov2!=0):
      result=result + (15/100) *((mov1-mov2)/(mov1+mov2)*100)
    if(p1+p2!=0):
      result+=result + (15/100) *((p1-p2)/(p1+p2)*100) 
    if(value1 + value2!=0):
      result+=(95/100) * result + (5/100) *((value1-value2)/(value1+value2)*100) 

    return result """
    