menuList=[]
priseList=[]
menuPrise=[]
while True:
  menuName = input('Plese Enter Menu :')
  if(menuName.lower() == 'exit'):
    break
  else:
    priseName = int(input('Enter Your Prise :'))
    menuList.append(menuName)
    priseList.append(priseName)
i=1
total=0
while i <= len(menuList) :
  print(menuList[i-1],'     ',priseList[i-1])
  total+=priseList[i-1]
  i+=1
print('totalprise =',total)
