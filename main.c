#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_matrix (int m, int n, int mat[m][n]){
  for (int i=0;i<m;i++){
    for (int j=0;j<n;j++){
      printf ("%d\t",mat[i][j]);
    }
    printf ("\n");
  }
  printf ("\n");
  
}

void print_array (int n, int arr[]){
  for (int i=0;i<n;i++){
    printf("%d\t", arr[i]);
  }
  printf ("\n");
}

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
  if (proc_min==proc_max){
    zero_percentage=proc_min;
  }
  else {
    zero_percentage=proc_min+rand()%percentage_diff;
  }
  
  int tmp_arr[n*m];
  fill_with_zeroes(tmp_arr,n*m,zero_percentage);
  shuffle_array(tmp_arr,n*m);

 for (int i=0;i<m;i++){
    for (int j=0;j<n;j++){
      mat[i][j]=tmp_arr[i*n+j];
    }
  }

}

int calculate_non_zero_elements ( int m, int n, int mat[m][n]){
  int sum=0;
  for (int i=0;i<m;i++){
    for (int j=0;j<n;j++){
      if (mat[i][j]!=0){
        sum++;
      }

    }
  }
  return sum;
} 

void transformToCSR (int m, int n, int mat[m][n], int A[], int IA[], int JA[]){
  int index=0;
  for (int i=0;i<m;i++){
    for (int j=0;j<n;j++){
      if (mat[i][j]!=0){
        A[index]=mat[i][j];
        IA[index]=i;
        JA[index]=j;
        index++;
      }
    }
  }
}

void sum(int m, int n, int A[m][n], int B[m][n], int C[m][n]){
  for (int i=0;i<m;i++){
    for (int j=0;j<n;j++){
      C[i][j] = A[i][j] + B[i][j];
    }
  }
}

void product(int m, int n, int p, int A[m][n], int B[n][p], int C[m][p]){
  for (int i=0;i<m;i++){
    for (int j=0;j<p;j++){
      int sum=0;
      for (int brojac=0;brojac<n;brojac++){
        sum+=A[i][brojac]*B[brojac][j];
      } 
      C[i][j]=sum;

    }
  }
}

int main(){
  int mat1[3][4];
  int mat2[4][5];
  int rez_mat[3][5];
  create(3,4,mat1,70,80);
  create(4,5,mat2,20,50);
  print_matrix(3,4,mat1);
  print_matrix(4,5,mat2);
  product(3,4,5,mat1,mat2,rez_mat);
  print_matrix(3,5,rez_mat);
  
  




}