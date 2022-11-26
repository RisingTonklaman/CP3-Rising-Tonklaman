from forex_python.converter import CurrencyRates
c = CurrencyRates()
c.get_rates('USD')
print(c.convert('USD', 'THB', 29.99))
#print(c.get_rates('USD','THB'))