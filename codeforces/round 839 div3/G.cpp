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