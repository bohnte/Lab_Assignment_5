#include <stdio.h>
// A function to implement bubble sort
// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
int i, j,temp,swap;
for (i = 0; i < n-1; i++)
{
swap = 0;
for (j = 0; j < n-i-1; j++)
{
if (arr[j] > arr[j+1])
{//then swap
temp=arr[j];
arr[j]=arr[j+1];
arr[j+1]=temp;
swap++;
}

// Driver program to test above functions
int main(){
int arr[] = {97,16,45,63,13,22,7,58,72};
int n = sizeof(arr)/sizeof(arr[0]);
printf("%d", bubbleSort);
if (swap == 0) break;
return 0;
}