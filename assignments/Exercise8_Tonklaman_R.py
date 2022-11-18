Username=input("Enter your Username:")
Password=input("Enter your Username:")
if Username=="Tonkla" and Password=="123456":
    print("Welcome to SuperShop")
    print("1.Esspresso  25 Bath")
    print("2.Americano  30 Bath")
    print("3.Latte      40 Bath")
    Menu=int(input("Choose your Menu:"))
    if Menu==1:
        List=int(input("How many do you want:"))
        print("Total prise are ",List*25)
    if Menu==2:
        List=int(input("How many do you want:"))
        print("Total prise are ",List*30)
    if Menu==3:
        List=int(input("How many do you want:"))
        print("Total prise are ",List*40)
    print("Thank you for purchasing ")
else : print("You do not have to access")