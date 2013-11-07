#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
void copyarray(char [],char [],int ,int);
struct s_element
{

struct s_element *leftchild ;
struct s_element *rightchild;
struct s_element *parent;
struct s_element *suffixlink ;
char  ar[];//variable length member
};
typedef struct s_element node;
node *root;
void buildtree(node **,char [],int,int);
void printelements(node *);
void prunetree(node *);
node *matcharray(node *,char []);
bool checksimilarity(node *,node *);
void copytoarray(char [],char []);
int q;//q-gram size
int main()
{
//node *root;
root =NULL;
printf("%u\n",root);
int size;
printf("enter the sequence text size");
scanf("%d",&size);
char text[size+1];
printf("enter the sequence");
scanf("%s",text);
printf("enter the q-gram size");
scanf("%d",&q);

int i;
for(i=0; i<(size-q+1);i++)
{
//printf("this is from for loop");
buildtree(&root,text,i,i+q-1);
}

printf("%u\n",root);
printelements(root);
printf("\npruning the tree\n\n");
prunetree(root);
printf("\n");
printelements(root);
}

void buildtree(node **x,char a[],int s,int e)
{
int i;
printf("this is from build tree\n");
if((*x) == NULL)
{
printf("from if's loop\n");
(*x)= (node *)malloc(sizeof(node));
(*x)->leftchild= NULL;
(*x)->rightchild= NULL;
(*x)->parent = NULL;
(*x)->suffixlink=NULL;
}
node *p;
p = (*x);
//printf("%u\n",p);
i= s;
while(i<=e)
{
	if(a[i]=='0')
	{
//         printf("character is 0\n");
		if(p->leftchild == NULL)
{

p->leftchild = (node *)malloc(sizeof(node));//
p->leftchild->parent = p;
p = p->leftchild;
copyarray(p->ar,a,i,s);
printf("%s,%u,%d\n",p->ar,p,strlen(p->ar));
i++;
}  

else
{
p = p->leftchild;
i++;
}

 	}
	else
	{
	printf("charatcer is 1\n");
        if(p->rightchild ==NULL)
	{
        p->rightchild = (node *)malloc(sizeof(node));
	p->rightchild->parent = p;
	p = p->rightchild;
	 copyarray(p->ar,a,i,s);

printf("%s,%u,%d\n",p->ar,p,strlen(p->ar));
        i++;
}
         else
	 {

p = p->rightchild;
i++;
	 }

	 }

}
return; 

}

void copyarray(char arr1[],char arr2[],int s1,int e1)
{
int i; 
//i = s1;
for(i= 0;i<=s1-e1;i++)
{
arr1[i]= arr2[e1+i];
}

arr1[i] = '\0';
//terminating null character
}


void printelements(node *x)
{
if(x == NULL)
{
return;
}else
{
printf("%s::%u,%d\n",x->ar,x,strlen(x->ar));
printelements(x->leftchild);

printelements(x->rightchild);

}
}
void prunetree(node *x)
{
//printf("entered prunetree\n");
char arr3[q];
node *y;

if(strlen(x->ar)==0)
{
printf("length is zero\n");
}
if(strlen(x->ar)==1)
{
printf("length is 1\n");
if(checksimilarity(x,x->parent)==true)
{
//printf("This was called\n");
x->leftchild=NULL;
x->rightchild = NULL;
return;
}

}
if(strlen(x->ar)==q)
{
return;
}
if(strlen(x->ar)>1)
{
printf("lenght is %d\n",strlen(x->ar));
copytoarray(arr3,x->ar);
printf("%s\n",arr3);
y = matcharray(root,arr3);//match for the suffix
printf(":::%u",y);
if(y!=NULL)
{
printf("returned NULL%s\n",y->ar);
if(checksimilarity(x,y)==true)
{
printf("similarity was found");
x->leftchild =NULL;
x->rightchild = NULL;
return;
}
}
}
if(x->leftchild!=NULL)
{
prunetree(x->leftchild);
}
if(x->rightchild!=NULL)
{
prunetree(x->rightchild);
}

}

void copytoarray(char ay1[],char ay2[])
{
//printf("copy to array was called\n");
int i;
for(i=1;i<strlen(ay2);i++)
{
ay1[i-1]= ay2[i];
}
ay1[i-1]= '\0';

}

node *matcharray(node *x,char ar1[])
{
//printf("match array was called");
int i;
node *p;
p = x;
while(i<strlen(ar1))
{
if(ar1[i]=='0')
{
if(p->leftchild!=NULL)
{
p = p->leftchild;
i++;
}
else
{
return NULL;
}
}
else
{
if(ar1[i]=='1')
{

if(p->rightchild!=NULL)
{
p= p->rightchild;
i++;
}
else
{
return NULL;
}

}

}
}

return p;

}



bool checksimilarity(node *p,node *q1)
{
//printf("enterd into checksimilarity\n");
if(p->leftchild==NULL)
{
  if(q1->leftchild!=NULL)
   	{
         if(strlen(p->ar)==q)
	 { 
	 printf("\nThis ar==q was called\n");
	 return true;
	 }
	 else
	 {
	return false;
	}
	}

  else { if(p->rightchild==NULL)
  		{
			if(q1->rightchild!=NULL)
			{
			return false;
			}

			else
			{
			return true;
			}	
		}    

	else { if(q1->rightchild==NULL)
	
		{
		return false;
		}

	     else
	     {
	     printf("entered 1\n");
	     return checksimilarity(p->rightchild,q1->rightchild);
	     }

	}

}
}
else { if(q1->leftchild==NULL)
	{
	return false;
	}

     else { if (p->rightchild == NULL)
           {
		if(q1->rightchild == NULL)
		{ printf("entered 2\n");

 		return checksimilarity(p->leftchild,q1->leftchild);
                
		}

		else
		{
		return false;
		}


	}
	   else 
	   {
		if(q1->rightchild == NULL)
		{
		return false;
		}

		else
		{ printf("entered 3\n");

		return ((checksimilarity(p->leftchild,q1->leftchild))&&(checksimilarity(p->rightchild,q1->rightchild)));
		}

	   }	

	}
	}



}
