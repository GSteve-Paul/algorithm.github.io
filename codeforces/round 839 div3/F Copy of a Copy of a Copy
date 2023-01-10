分析:
按照题意,我们容易知道对于两个operation,其中第一种最为重要,是本题目的核心所在.
了解到第一种operation的行为是选取一个周围四个与本身不同的格子然后自己反转.那么我们可以计算得出某一张图片中的这样的格子数量,我们可以记作特殊点.
因此我们容易知道:
1).每进行一次这样的operation 1,我们就可以使得特殊点的数量减少,减少的数量>=1.
之所以可能超过1,是因为存在以下的情况
0000
0100
1010
0100
其中把(3,2)点反转后,原先(2,2),(3,3)点也不再是特殊点
因此我们容易得出,特殊点的数量最多的图片就是初始图片.
随着operation1的不断进行,图片的特殊点数量不断下降.
因此,我们可以把输入的各个图片按照特殊点的数量从大到小排序.
2).排序后的图片的基本操作如下:
进行若干次的operation1后,进行一次operation2.
对于operation1的次数,取决于两个排序后相邻图片的前者的特殊点被反转的个数.其中对于前者特殊点发生的operation1的顺序并没有要求.
原因:如果有要求,意思就是反转的先后会对其他特殊点的存在判定会有影响.然而事实上是,如果某个特殊点被反转,那么它周围4个点如果有特殊点,那么这些特殊点一定废了,就压根不可能再反转.
这样题目内就隐含一个条件:不可能有两个相邻的特殊点都被反转.因此operation1的顺序并没有要求.

有了以上的分析:我们可以得出代码的逻辑结构:
1).获得输入的图片,然后找出每个图片中的特殊点
2).按照图片特殊点的个数从大到小排序
3).按照排序后的顺序,以特殊点的反转为operation1的依据,以图片的数量为operation2的依据,循环遍历得出答案

代码:
```C++
#include <bits/stdc++.h>
#define N 35
#define M 35
#define K 105
using namespace std;
int n,m,k;
struct Operation
{
    short type;
    int x,y;//1 point x,y
    int i;//2,index i
    Operation(){type=0;x=0;y=0;i=0;};
    Operation(int x,int y){type=1;this->x=x;this->y=y;}
    Operation(int i){type=2;this->i=i;}
};
struct Point
{
    int x,y;
    Point(){}
    Point(int x,int y){this->x=x;this->y=y;}
    bool operator == (struct Point b){return x==b.x && y==b.y;}
    bool operator != (struct Point b){return x!=b.x || y!=b.y;}
}nullPoint(0,0);
struct Picture
{
    bool matrix[N][M];
    int no;
    vector<struct Point> spePoint;
    struct Point isSpePoint(int x,int y)
    {
        if(x==1 || x==n || y==1 || y==m)
            return nullPoint;
        else
        {
            int tx[]={-1,0,1,0};
            int ty[]={0,-1,0,1};
            if(this->matrix[x][y]==1)//最中间的是1
            {
                int t;
                for(t=0;t<=3;t++)
                {
                    if(this->matrix[x+tx[t]][y+ty[t]]!=0)
                        break;
                }
                if(t>3)//满足要求
                    return Point(x,y);
                else
                    return nullPoint;
            }
            else//最中间的是0
            {
                int t;
                for(t=0;t<=3;t++)
                {
                    if(this->matrix[x+tx[t]][y+ty[t]]!=1)
                        break;
                }
                if(t>3)//满足要求
                    return Point(x,y);
                else
                    return nullPoint;
            }
        }
    }  
}picture[K];
queue<struct Operation> operation;
bool screenCmp(struct Picture a,struct Picture b){return a.spePoint.size() > b.spePoint.size();}
int main()
{
    scanf("%d %d %d",&n,&m,&k);//k copies, one initial
    getchar();
    getchar();
    //read
    for(int i=1;i<=k+1;i++)
    {
        //input a single picture
        for(int j=1;j<=n;j++)
        {
            picture[i].no=i;
            for(int k=1;k<=m;k++)
            {
                picture[i].matrix[j][k]=getchar()-'0';
            }
            getchar();
        }
        if(i!=k+1)
            getchar();
        //calculate the special points
        for(int j=2;j<=n-1;j++)
        {
            for(int k=2;k<=m-1;k++)
            {
                //考察picture[i].matrix[j][k]周围四个
                struct Point temp=picture[i].isSpePoint(j,k);
                if(temp!=nullPoint)
                    picture[i].spePoint.push_back(temp);
            }
        }
    }
    //sort those pictures, from big to little
    sort(picture+1,picture+k+1+1,screenCmp);//1~k+1
    //output the initial picture
    printf("%d\n",picture[1].no);
    //output the operations
    for(int i=2;i<=k+1;i++)
    {//当前:picture[i],上一个picture[i-1]
        for(int j=0;j<picture[i-1].spePoint.size();j++)
        {
            if(picture[i-1].matrix[picture[i-1].spePoint[j].x][picture[i-1].spePoint[j].y]
             !=picture[i].matrix[picture[i-1].spePoint[j].x][picture[i-1].spePoint[j].y])
            {
                operation.push(Operation(picture[i-1].spePoint[j].x,picture[i-1].spePoint[j].y));
            }
        }
        operation.push(Operation(picture[i].no));
    }
    printf("%lld\n",operation.size());
    while(!operation.empty())
    {
        if(operation.front().type==1)//type1
        {
            printf("1 %d %d\n",operation.front().x,operation.front().y);
            operation.pop();
        }
        else //type2
        {   
            printf("2 %d\n",operation.front().i);
            operation.pop();
        }
    }
    return 0;
}
```
