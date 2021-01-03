#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
    char* data;
    int h,freq;
    struct node *left,*right;

}node;

node *Insert(node *,char*);
node *Delete(node *,char*);
int height( node *);
node *RightRotation(node *);
node *LeftRotation(node *);
node *leftright(node *);
node *rightleft(node *);
int BalFactor(node *);

int Max(int a, int b){
    if(a>b)
      return a;
    else
      return b;
}
/*
node * Insert(node *tree,char *data)
{
    printf("entered into: insert");
    int bf;
    if(tree==NULL)
    {
        printf("entered into: first if statement");
        tree=(node*)malloc(sizeof(node));
        tree->data=malloc(sizeof(char*)*strlen(data)+1);
        strcpy(tree->data,data);
        printf("\nentered into: %s",data);
        tree->right=NULL;
        tree->left=NULL;
        tree->freq=1;
        tree->h=1;
        printf("\nentered into: %s",tree->data);
    }
    else if(strcmp(data,tree->data)<0)
      {
        tree->left = Insert(tree->left,data);
        printf("\nentered into: 2"); }
    else if(strcmp(data,tree->data)>0)
      {
        tree->right = Insert(tree->right,data);
        printf("\nentered into: 1"); }

    else if(strcmp(data,tree->data)==0)
      {
        tree->freq++;
        printf("\nentered into: "); }
    tree->h=Max(height(tree->left),height(tree->right)) + 1;
    printf("\nentered into: before bf");
    bf = BalFactor(tree);
    printf("\nentered into: after bf %d",bf);

    if(bf<-1)
      { printf("\nentered into: aaa");
        if(strcmp(data,tree->right->data)>0 )
        {
            printf("\nentered into: a");
            return LeftRotation(tree);

         }
       }
    if(strcmp(data,tree->right->data)<0 && (bf<-1))
        { printf("\nentered into: b");
           return leftright(tree);
          }

    if(strcmp(data,tree->left->data)>0 && (bf>1))
        { printf("\nentered into: c");
          return rightleft(tree);
           }
    if(strcmp(data,tree->left->data)<0 && (bf>1))
        { printf("\nentered into: d");
           return RightRotation(tree);
         }

         printf("\nerri pooka\n");
    return tree;
} */

node* Insert(node *tree,char* data){
    int bf;
    if(tree== NULL){
        tree = (node*)malloc(sizeof(struct node));
        tree->data = malloc(sizeof(char*)*strlen(data)+1);

        strcpy(tree->data, data);
        tree->freq = 1;
        tree->h = 1;
        tree->left = NULL;
        tree->right = NULL;

    }
    else if(strcmp(data, tree->data) < 0){
        tree->left = Insert(tree->left,data);
    }
    else if(strcmp(data, tree->data) > 0){
        tree->right = Insert(tree->right,data );
    }
    else if (strcmp(data,tree->data) == 0){
        tree->freq++;
    }

    tree->h= Max(height(tree->left), height(tree->right)) + 1;

    bf = BalFactor(tree);

    if (bf> 1 && (strcmp(data, tree->left->data) < 0))
        return RightRotation(tree);

    if (bf< -1 && (strcmp(data, tree->right->data) > 0))
        return LeftRotation(tree);

    if (bf > 1 && (strcmp(data, tree->left->data) > 0))
    {
        return rightleft(tree);
    }

    if (bf< -1 && (strcmp(data, tree->right->data) < 0))
    {
        return leftright(tree);
    }
    return tree;
}

node *Delete(node *tree,char *data)
{
    node *p;

    if(tree==NULL)
    {
        return NULL;
    }
    else
        if(strcmp(data,tree->data)>0)
        {
            tree->right=Delete(tree->right,data);
            if(BalFactor(tree)==2)
                {
                  if(BalFactor(tree->left)>=0)
                    tree=RightRotation(tree);
                else
                    tree=leftright(tree);
                }
        }
        else
            if(strcmp(data,tree->data)<0)
            {
                tree->left=Delete(tree->left,data);
                if(BalFactor(tree)==-2)
                  {

                    if(BalFactor(tree->right)<=0)
                        tree=LeftRotation(tree);
                    else
                        tree=rightleft(tree);
                    }
            }
            else
            {
                //data to be deleted is found
                if(tree->right!=NULL)
                {    //delete its inorder succesor
                    p=tree->right;

                    while(p->left!= NULL)
                        p=p->left;

                    strcpy(tree->data,p->data);
                    tree->right=Delete(tree->right,p->data);

                    if(BalFactor(tree)==2)
                        {
                          if(BalFactor(tree->left)>=0)
                            tree=RightRotation(tree);
                        else
                            tree=leftright(tree);
                        }
                }
                else
                    return(tree->left);
            }
    tree->h=height(tree);
    return(tree);
}

