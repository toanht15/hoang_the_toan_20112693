#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node
{
	char *s;
	int count; //bien dem so lan xuat hien cua tu
	char *line; //xau luu chi so dong
	struct Node *next;
}node;

char* appendAfterLine(char *s, int i){  //chen so vao xau chi so dong
	char c = (char)(((int)'0')+i);
  	size_t n=strlen(s);
  	if (s[n-1]==c)
  	{
  		return s;
  	}
  	char* s2=malloc(n+1+1+1);
  	strcpy(s2,s);
  	s2[n]=',';
  	s2[n+1]=c;
  	s2[n+2]='\0';
  
  	return s2;
  	free(s2);
}

void insert(node *root,char *s1,int n){ 
	while(root->next!=NULL)
	{
		root=root->next;
	}
	
	root->next=(node*)malloc(sizeof(node));
	root=root->next;
	root->s=s1;
	root->count=1;
	root->line="";
	root->line=appendAfterLine(root->line,n);
	root->next=NULL;
}

void print(node *pointer)
{
        if(pointer==NULL)
        {
                return;
        }
        printf("%s  %d%s\n",pointer->s,pointer->count,pointer->line);
        print(pointer->next);
}

char* appendAfterS(char *s, char c){ //ham ghep xau
  size_t n=strlen(s);
  char* s2=malloc(n+1+1);
  strcpy(s2,s);
  s2[n]=c;
  s2[n+1]='\0';
  
  return s2;
  free(s2);
}



void lower(char *s){ //chuyen chu hoa thanh chu thuong
  int i=0;
  for (i = 0; i < strlen(s); i++)
  {
    if(isupper(s[i]))
      s[i]=tolower(s[i]);
  }
}

int checkInFile(node *root,char *str,int n)
{
	root=root->next;
	while(root!=NULL)
	{
		if (strcmp(root->s,str)==0)
		{
			root->count=root->count+1;
			root->line=appendAfterLine(root->line,n);
			return 1;
		}
		root=root->next;
	}
	return 0;
}

int checkInStopw(node *root,char *str) //kiem tra xau co o trong stopw.txt ko
{
	root=root->next;
	while(root!=NULL)
	{
		if (strcmp(root->s,str)==0)
		{
			return 1;
		}
		root=root->next;
	}
	return 0;
}

node *list_switch( node *l1, node *l2 )
{
    l1->next = l2->next;
    l2->next = l1;
    return l2;
}

node *sort( node *start )
{
  start=start->next;
    if( start == NULL ) return NULL;
    /* First push the larger items down */
    if( start->next !=NULL && strcmp(start->s,start->next->s)>0 )
        start = list_switch( start, start->next );
    /* Always sort from second item on */
    start->next = sort(start->next);
    /* bubble smaller items up */
    if( start->next !=NULL && strcmp(start->s,start->next->s)>0 ) {

        start = list_switch( start, start->next );
        start->next = sort(start->next);
    }
    return start;
}



node* sort1( node *root)
{
  
    root=root->next;
  
  while(root!=NULL){
    if (strcmp(root->s,root->next->s)<0)
    {
      //root=list_switch(root,root->next);
    }
    root=root->next;
    }
  
  return root;
}

int main()
{
	node *start,*temp,*root,*tmp;
        start = (node *)malloc(sizeof(node)); 
        root = (node *)malloc(sizeof(node)); 
        temp = start;
        temp->next = NULL;
        tmp=root;
        tmp->next=NULL;

    char ch, file_name[25];
   FILE *fp,*f;

//Doc file stopw.txt vao con tro root
   	f=fopen("stopw.txt","r");
 	char *p[100];
 	int m=0;
 	p[m]="";
 	while( ( ch = fgetc(f) ) != EOF ){
 		if ((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')) //chi doc ki tu
 		{
   			p[m]=appendAfterS(p[m],ch);
 		}

 	if(ch==32||ch=='\n')
 	{
 		insert(root,p[m],1);
 		++m;
 		p[m]="";
 	}	
 }
 
//xu ly vao luu ket qua vao con tro start
   printf("Enter the name of file you wish to see (vanban.txt):\n");
   gets(file_name);
 
   fp = fopen(file_name,"r"); // read mode
 
   if( fp == NULL )
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
   	char *s[100];
	int i=0;
	s[i]="";
	int n=1;
   while( ( ch = fgetc(fp) ) != EOF ){
 	if ((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
 	{
   		s[i]=appendAfterS(s[i],ch);
 	}

 	if(ch==32||ch=='\n'){
 		lower(s[i]);
 		int check1;
 		check1=checkInStopw(root,s[i]);
 		if (check1==0)
 		{
 			int k;
 		k=checkInFile(start,s[i],n);
 		if (strlen(s[i])!=0&&k==0)
 		{
 			insert(start,s[i],n);
 		}
 		}
 		
 		
 		
 		++i;
 		s[i]="";
 	}
 		if (ch=='\n')  // tai sao them || \r vao thi ket qua bi loi
 		{
 			n=n+1; 		
 		}
 }
 	
  //start=sort(start);
 	print(start); //in ket qua

 	fclose(f);
 	fclose(fp);
	return 0;
}

