n, m, x1, y1, x2, y2 = map(int, input().split())
print("NO" if abs(x1 - x2) == abs(y1 - y2) else "YES" )