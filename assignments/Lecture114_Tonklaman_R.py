from forex_python.converter import CurrencyRates
class Currency(CurrencyRates):
    def converting(self):
        type_my_currency = input('my wonder currency are:')
        type_currency_convert = input('I want to convert to:')
        my_currency = int(input('Enter my money how much I want to convert:'))
        convert = Currency().convert(type_my_currency, type_currency_convert, my_currency)
        return print(my_currency,type_my_currency,'=',convert,type_currency_convert)
    def Currency_Check(self):
        type_my_currency = input('my wonder currency are:')
        c_rate = Currency().get_rates(type_my_currency)
        for i in c_rate :
            print('1',type_my_currency,'=',c_rate[i],i)

def program():
    print("----- choose your program -----")
    print("1. Convert money")
    print("2. Currency check")

program()
my_program = int(input('my program are:'))
if my_program == 1 :
    Currency().converting()
elif my_program == 2 :
    Currency().Currency_Check()
