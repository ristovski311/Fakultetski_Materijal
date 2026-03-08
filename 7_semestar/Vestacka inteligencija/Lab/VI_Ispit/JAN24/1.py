from functools import reduce

def napravi(lista):
    #od liste tuple kreira dictionary
    
    recnik = { t[0] : None if len(t) < 2 else reduce(lambda a,b:a*b, t[1:]) for t in lista }
    
    return recnik

print(napravi([(1,2,3),(3,4,2),(9,),(6,7,8,9),(1,1,1)]))