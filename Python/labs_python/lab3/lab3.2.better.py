import sys
import re
from bs4 import BeautifulSoup


def extr_name(filename):
    try:
        file = open(filename, 'r')
    except IOError:
        print
        'error open ', filename
    else:
        males = []
        females = []
        mysoup = BeautifulSoup(file.read(), 'html.parser')
        tables = mysoup.find_all('table', summary="Popularity for top 1000")
        for table in tables:
            for row in table.find_all('tr', align="right"):
                cell = row.find_all('td')
                males.append(str(cell[1].string + ' ' + cell[0].string))
                females.append(str(cell[2].string + ' ' + cell[0].string))
        all = sorted(males + females)
        all.insert(0, filename.replace('name', '').replace('.html', ''))
        return (all, males, females)


def main():
    args = sys.argv[1:]
    if not args:
        print
        'use: [--file] file [file ...]'
        sys.exit(1)
    else:
        for arg in args:
            (all, males, females) = extr_name(arg)
            print (all)
            print ('top 10 males ' + str(sorted(males, key=lambda x: int(re.search('\d+', x).group(0)))[:10]))
            print ('top 10 females ' + str(sorted(females, key=lambda x: int(re.search('\d+', x).group(0)))[:10]))


if __name__ == '__main__':
    main()
