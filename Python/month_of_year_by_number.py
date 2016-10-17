#Функция одной математической формулой по номеру месяца считает количество дней в нем
def days_in_month(number_of_month):
    days_in_month = (28 + (number_of_month + number_of_month // 8) % 2 + 2 % number_of_month + 1 // number_of_month * 2)
    return days_in_month


if __name__ == "__main__":
    number = int(input("Введите номер месяца: "))
    print("- - - - - - - - - - - - ")
    print('   В {} месяце {} дней'.format(number, days_in_month(number)))

#https://tproger.ru/problems/days-in-month-formula/#more-22220