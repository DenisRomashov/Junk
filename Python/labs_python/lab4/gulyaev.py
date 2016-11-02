
import random
import sys

def my_words(input):
    words =[]
    for line in open(input, 'r'):
        linewords = line.split()
		# получаем все слова из одной строки
        words += linewords
    return words
	# получаем все слова из всех строк (разделитель: пробел)

def mem_dict(input, output):
    words=my_words(input)
    my_slovar = {}
    last_index=len(words)
    for i in range(last_index):
        if words[i] in my_slovar:
            continue
        else:
            my_slovar[words[i]] = words[i + 1:last_index]
            # заполняем "ПОХОЖИЙ" словарь ( ключ: зн-ие1, зн-ие2, ... )
    stroka = str(words[0])
    index = words[0]
    while index != str(words[last_index - 1]):
        msr = random.choice(my_slovar[index])
        stroka += " " + str(msr)
        index = msr
    # создание "НОВОГО" текста
    print_to_output = open(output, 'w')
    print_to_output.write(stroka)
    print_to_output.close()
    # запись в файл
    return stroka


def main():
    args = sys.argv[1:]
    if len(args) > 2 or len(args) < 1:
        print
        'ERROR use: file.py file1.txt OR file.py file1.txt file2.txt'
        sys.exit(1)
    if len(args) == 2:
        print
        mem_dict(args[0], args[1])
        print
        mem_dict(args[1], args[1])
    if len(args) == 1:
        print
        mem_dict(args[0], "output.txt")


if __name__ == '__main__':
    main()
