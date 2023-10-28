import aiarena
from aiarena.connect4 import cell


def color_score(gameState, color):

    cells = gameState.cells
    width = gameState.width
    height = gameState.height

    lines = {"2": 0, "3": 0, "4": 0}

    for i in range(height):
        for j in range(width):

            # Horizontales
            if cells[width * i + j].color == color:
                if (j + 1 < width) and (cells[width * i + j + 1].color == color):
                    if (j + 2 < width) and (cells[width * i + j + 2].color == color):
                        if (j + 3 < width) and (cells[width * i + j + 3].color == color):
                            lines["4"] += 1
                        else:
                            lines["3"] += 1
                    else:
                        lines["2"] += 1

            # Diagonales droites
            if cells[width * i + j].color == color:
                if ((i + 1 < height) and (j + 1 < width)) and (cells[width * (i + 1) + j + 1].color == color):
                    if ((i + 2 < height) and (j + 2 < width)) and (cells[width * (i + 2) + j + 2].color == color):
                        if ((i + 3 < height) and (j + 3 < width)) and (cells[width * (i + 3) + j + 3].color == color):
                            lines["4"] += 1
                        else:
                            lines["3"] += 1
                    else:
                        lines["2"] += 1

            # Diagonales gauches
            if cells[width * i + j].color == color:
                if ((i + 1 < height) and (j - 1 >= 0)) and (cells[width * (i + 1) + j - 1].color == color):
                    if ((i + 2 < height) and (j - 2 >= 0)) and (cells[width * (i + 2) + j - 2].color == color):
                        if ((i + 3 < height) and (j - 3 >= 0)) and (cells[width * (i + 3) + j - 3].color == color):
                            lines["4"] += 1
                        else:
                            lines["3"] += 1
                    else:
                        lines["2"] += 1

    # Verticales
    for j in range(width):
        for i in range(height):

            if cells[width * i + j].color == color:
                if (i + 1 < height) and (cells[width * (i + 1) + j].color == color):
                    if (i + 2 < height) and (cells[width * (i + 2) + j].color == color):
                        if (i + 3 < height) and (cells[width * (i + 3) + j].color == color):
                            lines["4"] += 1
                        else:
                            lines["3"] += 1
                    else:
                        lines["2"] += 1

    # if (color == aiarena.connect4.cell.WHITE) ^ (gameState.isWhiteTurn == False):
    score_color = lines["2"] + 10 * lines["3"] + 100 * lines["4"]
    # else:
    #    score_color = lines["2"]  +  100 * lines["3"]  +  100 * lines["4"]

    return(score_color)


def evaluate(gameState):

    # White scores positive, black scores negative
    score_w = color_score(gameState, aiarena.connect4.cell.WHITE)
    score_b = color_score(gameState, aiarena.connect4.cell.BLACK)

    return(score_w - score_b)
