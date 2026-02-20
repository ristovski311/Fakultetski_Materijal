# Zadatak 1
def parni(lista):
    parni = []
    neparni = []
    for broj in lista:
        if broj % 2 == 0:
            parni.append(broj)
        else:
            neparni.append(broj)
    return {
        'Parni': parni,
        'Neparni': neparni
    }

def parni_better(lista):
    return {
        'Parni': list(filter(lambda x: x%2==0, lista)),
        'Neparni': list(filter(lambda x: x%2==1, lista))
    }
    
# res = parni(range(1,10))
# print(res)
# res2 = parni_better(range(1,10))
# print(res2)



# Zadatak 2
def numlista(lista):
    d = {}
    for el in lista:
        if(type(el).__name__ in d.keys()):
            d[type(el).__name__].append(el)
        else:
            d[type(el).__name__] = [el]
    return d

# res3 = numlista([1, "ej", True, [1,2], 3, False, "Caos", {1, "e"}])
# print(res3)



# Zadatak 3
def uredi(lista, N, num):
    if(N > len(lista) or N < -len(lista)): # Cisto da nemamo greske
        N = len(lista)
    for x in range(N):
        lista[x] += num
    for x in range(N, len(lista)):
        lista[x] -= num
    
# lista = [1,2,3,4,5]
# uredi(lista, -6 ,1)
# print(lista)



# Zadatak 4
def zbir(lista):
    nova = []
    for x in range(1, len(lista)):
        nova.append(lista[x - 1] + lista[x])
    return nova

# lista = [1,2,3,4,5,6,7,8,9,10]
# res = zbir(lista)
# print(res)



# Zadatak 5
def brojel(lista):
    rez = []
    for x in lista:
        if(type(x) == type([])):
            rez.append(len(x))
        else:
            rez.append(-1)
    return rez

# lista = [1, [1,2], [1, 2, 3, 4, [4, 5]], True, [2]]
# print(brojel(lista))

# Zadatak 6
def razlika(lista1, lista2):
    res = []
    tuplovi = [(el, type(el)) for el in lista2]
    for x in lista1:
        if((x, type(x)) not in tuplovi):
            res.append(x)
    return res
    
    # res = [] # OVO NE RADI ZATO STO JE True == 1
    # for x in lista1:
    #     if(x not in lista2):
    #         res.append(x)
    # return res

# lista = [1, 4, 6, "2", "6", True]
# lista2 = [4, 5, "2", 1]
# res = razlika(lista, lista2)
# print(res)


# Zadatak 7
def saberi(lista):
    res = []
    for x in lista:
        res.append(sum(x))
    return res

def saberi_better(lista): # tehnicki jos nismo radili comprehensions tkd nzm
                          # moze u mnogo gornjih f-ja da se primeni i bas je dobra stvar 
    return [sum(x) for x in lista]

# lista = [(1,2,3), (4,5), (6,)]
# print(saberi(lista))
# print(saberi_better(lista))



# Zadatak 8
def izmeni(lista):
    for x in range(1, len(lista)):
        lista[x] += lista[x-1]

# lista = [1,2,4,7,9]
# izmeni(lista)
# print(lista)



# Zadatak 9
def prosek(lista):
    res = []
    for x in lista:
        res.append(sum(x) / len(x))
    return res

# lista = [[1,2,3,4,5], [1,2,3], [2,4,6,8,10,12], [3, 3, 3], [3,4,7]]
# print(prosek(lista))



# Zadatak 10
def izbroj(param):
    res = 0
    if(type(param) == type([])):
        for x in param:
            res += izbroj(x)
    else:
        res = 1
    return res

# Da l treba rekurzivna nemam ideju ali ajd

# lista = [1, [2, 3], [4, 5, [6, 7, [8]]], 9, 10, [11, 12], 13]
# print(izbroj(lista))



# Zadatak 11
def razlika2(lista):
    res = []
    for x in range(1, len(lista)):
        res.append(lista[x-1] - lista[x])
    return res

# lista = [8,5,3,1,1]
# print(razlika2(lista))



# Zadatak 12
def presek(lista1, lista2):
    res = []
    tuplovi = [(el, type(el)) for el in lista2]
    for x in lista1:
        if((x, type(x)) in tuplovi):
            res.append(x)
    return res

# lista1 = [1, 4, 6, "2", "6", True]
# lista2 = [4, 5, "2", 1]
# print(presek(lista1, lista2))



# Zadatak 13
def izmeni(lista):
    pp = []
    np = []
    for x in range(len(lista)):
        if(x % 2 == 0):
            pp.append(lista[x] + 1)
        else:
            np.append(lista[x] - 1)
    return {
        'pp': pp,
        'np': np
    }

# lista = [0,1,2,3,4,5,6,7,8,9,10]
# print(izmeni(lista))



# Zadatak 14
def unija(lista1, lista2):
    set1 = set(lista1)
    set2 = set(lista2)
    set1.update(set2)
    return list(set1)

# print(unija([1,2,3,4,5,1,2,3], ["a", 4, 5, "b"]))



# Zadatak 15
def izdvoji(lista):
    rez = []
    for x in range(len(lista)):
        if(len(lista[x]) < x+1):
            rez.append(0)
        else:
            rez.append(lista[x][x])
    return rez

# lista = [[1,2,3], [3,2,4,5], [1], [1,2,3,4], [6,3,8,9,2], [2,7]]
# print(izdvoji(lista))



# Zadatak 16
def brojanje(recnik):
    tipovi = {}
    for x in recnik.values():
        if(type(x).__name__ not in tipovi):
            tipovi[type(x).__name__] = 1
        else:
            tipovi[type(x).__name__] += 1
    return tipovi

# print(brojanje({1 : 4, 2 : [2, 3], 3 : [5, 6], 4 : 'test', 5 : 9, 6 : 8})) 
 
    
# Zadatak 17
def kreiraj(n):
    lista = []
    cur = 0
    for x in range(n):
        cur+=x
        lista.append((x, cur*cur))
    return lista

# print(kreiraj(6))



# Zadatak 18
def kreiraj2(lista):
    rez = []
    for x in range(len(lista)-1):
        tuplovi = [(el, type(el)) for el in lista[x+1]]
        rez.append([element for element in lista[x] if (element, type(element)) not in tuplovi])    
    return rez

# print(kreiraj2([[1,2,3, True], [1,2,4,5], [4,5,6,7], [1,5]]))



# Zadatak 19
def stepenuj(lista):
    rez = []
    for x in lista:
        m = x[0]
        for y in range(1,len(x)):
            m = m ** x[y]
        rez.append(m)
    return rez

# print(stepenuj([(1, 4, 2), (2, 5, 1), (2, 2, 2, 2), (5, )]))


# Zadatak 20
def boje(rgb):
    r = rgb[1:3]
    g = rgb[3:5]
    b = rgb[5:7]
    return {
        "Red": int(f"0X{r}", base=16),
        "Green": int(f"0X{g}", base=16),
        "Blue": int(f"0X{b}", base=16)
    }
    
# print(boje("#FA1AA0"))
# print(boje("#37760B"))