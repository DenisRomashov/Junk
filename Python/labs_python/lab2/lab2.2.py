# 1.
# Вх: строка. Если длина > 3, добавить в конец "ing",
# если в конце нет уже "ing", иначе добавить "ly".
def v(s):
    if len(s) > 3 and s.find('ing')==-1:
        return s+'ing'
    if len(s) > 3 and s.find('ing')!=-1:
        return s+'ly'
# 2.
# Вх: строка. Заменить подстроку от 'not' до 'bad'. ('bad' после 'not')
# на 'good'.
# Пример: So 'This music is not so bad!' -> This music is good!
def nb(s):
    n = s.find('not')
    b = s.find('bad')
    sub = s[n:b+3]
    return s.replace(sub,'good')

def test(res, expt):
    if res == expt:
        return True
    else:
        return False

print(test(v('rising'),'risingly'))
print(test(nb('This music is not so bad'), 'This music is good'))