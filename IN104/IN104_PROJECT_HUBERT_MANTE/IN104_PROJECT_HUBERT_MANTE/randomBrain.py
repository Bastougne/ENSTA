import random


class RandomBrain:
    def __init__(self):
        pass

    def play(self, gameState, timeLimit):
        possibleMoves = gameState.findPossibleMoves()
        return random.choice(possibleMoves)

    def __str__(self):
        return "Random_Player"
