分析：
对于先手来说,最后所得的序列是想要升序,所以原来a[i]==i的地方是不需要染色的,那可以用cnt1来表示不需要染色的地方的数量.
对于后手来说,最后所得的序列是想要降序,所以原来a[i]==n+1-i的地方是不需要染色的,那就可以用cnt2表示后手所不需要染的地方.
cnt3表示的是都不等于的一种情况,即a[i]!=i && a[i]!=n+1-i的地方.

对于先手来说，先手想染所需要染的部分，后手肯定不会帮助先手染先手所需要的数字,即后手会和先手反着染,也就是染cnt1.反之亦然.

因此得出
后手想染色的是cnt1+cnt3,首先优先染cnt1
先手想染色的是cnt2+cnt3,首先优先染cnt2

可以明显的知道，只有在需要染色的地方全部染完之后然后进行一次重新排列才可能赢.
如果对于两个人来说都只剩一个需要染色,那么就会出现平局的状态,因为谁都不愿意染这个,因为再下一次对方会重新排列,然后输.这是平局的情况.

因此得出
cnt2+cnt3<=cnt1 先手必胜：保证了先手再后手还在染cnt1的时候，已经把该染的cnt2+cnt全部染完，这个时候先手必胜
为何可以取到等号:cnt2+cnt3代表的是先手,取等号意思是在某一轮中先手把cnt2+cnt3涂完了,然后后手也把cnt1涂完了,接着等到下一轮先手就把蓝色的反复交换而成功得到升序.
cnt1+cnt3<cnt2  后者必胜：与上面同理
为何不能取到等号:cnt1+cnt3代表的是后手,如果取到等号了,则在某一轮中在后手之前先手已经把cnt2涂完了,而之后后手就无法再涂,因为此时两个人都相当于只涂了cnt1+cnt3-1和cnt2+cnt3-1,都不愿意再图,这就导致了平局.
除了cnt2+cnt3<=cnt1和cnt1+cnt3<cnt2,其他情况全为平局.

解决方案如下:
C++
```
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
```
