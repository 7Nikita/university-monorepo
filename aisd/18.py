x = int(input())
if x % 400 == 0:
    print("YES")
elif x % 100 != 0 and x % 4 == 0:
    print("YES")
else:
    print("NO")