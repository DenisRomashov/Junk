# 1.
# Входящие параметры: int <count> ,
# Результат: string в форме
# "Number of: <count>", где <count> число из вход.парам.
# Если число равно 10 или более, напечатать "many"
# вместо <count>
# Пример: (5) -> "Number of: 5"
# (23) -> 'Number of: many'
def num_of_items(count):
    if count >= 10:
        return ("Number of: many")
    else:
        return ("Number of: {}".format(count))
# 2.
# Входящие параметры: string s,
# Результат: string из 2х первых и 2х последних символов s
# Пример 'welcome' -> 'weme'.
def start_end_symbols(s):
    return (s[0:2]+s[len(s)-2:len(s)])
# 3.
# Входящие параметры: string s,
# Результат: string где все вхождения 1го символа заменяются на '*'
# (кроме самого 1го символа)
# Пример: 'bibble' -> 'bi**le'
# s.replace(stra, strb)
def replace_char(s):
    s1 = s[0]
    s = s.replace(s[0], '*')
    s = s.replace(s[0], s1, 1)
    return s
# 4
# Входящие параметры: string a и b,
# Результат: string где <a> и <b> разделены пробелом
# а превые 2 симв обоих строк заменены друг на друга
# Т.е. 'max', pid' -> 'pix mad'
# 'dog', 'dinner' -> 'dig donner'
def str_mix(a, b):
    return (a.replace(a[0:2],b[0:2])+' '+b.replace(b[0:2],a[0:2]))
def main():
    print("#1")
    print(num_of_items(3))
    print(num_of_items(10))
    print("#2")
    print(start_end_symbols("qwerty"))
    print("#3")
    print(replace_char("qwertq qqq gfjkq."))
    print("#4")
    print(str_mix("qwerty", "2016"))

if __name__ == '__main__':
    main()