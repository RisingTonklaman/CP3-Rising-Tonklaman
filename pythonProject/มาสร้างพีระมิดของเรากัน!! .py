i=int(input('Enter your Input:'))
text=''
blank=''
for x in range(i):
    j=i-x-1
    z=2*x+1
    #print('j=',j)
    for k in range(j):
        blank+=' '
    for y in range(z):
        text+='*'
    print(blank+text)
    text = ''
    blank = ''