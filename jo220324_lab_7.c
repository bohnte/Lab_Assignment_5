#include <stdio.h>
// A function to implement bubble sort
// A function to implement bubble sort
void bubbleSort(int arr[], int n){
int i, j,temp,swap[n];
for (i = 0; i < n; i++)
    swap[i] = 0;
for(i = 0; i < n-1; i++){
    for (j = 0; j < n-i-1; j++){
        if (arr[j] > arr[j+1]){//then swap
            temp=arr[j];
            arr[j]=arr[j+1];
            arr[j+1]=temp;
            swap[j]++;
            }
        }
    }   
    for(i = 0; i < n; i++)
        printf("%d", swap[i]);
}
// Driver program to test above functions
int main(){
int arr[] = {97,16,45,63,13,22,7,58,72};
int n = sizeof(arr)/sizeof(arr[0]);
bubbleSort(arr, n);
return 0;
}