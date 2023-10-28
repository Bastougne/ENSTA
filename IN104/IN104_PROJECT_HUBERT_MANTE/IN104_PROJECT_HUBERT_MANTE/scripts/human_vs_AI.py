import aiarena
from ..randomBrain import RandomBrain
from ..minimaxIterDeepBrain import MinimaxIterDeepBrain


brain1 = MinimaxIterDeepBrain(aiarena.checkers)
human_time = 0.5
brain2 = MinimaxIterDeepBrain(aiarena.checkers)
ai_time = 0.5
game = aiarena.Game(aiarena.checkers, brain1, human_time, brain2, ai_time)
game.displayLevel = 1
game.start()
print(game.pgn)
