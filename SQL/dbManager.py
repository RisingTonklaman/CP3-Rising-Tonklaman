import sqlite3
file = sqlite3.connect('chinook.db')

customer = file.execute('SELECT CustomerId , FirstName as "Namu", LastName FROM customers;')
for i in customer :
    print('customerID:',i[0],'  NAME ',i[1])