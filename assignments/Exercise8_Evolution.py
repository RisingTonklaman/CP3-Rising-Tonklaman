usernameInput = input("Username : ")
passwordInput = input("Password : ")
def login(usernameInput,passwordInput):
    if usernameInput == "Tonkla" and passwordInput == "123456":
        return True
    else:
        return False
def showMenu():
print("----- iShop -----")
print("1. Vat Calculator")
print("2. Price Calculator")
userSelected = int(input(">>"))
if login(usernameInput,passwordInput)==True :
    print(showMenu())
    def menuSelect(userSelected):
        if userSelected == 1 :
            return vatCalculator(totalPrice)
        else: userSelected == 2
            return priceCalculator() :
    def vatCalculator(totalPrice):
        price = int(input("Price (THB) : "))
        vat = 7
        result = price + (price * vat / 100)
        return result

    def priceCalculator():
        price1 = int(input("First Product Price : "))
        price2 = int(input("Second Product Price : "))
        return print(price1 + price2)