from itertools import *
from functools import *
from re import *

#Z1
def poredak(lista1, lista2):
    return [(x,y,"Jeste" if y == 2*x else "Nije") for (x,y) in zip_longest(lista1,lista2,fillvalue=0)]
# print(poredak ([1, 7, 2, 4], [2, 5, 2, 8] ))
#Z2
def spojidict(lista1,lista2):
    return [{"prvi":x, "drugi":y} for (x,y) in zip_longest(lista1,lista2,fillvalue="-")]
# print(spojidict([1, 7, 2, 4], [2, 5, 2]))
#Z3
def spoji(lista1,lista2):
    return [(min(x,y), max(x,y), x+y) for (x,y) in zip_longest(lista1,lista2,fillvalue=0)]
# print(spoji([1, 7, 2, 4], [2, 5, 2]))
#Z4
def suma(lista):
    return sum([sum(x) for x in lista])
# print(suma([[1, 2, 3], [4, 5, 6], [7, 8, 9], [1,1,1]]))
#Z5
def proizvod(lista, faktor):
    a = [sum(x) for x in lista]
    b = list(starmap(lambda x,y: x*y, zip(a, faktor)))
    return b
# print(proizvod([[1, 2, 3], [4, 5, 6], [7, 8, 9]], [1, 2, 3]))
#Z7
def objedini(lista):
    return {
        x[0]: [y for y in x[1:]] if len(x) > 1 else None for x in lista
    }
# print(objedini([(1,), (3, 4, 5), (7,), (1, 4, 5), (6, 2, 1, 3)]))
#Z6
def objedini2(lista1,lista2):
    return [(min(a,b), max(a,b)) for (a,b) in zip_longest(lista1, lista2, fillvalue=0)]
# print(objedini2([1, 7, 2, 4, 5], [2, 5, 2]))
#Z8
def izracunaj(lista):
    return [reduce(lambda a,b: a*b, element, initial = 1) if type(element) == type([]) else element for element in lista]
# print(izracunaj([1, 5, [1, 5, 3], [4, 2], 2, [6, 3]]))
#Z9
def zamena(lista, num):
    return [sum(lista[i+1:]) if lista[i] < num else lista[i] for i in range(len(lista))]
# print(zamena([1, 7, 5, 4, 9, 1, 2, 7], 5))
#Z10
def stepen(lista):
    a = list(pairwise(lista))
    return list(starmap(lambda a,b: a**b, a))
# print(stepen([1, 5, 2, 6, 1, 6, 3, 2, 9]))
#Z11
def proizvod2(lista):
    x = [broj for sublista in lista for broj in sublista]
    return reduce(lambda a,b: a*b, x, initial = 1)
# print(proizvod2([[1, 3, 5], [2, 4, 6], [1, 2, 3]]))
#Z12
def izracunaj2(lista):
    return [sum([y*y for y in el]) if type(el) == type([]) else el*el for el in lista]
# print(izracunaj2([2, 4, [1, 2, 3], [4, 2], 2, [9, 5]]))
#Z13
def skupi(lista):
    a = list(pairwise(lista))
    b = [list(zip_longest(x,y,fillvalue=0)) for (x,y) in a]
    return [[sum(x) for x in sublist] for sublist in b]
# print(skupi([[1, 3, 5], [2, 4, 6], [1, 2]]))
#Z14
def suma2(lista):
    a = [reduce(lambda x,y: x*y, subl, initial = 1) for subl in lista]
    return sum(a)
# print(suma2([[1, 2, 3], [4, 5, 6], [7, 8, 9]]))
#Z15
def promeni(lista,x):
    return [num - x if num>=x else num+x for num in lista]
# print(promeni([7, 1, 3, 5, 6, 2], 3))
#Z16
def broj(hex):
    a = [hex[1:3], hex[3:5], hex[5:]]
    return sum([(256**(2-i)) * int(a[i],16) for i in range(3)])
# print(broj("#FA0EA0"))
#Z17
def tekst(text):
    a = chain(text)
    b = [r"\\u" + (str(hex(ord(let))).upper()[2:]).zfill(4) if ord(let) not in chain(range(65,91), range(97,123), range(48,58)) else let for let in a]
    return reduce(lambda x,y: x+y, b, initial = "")
print(tekst("Otpornost 10Ω."))
#Z18
def brojevi(str):
    return findall(r"\d+", str)
# print(brojevi("42+10=52;10*10=100"))
#Z19
def brojanje(str):
    a = chain(str)
    b = pairwise(a)
    c = [(x,y) for (x,y) in b if x == y]
    return len(c)
# print(brojanje("aatesttovi"))
#Z20
def izracunaj2(x, fun):
    return [fun(x[i-2], x[i-1], x[i]) for i in range(2,len(x))]
# print(izracunaj2([2, 5, 1, 6, 7], lambda x, y, z: x + y * z))