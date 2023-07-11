from cs50 import get_int
while True:
    x = get_int("Height: ")
    if x > 0 and x < 9:
        break

for i in range(1, x + 1):
    print((" " * (x - i)) + ("#" * i) + "  " + ("#" * i))
