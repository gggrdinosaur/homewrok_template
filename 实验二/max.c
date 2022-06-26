#include <stdio.h>
#include <stdlib.h>
#include  <math.h>
#include <time.h>

int V[3000][3000];//前i个物品装入容量为j的背包中获得的最大价值
//随机数生成算法
void Random ( int list[] , int n)
{
    int a = 13; //乘数
    int m = 1000; //模数
    int c = 89; //增量
    for (int i = 0; i < n ;i++)
    {
        list[i + 1] = (a * list[i] + c) % m;
    }
}

int max(int a,int b)
{
   if(a>=b)
       return a;
   else return b;
}

int KnapsackDP(int n,int w[],int v[],int x[],int C)
{
    int i,j;
	//填表,其中第一行和第一列全为0
    for(i=0;i<=n;i++)
        V[i][0]=0;
    for(j=0;j<=C;j++)
        V[0][j]=0;
    for(i=1;i<=n;i++)
	{
        for(j=1;j<=C;j++)
		{
            if(j<w[i-1])
			{
				V[i][j]=V[i-1][j];
			}
            else
			{
                V[i][j]=max(V[i-1][j],V[i-1][j-w[i-1]]+v[i-1]);
			}
		}
	}
	//判断哪些物品被选中
            j=C;
            for(i=n;i>=1;i--)
            {
            if(V[i][j]>V[i-1][j])
                {
					x[i]=1;
					j=j-w[i-1];
                }
            else
                x[i]=0;
            }
            printf("选中的物品是:\n");
            for(i=1;i<=n;i++)
                printf("%d ",x[i]);
            printf("\n\n");
        return V[n][C];

}

void main()
{
    time_t t;
    struct tm * lt;
    time (&t);
    lt = localtime (&t);
    int begin,end;

    int s;//获得的最大价值
    int n;
    int C;//背包最大容量
    printf("请输入背包的最大容量:\n");
    scanf("%d",&C);

    printf("输入物品数:\n");
    scanf("%d",&n);

    int w[n];//物品的重量
    int v[n];//物品的价值
    int x[n];//物品的选取状态
    w[0] = 15;
    v[0] = 20;
    Random(w,n);//随机生成重量
    Random(v,n); //随机生成价值

    printf("物品重量：\n");
    for(int i = 0;i < n;i++){
        printf(" %d ",w[i]);
    }
    printf("\n\n");

    printf("物品价值：\n");
    for(int i = 0;i < n;i++){
        printf(" %d ",v[i]);
    }
    printf("\n\n");
    begin=clock();

    s=KnapsackDP(n,w,v,x,C);
    end = clock();	//计时结束

    printf("最大价值为:\n");
    printf("%d\n",s);
    printf("Running：%dms\n", end-begin);
    time (&t);
    lt = localtime (&t);


}
