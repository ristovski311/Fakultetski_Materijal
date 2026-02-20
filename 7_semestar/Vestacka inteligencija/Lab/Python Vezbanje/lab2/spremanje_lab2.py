from itertools import *
from functools import *
from re import *

#Zadatak 1
def poredak(lista1, lista2):
    c = [(x,y, "Jeste" if y==2*x else "Nije") for (x, y) in list(zip_longest(lista1, lista2, fillvalue=0))]
    return c    
#print(poredak([2, 4, 6, 2, 1], [4, 1, 12, 5, 8, 3, 2]))

#Zadatak 2
def spojidict(lista1, lista2):
    c = [{"prvi":x, "drugi": y} for (x,y) in list(zip_longest(lista1, lista2, fillvalue="-"))]
    return c
# print(spojidict([1, 7, 2, 4], [2, 5, 2]))

#Zadatak 3
def spoji(lista1, lista2):
    c = [(min(x,y), max(x,y), x+y) for (x,y) in list(zip_longest(lista1, lista2, fillvalue=0))]
    return c
# print(spoji([1, 7, 2, 4], [2, 5, 2]))

#Zadatak 4
def suma(lista):
    # c = sum([sum(x) for x in lista])
    c = sum([x for pod in lista for x in pod])
    return c
# print(suma([[1, 2, 3], [4, 5, 6], [7, 8, 9]]))

#Zadatak 5
def proizvod(lista1, lista2):
    c = list(map(lambda x,y: [a * y for a in x], lista1, lista2))
    d = [sum(x) for x in c]
    return d
# print(proizvod([[1, 2, 3], [4, 5, 6], [7, 8, 9]], [1, 2, 3]))

#Zadatak 6
def objedini(lista1, lista2):
    c = [(min(x,y), max(x,y)) for (x,y) in list(zip_longest(lista1,lista2, fillvalue=0))]
    return c
# print(objedini([1, 7, 2, 4, 5], [2, 5, 2]))

#Zadatak 7
def objedini2(lista):
    c = {x[0]:x[1:] if len(x) > 1 else None for x in lista}
    return c
# print(objedini2([(1,), (3, 4, 5), (7,), (1, 4, 5), (6, 2, 1, 3)]))

#Zadatak 8
def izracunaj(lista):
    c = [reduce(lambda a,b:a*b, x, 1) if type(x) == type([]) else x for x in lista]
    return c
# print(izracunaj([1, 5, [1, 5, 3], [4, 2], 2, [6, 3]]))

#Zadatak 9
def zamena(lista, broj):
    c = [lista[i] if lista[i] >= broj else sum(lista[i+1:]) for i in range(len(lista))]
    return c
# print(zamena([1, 7, 5, 4, 9, 1, 2, 7], 5))

#Zadatak 10
def stepen(lista):
    c = list(pairwise(lista))
    d = list(starmap(lambda x,y: x**y, c))
    return d
# print(stepen([1, 5, 2, 6, 1, 6, 3, 2, 9]))

#Zadatak 11
def proizvod2(lista):
    c = [x for sub in lista for x in sub]
    d = reduce(lambda a,b: a*b, c, initial=1)
    return d
# print(proizvod2([[1, 3, 5], [2, 4, 6], [1, 2, 3]]))

#Zadatak 12
def izracunaj2(lista):
    c = [reduce(lambda x,y: x+y, [a*a for a in x]) if type(x) == type([]) else x*x for x in lista]
    return c
# print(izracunaj2([2, 4, [1, 2, 3], [4, 2], 2, [9, 5]]))

#Zadatak 13
def skupi(lista):
    c = list(pairwise(lista))
    d = [list(zip_longest(x,y,fillvalue=0)) for (x,y) in c]
    e = [[sum(el) for el in sublist] for sublist in d]
    return e
# print(skupi([[1, 3, 5], [2, 4, 6], [1, 2]]))

#Zadatak 14
def suma(lista):
    c = sum([reduce(lambda x,y: x*y, x, initial=1) for x in lista])
    return c
# print(suma([[1, 2, 3], [4, 5, 6], [7, 8, 9]]))

#Zadatak 15
def promeni(list, num):
    c = [x-num if x >= num else x+num for x in list]
    return c
# print(promeni([7, 1, 3, 5, 6, 2], 3))

#Zadatak 16
def broj(hexa):
    d = [hexa[1:3], hexa[3:5], hexa[5:]]
    c = sum([(int(d[i], 16) * (256**(2-i))) for i in range(len(d))])
    return c
# print(broj("#FA0EA0"))

#Zadatak 17
def tekst(text):
    b = list(chain(text))
    c = [r"\\u" + str(hex(ord(char)))[2:].zfill(4) if (ord(char) not in chain(range(65,91), range(97,122), range(48,58))) else char for char in b]
    return reduce(lambda x,y: x+y, c, initial="")
# print(tekst("Otpornost 10Ω."))

#Zadatak 18
def brojevi(string):
    c = findall(r"\d+", string)
    return c
# print(brojevi("42+10=52;10*10=100"))

#Zadatak 19
def brojanje(string):
    c = list(chain(string))
    d = list(pairwise(c))
    e = [x for x in d if x[0] == x[1]]
    return len(e)
# print(brojanje("aatesttovi"))

#Zadatak 20
def izracunaj(lista, fun):
    c = [fun(lista[i-2], lista[i-1], lista[i]) for i in range(2, len(lista))]
    return c
# print(izracunaj([2, 5, 1, 6, 7], lambda x, y, z: x + y * z))