分析:

由题意容易知道我们是先把对手的能力从小到大排序,然后依次比赛,到某一轮为止.

记对手的能力值的数组op[N]

我们不妨仔细分析一下第一轮:

首先    我们要找到当前x下,Monocarp最多能赢到哪一步.

不难发现,如果要赢到第i个人,即1~i赢,i+1~n输,那么也就是说在i处有最后的x+i-1>=op[i]=>x>=op[i]-i+1

似乎这个地方可以在每一轮开始用二分法找到i,但是这是会导致超时的

我们考虑新建一个数组A[N],专门用来装对应op[N]下Monocarp能赢的最小x

也许会有:A[i]=op[i]-i+1.但是这是不准确的

例如有以下op[N]数组:1,3,3,3,3,3,3.可知按以上的算法第一个3要求x>=2即可,而最后一个3却要求x>=-3.这是万万错误的.因为越到后面要求的x应当越高.

所以A[0]=0;A[i]=max(A[i-1],op[i]-i+1);

然后    我们要讨论x在这一轮中的变化情况

很明显,x在前面赢的时候在增加,x在后面输的时候在减少

因此,这里有两个特殊情况:

1.x最大的时候就是与第i个对手比赛后,这时候x=x+i,若x+i>=y,则无需再接着比赛,asw+=y-x已经结束咧!

2.而如果推算出初始x能够把所有人都打赢,则相当于比赛几次就打赢几次,那么asw+=y-x,可以直接把后面的算出来.

除开这两种特殊情况,还有就是必须把这一轮给打完,由此就有了这一轮对于x的净收益delta=i-(n-i)=2*i-n

若delta<=0,其实x就再也不会增大,而且由于之前两中特殊情况已经排除,则可以确定的是x已经没有了翻身之日,直接返回-1

若delta>0,x会不断增大.但是我们为了减少循环的次数,防止超时,应当计算出x在当前delta下最多比赛几轮

如果x能达到下一个对手的水准,则delta就会增加:具体而言有以下不等式:

delta*k+x >= A[i+1]

其中k为delta不变的情况下,x比赛的轮数,下一轮x就能击败第i+1个对手

注意到k必须要向上取整

但是我们也应当明白,有一定可能性在这k轮中某轮赢到最大x的时候x>=y,所以我们应当做两手准备:

delta*k0+x+i >= y

其中k0为delta不变的情况下,x达到y比赛的整轮数.这里等式左边多的i的原因同之前说的x+i>=y.

注意到k0也必须向上取整

因此计算出k,k0后,我们应当比较k和k0的大小.

如果k0<=k,那么
asw+=k0*n

x+=delta*k0 

asw+=y-x,然后直接结束

如果k0>k,那么

asw+=k*n 

x+=delta*k,继续循环

这个地方的=不严格属于<=,换成>=也是一样的,无非是多一次循环下一次的特殊情况1

也许看完有点晕,下面看看代码:
```C++
#include <bits/stdc++.h>
#define N (int)2e5+5
using namespace std;
long long int A[N];//要在某轮中赢第n个人,需要多少的x的值
long long int n,x,y,asw=0;
int main()
{
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)
    {
        asw=0;
        cin >> n >> x >> y;
        for(int i=1;i<=n;i++)
            cin >> A[i];
        sort(A+1,A+n+1);
        for(int i=1;i<=n;i++)
            A[i]=max(A[i]-i+1,A[i-1]);
        //第一轮
        while(x<y)
        {
            int i=upper_bound(A+1,A+n+1,x)-A-1;//1~i win,i+1~n lose
            if(i+x>=y || i==n)
            {
                asw+=y-x;
                break;
            }
            long long int delta=2*i-n;
            //每一轮的收益
            if(delta <=0)
            {
                asw=-1;
                break;
            }
            long long int k=(A[i+1]-x)/delta;//k表示能使i+1必须要多少整轮次,需要向上取整
            //delta*k+x >= A[i+1]
            if((A[i+1]-x)%delta>=1) k++;
            long long int k0=(y-x-i)/delta;//k0表示能使x->y至少需要多少整轮次,需要向上取整
            //delta*k0+x+i >= y;
            if((y-x-i)%delta>=1) k0++;
            if(k0<=k)
            {
                asw+=k0*n;
                x+=delta*k0;
                asw+=y-x;
                break;
            }
            else 
            {
                x+=delta*k;
                asw+=k*n;
            }
        } 
        cout << asw << endl;
    }
    return 0;
}
```
