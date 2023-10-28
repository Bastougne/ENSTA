import aiarena
from .minimax.limited_depth import minimax
from .evaluation_functions import connect4, checkers


evaluations_functions = {
    aiarena.checkers: checkers.evaluate,
    aiarena.connect4: connect4.evaluate
}


class MinimaxBrain:

    def __init__(self, gameclass, gameclass_arguments={}):
        self.depth = 5  # Set the exploration depth here
        self.get_children = gameclass.GameState.findNextStates
        self.evaluate = evaluations_functions[gameclass]

    def play(self, gameState, timeLimit):
        gs_copy = gameState.copy()
        moves = gs_copy.findPossibleMoves()
        move_score = -10000
        move_i = 0
        for i in range(len(moves)):
            move = moves[i]
            temp_score = minimax(gs_copy.doMove(move), True, self.get_children, self.evaluate, self.depth)
            if temp_score > move_score:
                move_i = i
                move_score = temp_score
        return(moves[move_i])

    def __str__(self):
        return "MiniMax_Player"
