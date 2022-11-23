m = int(input())
n = int(input())
K = list()
J = list()
for M in range(m) :
    for N in range(n):
        #print(N)
        J.append(int(input()))
    #print(M)
    K.append(J)
    J = list()
print(K)
K.scale(0, 1)
for M in range(m) :
    for N in range(n):
        print(K[M][N],end=' ')
    print()



