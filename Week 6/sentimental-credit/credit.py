# TODO
from cs50 import get_int
num = get_int("Number: ")
snum = (str(num))
start =snum[:2]
x = True
sum = 0
for i in snum[::-1]:
    x = not x
    if x:
        product = 2 * int(i)
        sum += product // 10 + product % 10
    else:
        sum += int(i)
print(sum)
if (len(snum) < 13 or len(snum) > 16):
    print("INVALID")
elif start == "34" or start == "37":
    print("AMEX")
elif  start in ["51", "52", "53", "54", "55"]:
    print("MASTERCARD")
elif  snum[0] == "4"  and sum % 10 == 0:
    print("VISA")
else:
    print("INVALID")

