import math

cycle = math.pi * 2

def calcValues (func, sample_caunt):
    result = []
    step = cycle / sample_caunt
    for i in range (sample_caunt):
        result.append(func(i * step))

    return result

triangle = lambda x: (2 / math.pi * x - 1) if x < cycle / 2 else (3 - 2 / math.pi * x)

saw = lambda x : 1 - (1 / math.pi * x)

sq = lambda x: 1 if x < cycle / 2 else -1

def pp (l):
    for e in l:
        print(e, end=",\n")

pp(calcValues(triangle, 512))
