import aiarena
from aiarena.checkers import cell


def evaluate_color(gameState, white):
    score = 0
    taille = gameState.nRows
    for i in range(taille):  # position verticale
        for j in range(taille):  # position horizontale
            if (i + j) % 2 == 1:  # case valide
                cell = gameState.getCell(i, j)
                if cell.type != aiarena.checkers.cell.NONE and not (cell.isWhite ^ white):
                    if cell.type == aiarena.checkers.cell.MAN:  # pion
                        score += 5
                    if cell.type == aiarena.checkers.cell.KING:  # dame
                        score += 8
                    if i == taille - 1 and cell.isWhite:  # arrière blanc
                        score += 4
                    if i == 0 and not cell.isWhite:  # arrière noir
                        score += 4
                    if abs(i + 1 / 2 - taille / 2) <= taille / 8 and abs(j + 1 / 2 - taille / 2) <= taille / 4:  # centre
                        score += 3
    return(score)


def evaluate(gameState):
    return(evaluate_color(gameState, True) - evaluate_color(gameState, False))
