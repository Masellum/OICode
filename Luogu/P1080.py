class Minister:
    a: int
    b: int

    def __init__(self, a: int, b: int) -> None:
        self.a = a
        self.b = b

    def __lt__(self, other) -> bool:
        return self.a * self.b < other.a * other.b


def main():
    n: int = int(input())
    l = list(map(int, input().split(' ')))
    a = int(l[0])
    a: int
    minister: [Minister] = []
    for i in range(n):
        l = list(map(int, input().split(' ')))
        t1, t2 = l[0], l[1]
        t1: int
        t2: int
        minister.append(Minister(t1, t2))
    minister.sort()
    ssum: int = a
    ans: int = -1
    size: int = len(minister)
    for i in range(size):
        ans = max(ans, int(ssum / minister[i].b))
        ssum *= minister[i].a
    print(ans)


if __name__ == "__main__":
    main()
