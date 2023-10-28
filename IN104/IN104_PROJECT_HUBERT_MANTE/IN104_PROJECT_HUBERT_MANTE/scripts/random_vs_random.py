import aiarena
from ..randomBrain import RandomBrain


for module in [aiarena.chess, aiarena.checkers, aiarena.connect4]:
    brain1 = RandomBrain()
    timeLimit = 1
    brain2 = RandomBrain()
    game = aiarena.Game(module, brain1, timeLimit, brain2, timeLimit)
    game.displayLevel = 1
    game.start()
    print(game.pgn)
    input('press enter to continue')
