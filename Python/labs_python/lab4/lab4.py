import random
import sys

def mem_dict(filename):
    f = open(filename, 'r')
    words = f.read().strip('\n').split()
    word_dict = {'': words}

    for i, w in enumerate(words):
        if w not in word_dict:
            word_dict[w] = words[i + 1:]

    #print(word_dict)
   # print()
    return word_dict, words


def print_dict(arg_tuple):
    my_dict = arg_tuple[0]
    my_words = arg_tuple[1]

    output = list()
    choice = ''
    count = 0
    while True:
        if my_dict[choice]:
            output.append(random.choice(my_dict[choice]))
            choice = output[-1]
            #print(choice)
        else:
            output.append(random.choice(my_dict['']))
            choice = output[-1]
        count += 1
        if count == len(my_words):
            break

    print(' '.join(output))

def main():
    print_dict(mem_dict(sys.argv[1]))

if __name__ == '__main__':
    main()
