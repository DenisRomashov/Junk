# 1.
# Вх: список чисел, Возвр: список чисел, где
# повторяющиеся числа урезаны до одного
# пример [0, 2, 2, 3] returns [0, 2, 3].
def rm_adj(nums):
    new_list = []
    for i in nums:
        if i not in new_list:
            new_list.append(i)
    return (new_list)

def rm_adj2(nums):
    nums = [e for i,e in enumerate(nums) if e not in nums[:i]] #РАЗОБРАТЬ
    return nums

# 2. Вх: Два списка упорядоченных по возрастанию, Возвр: новый отсортированный объединенный список
def merge_lists(list_one, list_two):
    list = list_one + list_two
    list.sort()
    return list


def main():
    print(rm_adj([0, 1, 9, 6, 0, 3, 9]))
    print(rm_adj2([0, 1, 9, 6, 0, 3, 9]))
    print(merge_lists([0, 1, 3, 9, 15, 21, 30], [2, 4, 7, 8]))

if __name__ == '__main__':
    main()