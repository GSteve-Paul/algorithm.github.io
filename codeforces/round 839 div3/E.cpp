#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        int cnt1=0,cnt2=0,cnt3=0;
        //player1不需要涂色的,player2不需要涂色的
        for(int i=1,temp;i<=n;i++)
        {
            cin >> temp;
            if(temp==i)
                cnt1++;
            else if(temp==n+1-i)
                cnt2++;
            else
                cnt3++;
        }
        if(cnt2+cnt3<=cnt1)
            cout << "First" << endl;
        else if(cnt1+cnt3<cnt2)
            cout << "Second" << endl;
        else
            cout << "Tie" << endl;
    } 
    return 0;
}