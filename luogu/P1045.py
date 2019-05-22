import math
import re

j = 10 ** 500

def fastPower(x: int, k: int):
    res = 1
    base = x

    while k is not 0:
        if k & 1 == 1:
            res = res * base % j
        base = base * base % j
        k = k >> 1
    return res


def main():
    p: int = int(input())
    size: int = int(math.log10(2) * p) + 1
    print(size)
    res = str(fastPower(2, p) - 1)
    if len(res) < 500:
        res = ('0' * (500 - len(str(res)))) + res
    res = re.findall(r".{50}", res)
    res = "\n".join(res)
    print(res)

if __name__ == "__main__":
    main()
