#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap (int arr[],int index1, int index2){
  int tmp;
  tmp=arr[index1];
  arr[index1]=arr[index2];
  arr[index2]=tmp;

}
void shuffle_array (int arr[],int n){
  int index1, index2;
  for (int i=0; i<100;i++){
    index1=rand()%n;
    index2=rand ()%n;
    swap(arr,index1,index2);

  }
}

void fill_with_zeroes (int arr[], int n, int zero_percentage){
  int zero_num;
  zero_num=round(n*zero_percentage/100);
  for (int i=0;i<n;i++){
    if (i<zero_num){
      arr[i]=0;
    }
    else {
      arr[i]=1;
    }
  }

}

void create (int m, int n, int mat[m][n], int proc_min, int proc_max){
  int zero_percentage;
  int percentage_diff;
  percentage_diff=proc_max-proc_min;
  zero_percentage=proc_min+rand()%percentage_diff;
  int tmp_arr[n*m];
  fill_with_zeroes(tmp_arr,n*m,zero_percentage);
  shuffle_array(tmp_arr,n*m);

  for (int i=0;i<m;i++){
    for (int j=0;j<n;j++){
      mat[i][j]=tmp_arr[i*n+j];
      printf ("%d\t",mat[i][j]);
    }
    printf ("\n");
  }

}

int main(){
  int mat[3][4];
  create(3,4,mat, 45 , 55);
}