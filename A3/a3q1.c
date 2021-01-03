// Name: Dinesh Sainath Koti Reddy
// ID# 1025287
// CIS*2520 Assignment 3
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

char s[20];
int TOP=-1;       // Global variable

void PUSH(char element)                          // PUSH for stack 
{
    s[++TOP]=element;
}

char POP()                                    // POP for stack
{
    return(s[TOP--]);
}
 
int pr(char element)
{
    switch(element)
    {
    case '#': return 0;
    case '(': return 1;
    case '+':
    case '-': return 2;
    case '*':
    case '/': return 3;
    }
    return 0;
}

typedef struct node                                // binary tree
{
        char data;
        struct node *left;
        struct node *right;
}node;

char postfix[20];
int top = -1;
node *arr[20];
int r(char inputchar)
{                            // to check if its an operator
    if (inputchar == '+' || inputchar == '-' || inputchar == '*' || inputchar == '/')
        return (-1);
    else if (inputchar >= 'a' || inputchar <= 'z')
        return (1);
    else if (inputchar >= 'A' || inputchar <= 'Z')
        return (1);
    else
        return (-99); 
}


void push(node *tree)                       // pushing elements into the tree
{
    top++;
    arr[top] = tree;
}

node *pop()                                 // popping elements from the tree
{
    top--;
    return (arr[top + 1]);
}
 
void create_expr_tree(char *suffix)          // creating the expression tree
{
    char symbols;
    node *newl, *ptr1, *ptr2;
    int flag;                               // if flag=-1 then operator else operand
    symbols= suffix[0]; 
    for (int i = 1; symbols != '\0'; i++)
    { 
        flag = r(symbols);                  //check operator or operand
        if (flag == 1)
        {
            newl = malloc(sizeof(node));
            newl->data = symbols;
            newl->left = NULL;
            newl->right = NULL;
            push(newl);
        }
        else
        { 
            ptr1 = pop();
            ptr2 = pop();
            newl = malloc(sizeof(node));
            newl->data = symbols;
            newl->left = ptr2;
            newl->right = ptr1;
            push(newl);
        }
        symbols = suffix[i];
    }
}
 
void PREorder(node *tree)
{
    if (tree != NULL)
    {
        printf("%c",tree->data);
        PREorder(tree->left);
        PREorder(tree->right);
    }
}
 
void INorder(node *tree)
{
    if (tree != NULL)
    {
        INorder(tree->left);
        printf("%c",tree->data);
        INorder(tree->right);
    }
}
 
void POSTorder(node *tree)
{
    if (tree != NULL)
    {
        POSTorder(tree->left);
        POSTorder(tree->right);
        printf("%c",tree->data);
    }
}

int calculate(char * e)
{
    int n1,n2,n3,num;
    while(*e != '\0')
        {
            if(isdigit(*e))
            {
                num = *e - 48;
                PUSH(num);
            }
            else
            {
                n1 = POP();
                n2 = POP();
                switch(*e)
                {
                                case '+':
                                {
                                        n3 = n1 + n2;
                    break;
                                }
                                case '-':
                                {
                                        n3 = n2 - n1;
                                        break;
                                }
                                case '*':
                                {
                                        n3 = n1 * n2;
                                        break;
                                }
                                case '/':
                                {
                                        n3 = n2 / n1;
                                        break;
                                }
                }
                        PUSH(n3);
            }
                e++;
}  return n3;
}
void DispTree(node *n)
{
	if(n==NULL)
		return;
	printf("%c",n->data);
	if(n->left!=NULL)
		printf("[L:%c]",n->left->data);
	if(n->right!=NULL)
		printf("[R:%c]",n->right->data);
	printf("\n");
	DispTree(n->left);
	DispTree(n->right);
}

int main()
{
    char infix[50],POSTFIX[50],ch,element,*ec;
    int j=0,k=0;
    LOOP: printf("\nEnter the expression: ");
    scanf("%s",infix);
     PUSH('#');
    while( (ch=infix[j++]) != '\0')
    {
        if( ch == '(') PUSH(ch);
        else
            if(isalnum(ch)) POSTFIX[k++]=ch;
            else
                if( ch == ')')
                {
                    while( s[TOP] != '(')
                        POSTFIX[k++]=POP();
                    element=POP(); 
                }
                else
                {       
                    while( pr(s[TOP]) >= pr(ch) )
                        POSTFIX[k++]=POP();
                    PUSH(ch);
                }
    }
    while( s[TOP] != '#')     /* Pop until stack is empty to store in a variable */
        POSTFIX[k++]=POP();
    POSTFIX[k]='\0';
    ec= POSTFIX;

    create_expr_tree(POSTFIX);

    printf("\n1.Display\n2.Preorder\n3.Inorder\n4.Postorder\n5.Update\n6.Calculate\n7.Exit\nenter choice:");
    int choice,result=element;
    scanf("%d",&choice);
    switch(choice)
    {
        case 1: printf("\n");
		DispTree(arr[0]);
        break;

        case 2:
        printf( "\nPre-Order Traversal:  ");
        PREorder(arr[0]); 
        printf("\n");
	break;

        case 3:
        printf("\nIn-Order Traversal:   ");
        INorder(arr[0]);
	printf("\n");
        break;

        case 4:
        printf( "\nPost-Order Traversal: ");
        POSTorder(arr[0]);
	printf("\n");
	break;
 
        case 5:
        goto LOOP;
        break;

        case 6:
        result = calculate(ec);
        printf("\ncalculated result = %d", result);
        break;

        case 7:
        exit(0);

    }

    return 0;
}
