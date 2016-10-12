#1.
# Вх: список строк, Возвр: кол-во строк
# где строка > 2 символов и первый символ == последнему
def me(words):
    count = 0
    for word in words:
        if len(word) > 2 and word[0] == word[-1]:
            count += 1
    return count
#2.
# Вх: список строк, Возвр: список со строками (упорядочено)
# за искл всех строк начинающихся с 'x', которые попадают в начало списка.
# ['tix', 'xyz', 'apple', 'xacadu', 'aabbbccc'] -> ['xacadu', 'xyz', 'aabbbccc', 'apple', 'tix']
def fx(words):
    xlist = sorted([word for word in words if word[0] == 'x'])
    xlist += sorted([word for word in words if word[0] != 'x'])
    return xlist

#3.
# Вх: список непустых кортежей,
# Возвр: список сортир по возрастанию последнего элемента в каждом корт.
#  [(1, 7), (1, 3), (3, 4, 5), (2, 2)] -> [(2, 2), (1, 3), (3, 4, 5), (1, 7)]
def tuple_sort(toplist):
    return sorted(toplist, key = lambda i: i[-1])

def main():
    print(me(["ww", "wxw", "qwerty", "LOL", "ll"]))
    print(fx(['aetix', 'xyz', 'apple', 'bara', 'zcd','xaba']))
    print(tuple_sort([(1,4),(5,1),(7,8,2),(12,4,5,3)]))

if __name__ == '__main__':
    main()
