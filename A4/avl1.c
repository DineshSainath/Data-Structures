/*
Name:Dinesh Sainath Koti Reddy
Id# 1025287
CIS*2520 Assignment #4
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node {                   // structre for avl node
	char* data;
	int freq,h;
	struct node *left, *right;
}node;

int Max(int a, int b)                // to find the larger number
{
    if(b>a)
      return b;
    else
      return a;
}

void countall(node *tree,int *Size,int *count)   //counts the number of nodes &
{                                                // total count
    if (tree != NULL)
    {
        *count=*count+tree->freq;
        *Size+=1;
        countall(tree->left,Size,count);
        countall(tree->right,Size,count);
      }

}

int h(node* tree )                      // to find the height of avl tree
{
    if( tree== NULL )
        return 0;
    else
        return tree->h;
}

void Freqmax(node *tree,int freq){   //finds the keys whose frequency is greater
    if (tree!= NULL)                 // than or equal to the number entered
    {   Freqmax(tree->left,freq);
        if (tree->freq>=freq)
          printf("key = %s\tFrequency = %d\n",tree->data,tree->freq);
        Freqmax(tree->right,freq);
    }
}

int BalF(node *tree)                 // to find the balance factor
  {
    if(tree== NULL)
        return 0;
    int bf=h(tree->left)-h(tree->right);
    return bf;
  }

node* FindString(char* data,node* tree)      //to searh and find the key
  {
      if(tree==NULL)
          return NULL;
      if(strcmp(data,tree->data)<0)
          return FindString(data,tree->left);
      else if(strcmp(data,tree->data)>0)
          return FindString(data, tree->right);

      return tree;
  }

node * LeftRotation(node *tree)               // avl left rotation of tree
  {
      node*x=tree->right;
      node*y=x->left;
      x->left=tree;
      tree->right=y;
      tree->h=Max(h(tree->left),h(tree->right)) +1;
      x->h=Max(h(x->left),h(x->right)) +1;

      return x;
  }


node * RightRotation(node *tree)            // avl right rotation of tree
  {
    node *x=tree->left;
    node *y=x->right;
    x->right=tree;
    tree->left=y;
    tree->h=Max(h(tree->left),h(tree->right)) +1;
    x->h=Max(h(x->left),h(x->right)) +1;
    return x;
  }

node* leftright(node *tree)                 // avl left-right rotation of tree
  {
    tree->right=RightRotation(tree->right);
    return LeftRotation(tree);
  }

node* rightleft(node *tree)                // avl right-left rotation of tree
  {
    tree->left=LeftRotation(tree->left);
    return RightRotation(tree);
  }

node* Insert(node*tree,char* data)        // to insert values into tree
{
    int bf;
    if(tree == NULL)
    {
        tree = (node*)malloc(sizeof(node));
        tree->data = malloc(sizeof(char*)*strlen(data)+1);
        strcpy(tree->data, data);
        tree->left = NULL;
        tree->right = NULL;
        tree->freq = 1;
        tree->h = 1;
      }
    else if (strcmp(data,tree->data)==0)
        tree->freq++;                     // counts the freq as it enters into tree
    else if(strcmp(data, tree->data)>0)
        tree->right = Insert(tree->right,data);
    else if(strcmp(data, tree->data)<0)
          tree->left = Insert(tree->left,data);

    bf= BalF(tree);

    if(bf<-1 && (strcmp(data,tree->right->data)<0))
        return leftright(tree);

    if(bf<-1 && (strcmp(data,tree->right->data)>0))
        return LeftRotation(tree);

    if(bf>1 && (strcmp(data,tree->left->data)>0))
        return rightleft(tree);

    if(bf>1 && (strcmp(data,tree->left->data)<0))
        return RightRotation(tree);

    tree->h = Max(h(tree->right),h(tree->left)) + 1;
    return tree;
}


node* Delete(char* data,node *tree)             // to delete from tree
{
    node *p;
    int bf;
    if(tree == NULL)
        return NULL;
    else if(strcmp(data, tree->data)>0)
        tree->right = Delete(data,tree->right );
    else if(strcmp(data, tree->data)<0)
          tree->left = Delete(data,tree->left );
    else if (strcmp(data,tree->data)==0)
    {
        if(tree->freq > 1)
            tree->freq--;
        else if (tree->freq==1)
        {
            if(tree->right!=NULL)
            {
                p=tree->right;
                while(p->left!= NULL)
                    p=p->left;
                tree->data=p->data;
                tree->right=Delete(p->data, tree->right);
            }
            else
                return(tree->left);
        }
    }
    tree->h=Max(h(tree->right),h(tree->left)) + 1;
    bf = BalF(tree);

    if(bf<-1 && (strcmp(data, tree->right->data)<0))
        return leftright(tree);

    if(bf<-1 && (strcmp(data, tree->right->data)>0))
        return LeftRotation(tree);

    if(bf>1 && (strcmp(data, tree->left->data)>0))
        return rightleft(tree);

    if(bf>1 && (strcmp(data, tree->left->data)<0))
          return RightRotation(tree);

    return tree;
}

int main()
{
  FILE *f;                 // to read the textfile
  int c=0,freq=0;
  node *tree = NULL,*Enode = NULL;
  char data[20],File[80];

  do
  {
    printf("\n1.Initialization\n2.Find\n3.Insert\n");
    printf("4.Remove\n5.Check Height and Size\n");
    printf("6.Find All (above a given frequency)\n7.Exit\navl/> ");
    scanf("%d",&c);                      // input choice
    int count=0,size=0,h1;
    switch(c)
    {
        case 1:                            // intialzation
        f = fopen("A4_data_f18.txt","r");
        if (f == NULL)
        {
            printf("\nFile not found\n");
            exit(1);
        }
        else
        {
            while(fscanf(f,"%s",File)==1)  // reading the textfile
                tree=Insert(tree,File);
            printf("\nFile is loaded\n");
        }
        fclose(f);
        break;

        case 2:                         // finding the string
        printf("Search element: ");
        scanf("%s",data);
        Enode=FindString(data,tree);
        if (Enode==NULL)
            printf("No_such_data\n");
        else
            printf("Element: %s\tfrequency: %d\n",Enode->data,Enode->freq);
        break;

        case 3:                         // Insert element into tree
          printf("Insert Element: ");
          scanf("%s", data);
          tree = Insert(tree,data);
          Enode = FindString(data, tree);
          printf("Element: %s\tFrequency: %d\n",Enode->data,Enode->freq);
          break;

        case 4:                       //Delete element from tree
          printf("Remove Element: ");
          scanf("%s", data);
          Enode=FindString(data, tree);
          if (Enode==NULL)
            printf("No_such_data\n");
          else
          {
            tree= Delete(data, tree);
            Enode=FindString(data, tree);
            if(Enode == NULL)
              printf("data: %s, frequency: 0\n", data);
            else
              printf("data: %s, frequency: %d\n", Enode->data, Enode->freq);
          }
          break;

        case 5:                  // to print height, size and total count
          h1=h(tree);
          countall(tree,&size,&count);
          printf("\nHeight: %d\tSize: %d\tTotal count: %d\n",h1,size,count);
          break;

        case 6:           // to print elements with frequency more than input
          printf("frequency: ");
          scanf("%d", &freq);
          Freqmax(tree, freq);
          break;

        case 7:
          exit(1);                       //exit
          break;

        default:
          printf("\nInvalid choice\nChoose between 1-7\n");
          break;
      }

    } while(c!=7);

    return 0;
}
