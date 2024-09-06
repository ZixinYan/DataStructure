#include<stdio.h>
#include<stdlib.h>
typedef int Element;
typedef struct {
	Element* r;
	int length;
}SqList;
//The average number of inversions in an array of n distinct numbers is n(n - 1)/4.
//-----------------------------Insertion Sorting----------------------------
//O(nlogn)   worst: O(n^2)   best: O(n)
void InsertSort(SqList& L)  // from little to big
{
    int i, j;
    for (i = 2; i <= L.length; i++)
    {
        if (L.r[i] < L.r[i - 1])
        {
            L.r[0] = L.r[i];    //set a flag
            for (j = i - 1; L.r[0] < L.r[j]; --j)
                L.r[j + 1] = L.r[j];  //move right
        }
        L.r[j + 1] = L.r[0]; //find the right position 
    }
}

//-----------------------transposition sorting-------------------------------
//O(n^2)

//Bubble Sort
void BubbleSort(SqList& L) {
    for (int i = 0; i < L.length - 1; ++i) {  // ���ѭ�������������
        bool swapped = false;                   // ��ǰ�˳�ð��ѭ���ı�־λ
        for (int j = 0; j < L.length - 1 - i; ++j) {  // �ڲ�ѭ������Ԫ�صıȽϺͽ���
            if (L.r[j] > L.r[j + 1]) {  // ���ǰһ��Ԫ�رȺ�һ��Ԫ�ش��򽻻�
                int temp = L.r[j];
                L.r[j] = L.r[j + 1];
                L.r[j + 1] = temp;
                swapped = true;  // ���ñ�־λ����ʾ��Ԫ�ؽ���
            }
        }
        if (!swapped) {  // ���û�з�����������ǰ�˳�ѭ��
            break;
        }
    }
}


//------------------------Shell sort-----------------------------------
// O(N^1.25)
void ShellSort(SqList& L) {
    int n = L.length;
    // ѡ��һ����ʼ�ļ���������У�����ʹ�� n/2, n/4, ..., 1 �ķ�ʽ
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // ��ÿһ��������в�������
        for (int i = gap; i < n; ++       i) {
            int temp = L.r[i];
            int j;
            for (j = i; j >= gap && L.r[j - gap] > temp; j -= gap) {
                L.r[j] = L.r[j - gap];
            }
            L.r[j] = temp;
        }
    }
}


//------------------------Quick sort-----------------------------------
//average O(nlogN)    worst(n^2)
int Partition(SqList& L, int low, int high) {
    int pivot = L.r[low];  // ѡ���һ��Ԫ����Ϊ����
    while (low < high) {
        while (low < high && L.r[high] >= pivot) --high;  // ����������С��pivot��Ԫ��
        L.r[low] = L.r[high];  // ��С��pivot��Ԫ���Ƶ����
        while (low < high && L.r[low] <= pivot) ++low;  // ���������Ҵ���pivot��Ԫ��
        L.r[high] = L.r[low];  // ������pivot��Ԫ���Ƶ��ұ�
    }
    L.r[low] = pivot;  // ��pivot�ŵ���ȷλ��
    return low;  // ����pivot��λ��
}

void QuickSort(SqList& L, int low, int high) {
    if (low < high) {
        int pivotIndex = Partition(L, low, high);  // ������������������λ��
        QuickSort(L, low, pivotIndex - 1);  // �ݹ�������벿��
        QuickSort(L, pivotIndex + 1, high);  // �ݹ������Ұ벿��
    }
}


//------------------------Selection Sorting---------------------------------
//O(n^2)
void SelectionSort(SqList& L) {
    for (int i = 0; i < L.length - 1; ++i) {
        int minIndex = i;  // �����i��Ԫ������С��
        for (int j = i + 1; j < L.length; ++j) {
            if (L.r[j] < L.r[minIndex]) {  // �ҵ��ȵ�ǰ�������Сֵ��С��Ԫ��
                minIndex = j;
            }
        }
        if (minIndex != i) {  // ����Ԫ��
            int temp = L.r[i];
            L.r[i] = L.r[minIndex];
            L.r[minIndex] = L.r[i];
        }
    }
}


//-----------------------Heap Sort-------------------------------------------
//O(nlogN)
//1.create a heap use max heap
//2.delete root and output to array


//--------------------------Merge Sort--------------------------------------
//Average O(nlogN)  worst O(n^2)
// 
// �ϲ����������鵽ԭ������
void Merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;  // ��������Ĵ�С
    int n2 = right - mid;  // ��������Ĵ�С

    // ��̬�����ڴ������������
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // �����ݸ��Ƶ�����������
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;  // ��ʼ�������������ͺϲ����������
    // �ϲ����������鵽ԭ������
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {  // �����������Ԫ�ؽ�С�����
            arr[k] = L[i];
            ++i;
        }
        else {  // �����������Ԫ�ؽ�С
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    // ������������ʣ���Ԫ�ظ��Ƶ�ԭ����
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    // ������������ʣ���Ԫ�ظ��Ƶ�ԭ����
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }

    // �ͷŷ�����ڴ�
    free(L);
    free(R);
}

// �ݹ�ؽ��й鲢����
void MergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;  // �����м���������ֹ���
        MergeSort(arr, left, mid);  // �ݹ�������벿��
        MergeSort(arr, mid + 1, right);  // �ݹ������Ұ벿��
        Merge(arr, left, mid, right);  // �ϲ�������
    }
}

//----------------------------------Bucket Sort-------------------------------
//O(n).

//---------------------------------Radix Sort---------------------------------
//���ո�ʮ��λ����С����

//---------------------------------External Sort------------------------------