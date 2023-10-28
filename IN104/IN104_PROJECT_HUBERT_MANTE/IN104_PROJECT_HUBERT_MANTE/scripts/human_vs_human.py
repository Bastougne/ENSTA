import aiarena


brain1 = aiarena.ManualBrain()
brain2 = aiarena.ManualBrain()
timeLimit = 10
game = aiarena.Game(aiarena.connect4, brain1, timeLimit, brain2, timeLimit)
game.start()
print(game.pgn)
