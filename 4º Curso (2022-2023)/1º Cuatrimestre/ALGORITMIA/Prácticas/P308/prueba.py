import p308

T=[15, 2, 10, 200, 1, 16]
assert(p308.split(T) == [ 2, 10,  1], 15, [200,  16])
print("QSel recursivo")
for i in range(len(T)+1):
    aux = p308.qsel(T, i)
    print(i, aux)
print("QSel NO recursivo")

for i in range(len(T)+1):
    aux = p308.qsel_nr(T, i)
    print(i, aux)

print(p308.pivot5(T))

print("QSel 5")

for i in range(len(T)+1):
    aux = p308.qsel5_nr(T, i)
    print(i, aux)

print(p308.qsort_5(T))
str_1 = "biscuit"
str_2="suitcase"
print("-------------")
print("Tiene que ser un 6 -> " + str(p308.edit_distance(str_1, str_2)))
print(p308.max_common_subsequence(str_1, str_2))

l_dims = [50, 10, 40, 30, 5]
l_dims2 = l_dims + [20]
l_dims3 = [30, 35, 15, 5, 10]
print("Tiene que dar 10500 -> %d" % p308.min_mult_matrix(l_dims))
print("Tiene que dar 15500 -> %d" % p308.min_mult_matrix(l_dims2))
print("Tiene que dar 9375 -> %d" % p308.min_mult_matrix(l_dims3))
