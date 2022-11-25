from tkinter import *

x = 1
def sayHelloWorld():
   return print('Hello World',x)


MainWindow = Tk()
button = Button(MainWindow,text = "Click me",command = sayHelloWorld).grid(row=0)
#button.place(x = 50, y = 20)
button2 = Button(MainWindow,text = "Click me",command = sayHelloWorld,).grid(row=1)
MainWindow.mainloop()