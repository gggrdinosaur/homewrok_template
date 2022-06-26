#include <stdio.h>
#include <stdlib.h>
#include  <math.h>

int bubblenumber = 0;//冒泡排序比较次数
int mergenumber = 0;  //归并排序比较次数
int pivotnumber = 0;  //快速排序比较次数


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


//冒泡排序
int bubbleSort(int list[], int n)
{
    int numberOfPairs = n ;
    int swappedElements = 1;
    int tmp;

    while (swappedElements == 1)
    {
        numberOfPairs--;
        swappedElements = 0;
        for (int i = 0; i < numberOfPairs; i++)
        {
            if(list[i] > list[i + 1])
            {
                bubblenumber++;  //比较次数
                tmp = list[i];
                list[i] = list[i +1];
                list[i +1] =tmp;
                swappedElements = 1;
            }
        }
    }
}

//归并排序
void Merge(int arr[], int low, int mid, int high){
    int i, k;
    int *tmp = (int *)malloc((high-low+1)*sizeof(int));
    //申请空间，使其大小为两个
    int left_low = low;
    int left_high = mid;
    int right_low = mid + 1;
    int right_high = high;
    for(k=0; left_low<=left_high && right_low<=right_high; k++){
        mergenumber++;// 比较两个指针所指向的元素
        if(arr[left_low]<=arr[right_low]){
            tmp[k] = arr[left_low++];
        }else{
            tmp[k] = arr[right_low++];
        }
    }
    if(left_low <= left_high){  //若第一个序列有剩余，直接复制出来粘到合并序列尾
    //memcpy(tmp+k, arr+left_low, (left_high-left_low+l)*sizeof(int));
    for(i=left_low;i<=left_high;i++)
        tmp[k++] = arr[i];
    }
    if(right_low <= right_high){
    //若第二个序列有剩余，直接复制出来粘到合并序列尾
    //memcpy(tmp+k, arr+right_low, (right_high-right_low+1)*sizeof(int));
        for(i=right_low; i<=right_high; i++)
            tmp[k++] = arr[i];
    }
    for(i=0; i<high-low+1; i++)
        arr[low+i] = tmp[i];
    free(tmp);
    return;
}
void MergeSort(int arr[], unsigned int first, unsigned int last){
    int mid = 0;
    if(first<last){
        mid = (first+last)/2;
        MergeSort(arr, first, mid);
        MergeSort(arr, mid+1,last);
        Merge(arr,first,mid,last);
    }
    return;
}

//快速排序
int PivotList (int list[] ,int first, int last)
{
    int PivotValue = list[first];
    int PivotPoint = first;
    int tmp;
    for (int index =first+1; index <= last ;index++)
    {
        if(list[index] < PivotValue)
        {
            pivotnumber++;
            PivotPoint++;
            tmp = list[PivotPoint];
            list[PivotPoint] = list[index];
            list[index] =tmp;
        }
    }

    tmp = list[first];
    list[first] = list[PivotPoint];
    list[PivotPoint] = tmp;
    return PivotPoint;
}

void QuickSort(int list[] , int first,int last)
{
    int pivot;
    if(first < last)
    {
        pivot = PivotList(list,first, last);
        QuickSort(list,first,pivot - 1);
        QuickSort(list, pivot + 1, last);
    }
}

int main (int argv, char **argc)
{
    int n ;//数组元素个数
    printf("请输入随机数个数：\n");
    scanf("%d",&n);
    int list[n],list1[n],list2[n],list3[n];
    list[0] = 25;
    Random(list,n);

    for(int i = 0;i < n; i++)
    {
        list1[i] = list[i];
        list2[i] = list[i];
        list3[i] = list[i];
        printf(" %d",list[i]);
    }

    bubbleSort(list1,n);
    printf("\n\n******冒泡排序：\n");
    for(int i = 0;i < n; i++)
    {
        printf(" %d",list1[i]);
    }
    printf("\n冒泡排序比较次数：%d",bubblenumber);


    MergeSort(list2,0,n-1);
    printf("\n\n******归并排序：\n");
    for(int i = 0;i < n; i++)
    {
        printf(" %d",list2[i]);
    }
    printf("\n归并排序比较次数：%d",mergenumber);


    QuickSort(list3,0,n-1);
    printf("\n\n******快速排序：\n");
    for(int i = 0;i < n; i++)
    {
        printf(" %d",list3[i]);
    }
    printf("\n快速排序比较次数：%d",pivotnumber);


    printf("\n*********************************************\n\n");
    printf("\n冒泡排序比较次数：%d",bubblenumber);
    printf("\n归并排序比较次数：%d",mergenumber);
    printf("\n快速排序比较次数：%d",pivotnumber);

    return 0;
}


