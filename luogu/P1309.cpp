#include <algorithm>
#include <cstdio>

const int MAXN = 100000 + 5;

struct Person {
    int score, ability, num;

    bool operator<(const Person &that) {
        if (this->score == that.score) {
            return this->num < that.num;
        } else {
            return this->score > that.score;
        }
    }
} person[MAXN * 2], winner[MAXN], loser[MAXN];

void merge(Person a[], Person b[], Person result[], int len) {
    int cnt = 0, i, j;
    for (i = 1, j = 1; i <= len && j <= len;) {
        if (a[i] < b[j]) {
            result[++cnt] = a[i++];
        } else {
            result[++cnt] = b[j++];
        }
    }
    for (; i <= len;) {
        result[++cnt] = a[i++];
    }
    for (; j <= len;) {
        result[++cnt] = b[j++];
    }
}

int n, r, q;

int main() {
#ifndef ONLINE_JUDGE
    freopen("testdata/P1309.in", "r", stdin);
    freopen("testdata/P1309.out", "w", stdout);
#endif
    scanf("%d %d %d", &n, &r, &q);
    // for (int i = 1; i <= 2 * n; ++i) {
    //     scanf("%d", &person[i].score);
    // }
    // for (int i = 1; i <= 2 * n; ++i) {
    //     scanf("%d", &person[i].ability);
    // }
    for (int i = 1; i <= 2 * n; ++i) {
        person[i].num = i;
    }
    std::for_each(person + 1, person + 2 * n + 1,
                  [](Person &p) { scanf("%d", &p.score); });
    std::for_each(person + 1, person + 2 * n + 1,
                  [](Person &p) { scanf("%d", &p.ability); });
    std::sort(person + 1, person + 2 * n + 1);
    int wincnt = 0, losecnt = 0;

    for (int j = 1; j <= r; ++j) {
        wincnt = losecnt = 0;
        for (int i = 1; i <= 2 * n; i += 2) {
            if (person[i].ability > person[i + 1].ability) {
                person[i].score++;
                winner[++wincnt] = person[i];
                loser[++losecnt] = person[i + 1];
            } else {
                person[i + 1].score++;
                winner[++wincnt] = person[i + 1];
                loser[++losecnt] = person[i];
            }
        }
        merge(winner, loser, person, n);
    }
    printf("%d\n", person[q].num);
    return 0;
}