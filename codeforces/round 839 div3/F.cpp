#include <algorithm>
#include <queue>
#include <cstdio>
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