import aiarena
from random import random
from .minimax.limited_depth_ab_id import minimax_ab_id_init
from .evaluation_functions import connect4, checkers


evaluations_functions = {
    aiarena.checkers: checkers.evaluate,
    aiarena.connect4: connect4.evaluate
}


class MinimaxIterDeepBrain:

    def __init__(self, gameclass, gameclass_arguments={}):
        self.get_children = gameclass.GameState.findNextStates
        self.evaluate = evaluations_functions[gameclass]

    def play(self, gameState, timeLimit):
        self.evaluate(gameState)
        nb_moves = len(gameState.findPossibleMoves())
        move_score = -10000
        move_i = 0
        timeOneMove = (timeLimit - 10 * 10**-3) / nb_moves  # délai pour éviter le timeout
        k = 1
        for i in range(nb_moves):
            gs_copy = gameState.copy()  # doMove modifie gameState
            moves = gs_copy.findPossibleMoves()
            move = moves[i]  # minimax ne donne qu'un score, on récupère l'indice du meilleur coup à la main
            temp_score = minimax_ab_id_init(gs_copy.doMove(move), True, -10000, 10000, self.get_children, self.evaluate, timeOneMove)
            if temp_score > move_score:
                move_i = i
                move_score = temp_score
            elif (temp_score == move_score) and (random() < 2**-k):  # évite de bloquer le jeu indéfiniment
                move_i = i
                k += 1
        return(moves[move_i])

    def __str__(self):
        return "MiniMax_v2_Player"
