#given a prob matrix from a directed graph, returns the simplified fractions of the absorving markov chain for each final state

import fractions

def solution(m):
    n = len(m)
    s = [0 for i in range(n)]
    
    nr = 0
    nt = 0
    
    for i in range(n):
        for j in range(n):
            s[i] += m[i][j]
        if s[i] != 0:
            nt += 1
    nr = n - nt

    sum = [0 for i in range(nt)]
    Q = [[0 for j in range(nt)] for i in range(nt)]
    D = [[0 for j in range(nt)] for i in range(nt)]
    R = [[0 for j in range(nr)] for i in range(nt)]
    
    x = 0
    for i in range(n):
        if s[i] == 0:
            continue
        y, y2 = 0, 0
        sum[x] = s[i]
        for j in range(n):
            if s[j] != 0:
                Q[x][y] = m[i][j]
                y += 1
            else:
                R[x][y2] = m[i][j]
                y2 += 1
        x += 1
        
    if s[0] == 0:
        r = [0 for i in range(nr + 1)]
        r[0] = r[nr] = 1
        return r
        
    for i in range(nt):
        for j in range(nt):
            if i == j:
                Q[i][j] = sum[i] - Q[i][j]
            else:
                Q[i][j] *= -1
            D[i][j] = sum[i]
    
    IN = [[1 if i == j else 0 for j in range(nt)] for i in range(nt)]
    ID = [[1 for j in range(nt)] for i in range(nt)]

    for i in range(nt):
        num, den = Q[i][i], D[i][i]
        for j in range(nt):
            Q[i][j] *= den
            D[i][j] *= num
            IN[i][j] *= den
            ID[i][j] *= num
        for j in range(nt):
            if i == j:
                continue
            fn = Q[j][i]
            fd = D[j][i]
            for k in range(nt):
                Q[j][k] = Q[j][k] * fd * D[i][k] - fn * Q[i][k] * D[j][k]
                D[j][k] *= fd * D[i][k]
                IN[j][k] = IN[j][k] * fd * ID[i][k] - fn * IN[i][k] * ID[j][k]
                ID[j][k] *= fd * ID[i][k]

    for i in range(nt):
        for j in range(nt):
            g = fractions.gcd(Q[i][j], D[i][j])
            if g != 0:
                Q[i][j] /= g
                D[i][j] /= g
            g = fractions.gcd(IN[i][j], ID[i][j])
            if g != 0:
                IN[i][j] /= g
                ID[i][j] /= g

    SN = [0 for i in range(nr)]
    SD = [1 for i in range(nr)]

    lcm = 1

    for j in range(nr):
        for k in range(nt):
            SN[j] = SN[j] * ID[0][k] * sum[k] + SD[j] * IN[0][k] * R[k][j]
            SD[j] = SD[j] * ID[0][k] * sum[k]
            g = fractions.gcd(SN[j], SD[j])
            SN[j] /= g
            SD[j] /= g
        lcm = lcm / fractions.gcd(lcm, SD[j]) * SD[j]
    
    r = [0 for i in range(nr + 1)]
    
    r[nr] = lcm
    
    for i in range(nr):
        r[i] = lcm / SD[i] * SN[i]    
    
    return r
