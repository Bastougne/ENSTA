def minimax_ab(node, maximize, a, b, get_children, evaluate, max_depth, known_states):
    if max_depth == 0 or get_children(node) == []:
        return(evaluate(node))

    if str(node) in known_states:
        return(known_states[str(node)])

    if maximize:
        score = -10000
        children = get_children(node)
        for child in children:
            temp = minimax_ab(child, False, a, b, get_children, evaluate, max_depth - 1, known_states)
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
            temp = minimax_ab(child, True, a, b, get_children, evaluate, max_depth - 1, known_states)
            known_states[str(child)] = temp
            score = min(score, temp)
            b = min(b, score)
            if a > b:
                break
        return(score)
