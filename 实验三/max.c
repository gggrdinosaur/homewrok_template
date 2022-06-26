#include <stdio.h>
#include <stdlib.h>
#include  <math.h>
#include <time.h>


int n;                 //输入的物品数
int SelectNumber;         //选中物品的数量，即单位重量价值降序排列后的前几个物品
float MaxValue;        //选中物品的总价值
float TotalWeight;         //选中物品的总重量
float LimitWeight;         //输入的限制总重量
struct  goods        //物品结构
{
    int order;         //物品序号
    float weight;         //物品重量
    float value;         //物品价值
    float UnitValue;          //物品单位重量价值
}good;


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

void CheckOut(struct goods g[] ,int num,float tw)   //检查排序后的物品集中选择多少个物品不超过限重
{
    int i;
    SelectNumber=0;
    TotalWeight=0.0;
    MaxValue=0.0;
    for(i=0;i<num;i++)
        if(TotalWeight+g[i].weight <=tw )   //从已排序的物品中选出一个物品，测试增加一个物品后是否超过限重
        {
            MaxValue+=g[i].value;
            TotalWeight=TotalWeight+g[i].weight;
            SelectNumber++;
        }
        else   //一旦超重则停止对后面物品的选择，退出循环，结束函数执行
            break;
}

void sort(struct goods g[] ,int num)                  //对所有物品单位重量价值按降序排列
{
    float temp,max;
    int i,j,flag,position,temporder;
    for(i=0;i<num-1;i++)
    {   max=g[i].UnitValue;
        flag=0;
        for(j=i+1;j<num;j++)
            if(max<g[j].UnitValue)
            {   position=j;
                max=g[j].UnitValue;
                flag=1;
            }
        if(flag)
        {   temp=g[i].UnitValue;                     //交换单位重量价值
            g[i].UnitValue=max;
            g[position].UnitValue=temp;
            temp=g[i].value;                       //交换价值
            g[i].value=g[position].value;
            g[position].value=temp;
            temp=g[i].weight;                      //交换重量
            g[i].weight=g[position].weight;
            g[position].weight=temp;
            temporder=g[i].order;                   //交换序号
            g[i].order=g[position].order;
            g[position].order=temporder;
        }
    }
}


int main()
{
    time_t t;
    struct tm * lt;
    time (&t);
    lt = localtime (&t);
    int begin,end;

    int i;
    printf("请输入物品个数:\n");
    scanf("%d",&n);
    struct goods  good[n];
    int w[n];//物品的重量
    int v[n];//物品的价值
    w[0] = 15;
    v[0] = 20;
    printf("\n请输入背包最大的重量:\n");
    scanf("%f",&LimitWeight);
    Random(w,n);//随机生成重量
    Random(v,n); //随机生成价值
    for(i=0;i<n;++i)
    {
        good[i].weight = w[i];
        good[i].value = v[i];
        good[i].UnitValue=good[i].value/good[i].weight;
        good[i].order=i;
    }
    printf("\n输入的物品有：\n");
    printf("序号  重量    价值\n");
    for(i=0;i<n;i++)
        printf("%3d   %.2f   %.2f\n",good[i].order+1,good[i].weight,good[i].value);


    begin=clock();

    sort(good,n);                          //对物品按单位重量价值降序排列
    CheckOut(good,n,LimitWeight);               //调用选择物品函数

    end = clock();	//计时结束

    printf("\n被选中的物品有：\n");
    printf("序号  重量    价值\n");
    for(i=0;i<SelectNumber;i++)
        printf("%3d   %.2f   %.2f\n",good[i].order+1,good[i].weight,good[i].value);
    printf("合计总价值为: %f\n",MaxValue);

    printf("Running：%dms\n", end-begin);
    time (&t);
    lt = localtime (&t);
}
