def minimax(node, maximize, get_children, evaluate, max_depth):
    if max_depth == 0 or get_children(node) == []:
        return(evaluate(node))

    elif maximize:
        score = -10000
        children = get_children(node)
        for child in children:
            temp = minimax(child, False, get_children, evaluate, max_depth - 1)
            score = max(score, temp)
        return(score)

    else:
        score = 10000
        children = get_children(node)
        for child in children:
            temp = minimax(child, True, get_children, evaluate, max_depth - 1)
            score = min(score, temp)
        return(score)
