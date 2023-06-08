n = int(input())

names = set()
S, T = [], []
for i in range(n):
    s, t = input().split()
    names.add(s)
    S.append(s)
    T.append(t)

oneChange = False

while True:
    i = 0
    oneChange = False
    while i < len(S):
        if T[i] not in names:
            names.add(T[i])
            names.remove(S[i])
            T.pop(i)
            S.pop(i)
            oneChange = True
        i += 1

    if not oneChange:
        break

if (len(S) == 0):
    print("Yes")
else:
    print("No")
