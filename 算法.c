//排序算法
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//函数声明
//冒泡排序
void bubble_sort(int* a,int len);
//选择排序
void select_sort(int* a,int len);
//插入排序
void insert_sort(int* a,int len);
//希尔排序
void shell_sort(int* a,int len);
//归并排序
void mergeSort(int* a,int l,int r);//递归拆开
void hebing(int* a,int l,int m,int r);//合并
//快速排序
void quick_sort(int* a,int len);
void quickSort(int* a,int l,int r);

//打印
void show(int* a,int len,bool isAfter);

int main(){
    int arr[10] = {98,64,0,22,34,55,12,9,3,-22};

    show(arr,10,false);
    //bubble_sort(arr,10);//冒泡排序
    //select_sort(arr,10);//选择排序
    //insert_sort(arr,10);//插入排序
    //shell_sort(arr,10);//希尔排序
    //hebing(arr,0,4,9);//归并排序
    quickSort(arr,0,9);//快速排序
    show(arr,10,true);A

    return 0;
}
//选择排序
void select_sort(int* a,int len){
    int minIdx;
    for(int i=0;i<len-1;i++){//选择len-1次
        //从下标i到len-1范围内找最小的元素 和 a[i]交换
        minIdx = i;//先假设范围内第一个最小
        for(int j=i;j<len;j++){//从下标i到len-1范围内找最小的元素
            minIdx =  ((a[minIdx]<a[j]) ?minIdx:j);
        }
        //a[minIdx]和 a[i]交换
        if(a[i]>a[minIdx]){//if不写也没事
            int t = a[i];
            a[i] = a[minIdx];
            a[minIdx] = t;
        }

        show(a,len,false);
    }
    
}
//冒泡排序
void bubble_sort(int* a,int len){
    for(int j=0;j<len-1;j++){
        for(int i=0;i<len-1-j;i++){
            if(a[i]>a[i+1]){
                int t = a[i];
                a[i] = a[i+1];
                a[i+1] = t;
            }
        }
        show(a,len,false);
    }
    
}

//插入排序
void insert_sort(int* a,int len){
    //插入len-1次
    for(int i=1;i<len;i++){
        //每次插入的数据是   a[i];

        //临时存储待插数据
        int temp = a[i];
        int j;
        for(j=i-1;j>=0 && a[j]>=temp;j--){
           a[j+1] = a[j];//往后覆盖 
        }

        //待插数据覆盖到 停止位置后一个位置
        a[j+1] = temp;

        show(a,10,false);
    }
}

//希尔排序
void shell_sort(int* a,int len){
    //步长
    int step = (len>>1);//int step = len/2;

    while(step){//while(step!=0)

        //组内作插入排序
         for(int i=step;i<len;i++){
            //每次插入的数据是   a[i];

            //临时存储待插数据
            int temp = a[i];
            int j;
            for(j=i-step;j>=0 && a[j]>=temp;j-=step){
                a[j+step] = a[j];//往后覆盖 
            }

            //待插数据覆盖到 停止位置后一个位置
            a[j+step] = temp;
        }
        show(a,10,false);
        step>>=1;//step = step / 2;
    }
}

//归并排序
void mergeSort(int* a,int l,int r){//递归拆开
    //if(l>=r) return;
    if(l<r){
        int left = l;
        int mid = l + (r-l)/2;
        int right = r;

        mergeSort(a,l,mid);
        mergeSort(a,mid+1,r);
        hebing(a,l,mid,r);
        show(a,10,false);
    }
}
void hebing(int* a,int l,int m,int r){//合并
    //1. 来个临时数组
    int* p = malloc(sizeof(int)*(r-l+1));
    //2. 循环放完一个
    int left = l;
    int right = m+1;
    int k=0;
    while(left<=m && right <=r){
        while(left<=m && a[left]<a[right]) p[k++]=a[left++];
        while(right<=r && a[right]<a[left]) p[k++]=a[right++];
    }
    //3. 剩下的也放到临时数组中
    while(left<=m)  p[k++]=a[left++];
    while(right<=r) p[k++]=a[right++];
    //4. 临时数组覆盖回来
    memcpy(a+l,p,sizeof(int)*(r-l+1));
    //5. 释放
    free(p);
}
void merge_sort(int* a,int len){
    mergeSort(a,0,len-1);
}

//快速排序
void quickSort(int* a,int l,int r){
    if(l>=r) return;//递归结束 不然死递归
    int left = l;
    int right = r;

    //先假设一个中间值
    int mid = left;

    //临时存储中间值
    int temp = a[mid];
    while(left<right){
        while(left<right && a[right]>temp) right--;
        a[left] = a[right];
        while(left<right && a[left]<temp) left++;
        a[right] = a[left];
    }
    //中间值覆盖回来
    a[left] = temp;

    show(a,10,false);
    //左边
    quickSort(a,l,left-1);
    //右边
    quickSort(a,left+1,r);
}
void quick_sort(int* a,int len){
    quickSort(a,0,len-1);
}

//打印
void show(int* a,int len,bool isAfter){
    if(isAfter) printf("after  sort:");
    else        printf("before sort:");
    for(int i=0;i<len;i++)
        printf("%2d ",a[i]);
    printf("\n");
}
