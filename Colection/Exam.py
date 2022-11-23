hours = int(input())
minu = int(input())
k=0
Time = hours*60+minu
Time -= 20
Time-=60
k+=10
Time-=60
k+=20
L=Time/60
k+=L*40
print(k)