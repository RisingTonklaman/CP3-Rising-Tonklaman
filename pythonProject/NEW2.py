inputz=int(input("Number of Round:"))
i=0
for x in range(inputz) :
    inputNumber=int(input("i"+str(x+1)+":"))
    i += inputNumber

    print(i ,end="")
print(i)