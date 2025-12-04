lista = [["a", "b"], ["c", "d"]]
for l in lista:
    if "a" in l:
        print("JESTE")
    else:
        print("NIJE")

lista2 = sorted(lista)
lista3 = lista.copy()
lista4 = list(lista)

print("ID liste 1: {}".format(id(lista)))
print("ID liste 2: {}".format(id(lista2)))
print("ID liste 3: {}".format(id(lista3)))
print("ID liste 4: {}".format(id(lista4)))

tapl = ("hi")
tapl2 = ("hi", ["hey", "everyone"])
tapl3 = ("world",)

tapl3 += tapl2

print(f"Tip tapl-a je {type(tapl)}")
print(f"Tip tapl-a 2 je {type(tapl2)}")

print(tapl3)

tapl3[2].append("!!!!")

print(tapl3)

print("-------------------------")

recnik = {
    "make": "VW",
    "model": "Golf V",
    "year": 2004
}
print(type(recnik))
print(recnik)
for i in recnik.items():
    print(f"{i} | {type(i)}")

print("================================")

set1 = {"skinner", "scully", "mulder"}
set2 = {6,2,9,5,1}
set1.update(set2)
print(set1)
print(type(set1))
for i in set1:
    print(i)

for x in range(len(lista)):
    print(lista[x])

for x in range(10, 20):
    print(x)
    if(x % 7 == 0):
        break
else:
    print("hello")

def funkcija1(x, y = "lesnik"):
    print(f"{x} je mnogo bolje od {y}")

funkcija1("sladoled", "banana")




