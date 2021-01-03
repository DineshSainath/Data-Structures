// Name: Dinesh sainath Koti reddy
// ID# 1025287
// CIS2520 Assignment 3

#include<stdio.h>
#include<stdlib.h>

// heap structure
struct s{
int key;
int position;
};

void MaxHeapify();       //function declaration for max heap
struct s* create_max_heap(struct s a[], int n)
 {
  int hsize = n;
  int x;
  for (x = n/2; x >= 0; x--) { 
    MaxHeapify(a, x, hsize);
 }
return a;
 }

//max heapify the struct array
void MaxHeapify(struct s a[], int i, int hsize)
{
  struct s t;
  int max, left, right;
  left = (2*i+1);
  right = ((2*i)+2);

  if (left >= hsize)
   return;
  else {
  if (left < (hsize) && a[left].key > a[i].key)
   max = left; 
  else
   max = i;
  if (right < (hsize) && a[right].key > a[max].key)
   max = right;
  if (max != i) { 
   t = a[i];
   a[i] = a[max];
   a[max] = t;
  MaxHeapify(a,max,hsize);
  }
 }
}
int main()
{

FILE *f;
f = fopen("f.dat", "r");

int a[20][10];
int i,j;

 for (i = 0; i < 20; i++)
  {
 for(j=0;j<10;j++){
 fscanf(f,"%d", &a[i][j]);      //getting the input in 2D matrix form
 }
}

struct s k[20];               //array of objects
for (i = 0; i < 20; i++)
{
 k[i].position=i;
 int sum=0;
 for(j=0;j<3;j++){
sum=sum+a[i][j];
}
k[i].key=sum;
}
create_max_heap(k,5);
for(i=0;i<20;i++)
{
for(j=0;j<10;j++)
{
printf("%d ",a[k[i].position][j]);     //printing after max heap
}
printf("\n");
}
return 0;
}
