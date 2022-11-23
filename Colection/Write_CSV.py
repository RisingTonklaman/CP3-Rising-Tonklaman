import csv
def creat_CSV() :
    with open('employee_file.csv', mode='w') as employee_file:
        employee_writer = csv.writer(employee_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
        employee_writer.writerow(['KamenRider ZI-O', 'King of Time', 'November'])
        employee_writer.writerow(['KamenRider GEIZ', 'Guardian of Time', 'March'])
        employee_writer.writerow(['KamenRider WOZ','Predictor of Time', 'August' ])
creat_CSV()
