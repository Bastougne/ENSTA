from time import time


def minimax_ab_id_init(node, maximize, a, b, get_children, evaluate, timeOneMove):
    depth = 0
    timeStop = timeOneMove + time()
    while True:
        depth += 1
        known_states = {}
        temp = minimax_ab_id(node, maximize, a, b, get_children, evaluate, depth, known_states, timeStop)
        if temp != -10000:
            score = temp
        if time() > timeStop:
            return(score)


def minimax_ab_id(node, maximize, a, b, get_children, evaluate, max_depth, known_states, timeStop):
    if time() > timeStop:
        return(-10000)
    if max_depth == 0 or get_children(node) == []:
        return(evaluate(node))
    if str(node) in known_states:
        return(known_states[str(node)])
    if maximize:
        score = -10000
        children = get_children(node)
        for child in children:
            temp = minimax_ab_id(child, False, a, b, get_children, evaluate, max_depth - 1, known_states, timeStop)
            known_states[str(child)] = temp
            score = max(score, temp)
            a = max(a, score)
            if a > b:
                break
        return(score)
    else:
        score = 10000
        children = get_children(node)
        for child in children:
            temp = minimax_ab_id(child, True, a, b, get_children, evaluate, max_depth - 1, known_states, timeStop)
            known_states[str(child)] = temp
            score = min(score, temp)
            b = min(b, score)
            if a > b:
                break
        return(score)
