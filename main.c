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

int first_element(int row1, int column1, int row2, int column2){
  /*
    If element1 is the first element - return -1
    If element2 is the first element - return +1
    If both of the elements are on the same position - return 0
  */
  if (row1 < row2){
    return -1;
  }
  if (row2 < row1){
    return +1;
  } 
  // Elements are in the same row
  if (column1 < column2){
    return -1;
  }
  if (column2 < column1){
    return +1;
  }
  // Elements have the same position in the matrix
  return 0;

}

void spars_sum(int n1,int A1[], int IA1[], int JA1[], int n2, int A2[], int IA2[], int JA2[],int A[], int IA[], int JA[]){
  int index1 = 0;
  int index2 = 0;
  int index = 0;
  
  while (index1 < n1 && index2 < n2){
    int result=first_element(IA1[index1], JA1[index1], IA2[index2] , JA2[index2]);
    if (result == -1){
      A[index] = A1[index1];
      IA[index] = IA1[index1];
      JA[index] = JA1[index1];
      index++;
      index1++;
      continue;
    }
    if (result == +1){
      A[index] = A2[index2];
      IA[index] = IA2[index2];
      JA[index] = JA2[index2];
      index++;
      index2++;
      continue;
    }
    // result == 0
    A[index] = A1[index1] + A2[index2];
    IA[index] = IA1[index1];
    JA[index] = JA1[index1];
    index++;
    index1++;
    index2++;
    
  }
  while (index1<n1){
    A[index] = A1[index1];
    IA[index] = IA1[index1];
    JA[index] = JA1[index1];
    index++;
    index1++;
  }
   while (index2<n2){
    A[index] = A2[index2];
    IA[index] = IA2[index2];
    JA[index] = JA2[index2];
    index++;
    index2++;
  }



}

void transpose_sparse_matrix (int n, int A[], int IA[], int JA[]){
  int result;
  int tmpA, tmpI, tmpJ;
  //print_array(5,A);
  //print_array(5,IA);
  //print_array(5,JA);
  //printf ("\n");
  for(int i=0; i<n; i++){
    int index_min=i;
    for(int j=i; j<n; j++){
      if(-1 == first_element(JA[j], IA[j],JA[index_min], IA[index_min] )) {
        index_min=j;
      }
    }
    tmpA=A[i];
    tmpI=IA[i];
    tmpJ=JA[i];

      
    //printf ("%d ",A[index_min]);
    A[i]=A[index_min];
    //printf ("%d, ",A[i]);

    //printf("%d ",IA[index_min]);
    IA[i]=IA[index_min];
    //printf("%d, ",IA[i]);

    //printf ("%d ",JA[index_min]);
    JA[i]=JA[index_min];
    //printf ("%d      ",JA[i]); 
    //printf ("%d\n",index_min);
    //printf("----------------------\n");
  
    

    A[index_min]=tmpA;
    IA[index_min]=tmpI;
    JA[index_min]=tmpJ;

    tmpA=IA[i];
    IA[i]=JA[i];
    JA[i]=tmpA;

    //print_array(5,A);
    //print_array(5,IA);
    //print_array(5,JA);
    //printf ("\n");

    
  }

}

void sparse_multiply (int n1,int A1[], int IA1[], int JA1[], int n2, int A2[], int IA2[], int JA2[],int A[], int IA[], int JA[]){
  transpose_sparse_matrix(n2,A2,IA2,JA2);
  int index=0;
  int not_initialized=1;
  for(int i=0;i<n1;i++){
    for(int j=0;j<n2;j++){
      if(JA1[i] == JA2[j]){
       if (not_initialized == 1){
        A[index] = A1[i] * A2[j];
        IA[index] = IA1[i];
        JA[index] = IA2[j]; 
        not_initialized = 0;
        continue;
       } 
      else {
      
      if(IA[index] == IA1[i] && JA[index] == IA2[j]){
          A[index] += A1[i] * A2[j];
      }
      else {
        index++;
          A[index] = A1[i] * A2[j];
        IA[index] = IA1[i];
        JA[index] = IA2[j]; 
      }
        
        

       }
      }
    }
  }
}

int main(){
  int A1[3] = {1, 1, 1};
  int IA1[3] = {0, 0, 1};
  int JA1[3] = {0, 1, 0};

  int A2[4] = {1, 1, 1, 1};
  int IA2[4] = {0, 0, 1, 1};
  int JA2[4] = {0, 1, 1, 2};

  int A[5] = {0, 0, 0, 0, 0};
  int IA[5] = {0, 0, 0, 0, 0};
  int JA[5] = {0, 0, 0, 0, 0};

  sparse_multiply(3,A1, IA1, JA1, 4, A2, IA2, JA2, A, IA, JA);
 
  printf ("\n");
  print_array(5,A);
  print_array(5,IA);
  print_array(5,JA);


 




}