int height(node *tree)
{
    if(tree==NULL)
      return 0;
    else
      //return Max(height(tree->left),height(tree->right)) + 1;
      return tree->h;
}


node * LeftRotation(node *tree)
{
    node *x,*y;
    x=tree->right;
    y=x->left;
    x->left=tree;
    tree->right=y;
    x->h=Max(height(x->right),height(x->left))+1;
    tree->h=Max(height(tree->right),height(tree->left))+1;
    return x;
}

node * RightRotation(node *tree)
{
    node *x,*y;
    x=tree->left;
    y=x->right;
    x->right=tree;
    tree->left=y;
    x->h=Max(height(x->right),height(x->left))+1;
    tree->h=Max(height(tree->right),height(tree->left))+1;

    return(y);
}

node * leftright(node *tree)
{
    tree->left=LeftRotation(tree->left);
    tree=RightRotation(tree);

    return(tree);
}

node * rightleft(node *tree)
{
    tree->right=RightRotation(tree->right);
    tree=LeftRotation(tree);
    return(tree);
}

int BalFactor(node *tree)
{
    int bf;
    if(tree==NULL)
      return 0;
    bf=height(tree->left) - height(tree->right);
    return bf;
}
void searchkey(node *tree,char s[])
  {
      if( tree == NULL )
          printf("NULL");
      if(strcmp(s,tree->data))
        {
          printf("value found");
          printf("\n%d",tree->freq);

        }
      else if( strcmp(s,tree->data)<0)
        {
          tree->freq++;
          searchkey(tree->right,s);
        }
      else
          {
            tree->freq++;
            searchkey(tree->left,s);
          }

        //  if(freq>0)
          printf("\nElement found\nElement:%s\tFrequency:%d",s,tree->freq);
          //else
          //printf("not found");
  }

int Size(node *tree)
{ int c=1;
  if(tree!=NULL)
    return 0;
  else
  {
      c+=Size(tree->left);
      c+=Size(tree->right);
    }
    return c;
}
int main()
{
    node *tree=NULL;
    int c,ch;
    char s[10],text[80];
    char *Data=NULL;
    FILE *f;
    do
    {
        printf("\n1)Initialization:\n2)Insert:\n3)Delete:");
        printf("\n4)Size:\n5)Height:\n6)Search\n7)Exit:\n");
        printf("\nEnter Your Choice:");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1:
                  f= fopen("A4_data_f18.txt","r");
                  if(f==NULL)
                    return 1;
                  int count = 0;
                  while(fscanf(f,"%s",text)!=EOF)
                  {
                    tree=Insert(tree,text);
                    printf("\nfile loaded\n");
                    count++;

                  }
                  fclose(f);
                  break;
            case 2: printf("\nEnter element:");
                    scanf("%s",Data);
                    tree=Insert(tree,Data);
                    count++;
                    break;

            case 3: printf("\nEnter a data:");
                    scanf("%s",Data);
                    tree=Delete(tree,Data);
                    count--;
                    break;

            case 4: c = Size(tree);
                    printf("\nSize: %d",c);
                    break;
            case 5: printf("Height of the tree: %d",height(tree));
                    printf("\nTotal count: %d", count);
                    break;
            case 6:
                    printf("\nEnter the element to search: ");
                    scanf("%s",s);
                    searchkey(tree,s);
                    /*if(freq>0)
                    printf("\nElement found\nElement:%s\tFrequency:%d",s,freq);
                    else
                    printf("not found");*/
                    break;
          }
    }while(ch!=7);

    return 0;
}
