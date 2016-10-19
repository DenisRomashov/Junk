import codecs
import sys
from bs4 import BeautifulSoup

class NameRaitingGender:
    def __init__(self, name, rank, gender):
        self.name = name
        self.rank = rank
        self.gender = gender
    def printVal(self):
        print (self.name + " " + self.rank)


def extr_name(filename):
    try:
        f = codecs.open(filename, 'r')
    except IOError:
        print('cannot open', filename)
    else:
        soup = BeautifulSoup(f.read(), 'html.parser')
        tables = soup.find_all('table', summary="Popularity for top 1000")
        names = list()
        for table in tables:  # если больше одной таблице
            for row in table.find_all('tr', align="right"):  # По строчкам в таблице, tr align="right"><td>1</td><td>Jacob</td><td>Emily</td>
                fields = row.find_all('td')
                names.append(NameRaitingGender(fields[1].string, fields[0].string, "M"))  # [<td>982</td>, <td>Lennon</td>, <td>Rory</td>]
                names.append(NameRaitingGender(fields[2].string, fields[0].string, "W"))  # вырезаем 982 Lennon и Rory и добавляем к names

    names = sorted(names, key=lambda field: field.name)  # так как names 3 поля, указываем по какому полю сортируем
    names.insert(0, filename.replace('name', '').replace('.html', ''))  # добавляем на [0] измененное имя файла
    return names

def isExsist(elem, listElem):
  for elem2 in listElem:
    if elem.name == elem2.name:
      return True
  return False

def main():
  args = sys.argv[1:] #принимает больше 1 аргумента
  if not args:
    print ('use: [--file] file [file ...]')
    sys.exit(1)
  else:
    #Вывод всего списка
    for arg in args:
      nameList = set()
      names = extr_name(arg)
      print ('==============  ',names[0],'  ==============')
      names.remove(names[0])
      for name in names:
        if not isExsist(name, nameList):
          nameList.add(name)
        name.printVal()
      print("=====================================")
      #Составление списков ТОП 10
      men = list()
      women = list()
      for elem in nameList:
        if elem.gender == 'M':
          men.append(elem)
        else:
          women.append(elem)
      #Вывод ТОП 10
      print ("==========  TOP  10  MAN  ==========")
      for name in sorted(men, key=lambda field: field.name)[:10]:
        name.printVal()
      print("=====================================")
      print("=========  TOP  10  WOMEN  =========")
      for name in sorted(women, key=lambda field: field.name)[:10]:
        name.printVal()
      print("=====================================")

if __name__ == '__main__':
    main()