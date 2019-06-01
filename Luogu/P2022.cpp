#include <cstdio>
#include <iostream>
#include <cstring>

/*让我们来考虑1到N的正整数集合。让我们把集合中的元素按照字典序排列，
例如当N=11时，其顺序应该为：1,10,11,2,3,4,5,6,7,8,9。

定义K在N个数中的位置为Q(N,K)，例如Q(11,2)=4。现在给出整数K和M，要求找到最小的N，使得Q(N,K)=M。*/ 
//Q(k, k)显然是最小的，设为base 
int k, m, len;//len是输入的k的位数 ;
long long base, s, mi[20];//s是最后要求的n ;//k,m如题意，base是Q(n, k)的最小值即Q(k, k),mi[i]代表10^i 

int bs(int x) {
    char ss[12];
    sprintf(ss, "%d", x);//用字符串保存数字，便于按位计算 
    len = strlen(ss);
    int ans = 0, w = 0;
    for (int i = 0; i < len; i++) {
        w = (w << 3) + (w << 1) + ss[i] - '0';//w是k的前i+1位 
        ans += w - mi[i] + 1;//s加上从10^i到w的数字数 
    }
    return ans;
}

int main() {
    scanf("%d%d", &k, &m);
    mi[0] = 1;
    for (int i = 1; i <= 19; i++) {
        mi[i] = mi[i - 1] * 10;
    }
    for (int i = 0; i <= 9; i++) {
        if (k == mi[i] && m != i + 1) {
            printf("0");//特判，如果k是10^i那么m一定是i+1，否则无解 
        }
    }
    base = bs(k);//base是最小值 
    if (m < base) { 
        printf("0");
        return 0;
    }
    if (base == m) {
        printf("%d", k);
        return 0;
    }
    s = mi[len];//k有len位，mi[len]是10^len即比k刚好大一个数量级的10的幂 
    m -= base;//此时m>base，也就是说还差m-base个数排在k的前面 
    for (int i=1; ; i++) {
        long long tmp = k * mi[i] - mi[len + i - 1];//tmp是k*10^i-10^(len + i - 1)
        //10^(len - 1)是和k一个数量级的10的幂
        //10^(len - 1 + i)是比k大了i个数量级的10的幂
        //k*10^i是k变大i个数量级
        //也就是说tmp是k后面添i个0之后向下取到1最近的10的幂那么多个数字 
        if (m > tmp) {//如果m比tmp大了，也就是说我们取少了 
            m -= tmp; //那么m减去tmp，s再大一个数量级 
            s *= 10;
        } else {//否则就代表着取多了，直接跳出 
            break;
        }
    }
    s += m - 1;
    std::cout << s << std::endl;
//    printf("%lld", s);
    return 0; 
}
