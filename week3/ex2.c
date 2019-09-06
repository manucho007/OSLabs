#include <stdio.h>
#include <stdlib.h>

void bubble_sort (int arr[], int arr_size);
void print (int arr[], int arr_size);

int main()
{
    //int arr[5] = {7,8,2,4,9};
    int n, i;
    printf("\n Enter the size of the array");
    scanf("%d",&n);
    int arr_size=n;
    int arr[n];
    printf("\n Enter the array elements: \n");
    for(i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    bubble_sort(arr, arr_size);
    print(arr, arr_size);
    return 0;
}
void bubble_sort(int arr[], int arr_size){
    int i;
    int j;
    for( i=0; i<arr_size; i++){
        for(j = 0; j<arr_size-1; j++){
            if(arr[j]>arr[j+1]){
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }

}
void print(int arr[], int arr_size){
    int i;
    for(i = 0; i<arr_size; i++){
        printf("%d,", arr[i]);
    }

}