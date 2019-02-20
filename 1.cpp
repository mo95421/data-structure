#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
//函数状态码定义
#define TRUE       1
#define FALSE      0
#define OK         1
#define ERROR      0
#define INFEASIBLE -2
typedef int Status;

#define initstackmax 100;
typedef struct bittree {
 char data;
 bittree *left; //左孩子指针
 bittree *right; //右孩子指针
}bittree,*bit; //二叉树类型
struct stack{
 bit *base;//在栈构造之前和销毁之后，base的值为NULL
 int top;//栈顶指针
 int stacksize;//当前已分配的存储空间，以元素为单位
}; //栈类型


//其中函数操作的伪码算法如下:
void initstack(stack &s)
{ //构造一个空栈s
 s.base=new bit[100];
 s.top=-1;
 s.stacksize=initstackmax;
}

void push(stack &s,bit &s1)
{
 //插入元素s1为新的栈顶元素
 s.top++;
 s.base[s.top]=s1;
 }

char gettop(stack &s)
{
//用s返回栈顶元素
  return s.base[s.top]->data;
}

bit pop(stack &s)
{
//删除是栈顶元素，并用s返回其值
   s.top--;
   return s.base[s.top+1];
}

char compa(char a,char b)
{ 
//按优先级的高低顺序输出运算符
  char pri[6][7]={
   ' ','|','&','~','(',')','#',
   '|','>','<','<','<','>','>',
   '&','>','>','<','<','>','>',
   '~','>','>','>','<','>','>',
   '(','<','<','<','<','=',' ',
   '#','<','<','<','<',' ','=' //第一次进栈时进行比对
};
int i,j;
 for(i=0;i<6;i++){
 	if(pri[i][0]==a)
   break;
  for(int j=0;j<7;j++)
   if(pri[0][j]==b)
    break;
 }
  
   return pri[i][j];
}

bit creattree(char *p,stack &vari,stack &symbol)
{  
  //构造二叉树 
  initstack(vari);
  initstack(symbol);
  bit m,n;
  bit exam;
 exam=new bittree;
 exam->data='#';
 push(symbol,exam);
 while(*p!='#'||(gettop(symbol)!='#'))//第一次生成树时，*P！=#而(gettop()->data=='#')以后则相反
 { 
  if((int(*p)>=65)&&(int(*p)<=90))//是变量
        {
           exam=new bittree;
     exam->data=*p;
     exam->left=NULL;
           exam->right=NULL;
     push(vari,exam);
     p++;
  }
  else
  {
   switch(compa(gettop(symbol),*p)){
   case'<':exam=new bittree;
   exam->data=*p;
   exam->left=NULL;
   exam->right=NULL;
            push(symbol,exam);
   p++;
   break;
   case'=':exam=pop(symbol);
        
     p++;
    break;
   case'>':exam=pop(symbol);
        n=pop(vari);
     exam->left=n;
     exam->right=NULL;
     if(exam->data!='~')
     {
      m=pop(vari);
      exam->right=m;
     }
push(vari,exam);
     break;
   }//switch
}//else
}//while
 bit temp=pop(symbol);
 delete temp;
 return exam;
}

int getvalue(bit root,int num[])
{  
//根据变量的取值组合并利用逻辑表达式的性质对树进行求值 
if((root->data>=65)&&(root->data<=90))
     return num[root->data-65];
 else{
  switch(root->data){
  case'|':return getvalue(root->left,num)||getvalue(root->right,num);
  case'&':return getvalue(root->left,num)&&getvalue(root->right,num);
  case'~':return !getvalue(root->left,num);
  }
 }
}

void user(bit root,int m,char b[])
{  
//若用户对表达式变元取定一组值，程序就求出并显示逻辑表达式的值
int a[30];int n;
   for(int k=0;k<=m;k++)
   {
     printf("请输入n的值\n");
     scanf("%d",&n);
    a[b[k]-65]=n;
   }
   if(getvalue(root,a))
	   printf("True");
   else
	    printf("False");   
}

void judge(bit root,char bo[],int nu)
{
//重言式的判别
   int sample[30]; char bl[20],t;int m=0,lzq,value,count=0,tu=0,fa=0,sat=0;
   for(int k=0;k<nu;k++)
    if(bo[k]>=65&&bo[k]<=90)
    {
   int mark=0;
   for(int j=0;j<m;j++)
    if(bl[j]==bo[k]){
     mark=1;break;
    }
    if(mark==0){
     bl[m]=bo[k];
     m++;
    }
    }   
    int numall=(int)pow(2,m);
   m--;
   for(int i=0;i<numall;i++)
   {   lzq=m;
    for(int j=0;j<m+1;j++)
    {
     sample[bl[lzq]-65]=(i>>j)%2;
     lzq--;
    }
       value=getvalue(root,sample);
       if(value)
    {
     tu++;
     if(fa>0){
             printf("satisfactible");
             sat=1;
break;
     }
     if(tu==numall){
      printf("Ture forever\n"); 
	}
    }
    else
    {   fa++;
     if(tu>0){
     printf("satisfactible\n");
sat=1;
break;
     }
     else {
     
      if(fa==numall)
		    printf("False forever\n"); 
	  }
    }
   }  
     
  if(sat==1) {
   printf("请给变量赋值,c代表继续，e代表停止");
   scanf("%c",&t);
while(t){
    if(t=='c')
    {
            for(i=0;i<=m;i++)
           printf("%c",&bl[i]);
             user(root,m,bl);
    }
    else
     break;
   }
   }
 } 
//3．主函数
int main(int argc, char* argv[])
{

	char str[300],str1[100],*p;int n,len=0,j;int k=0,m,count=0;
    stack vari,symbol;
    bit root;
printf("请输入0或1，0--终止程序  1--继续程序\n");
scanf("%d",&m);
while(m)
 {
    count++;
  if(m==1)
  {
     if(count>1) delete []vari.base;
    k=0;
       printf(" 请输入表达式(变量以大写形式输入)");         
      gets(str);
     len=strlen(str);
    for(j=0;j<len;j++)
     if(str[j]!=' ') 
  {
   str1[k]=str[j];
      k++;
  }
  str1[k]='#';
  len=strlen(str1);
      p=str1;
         root=creattree(p,vari,symbol);
         judge(root,str1,len);
  }
  else
  {
   if(count>1) delete []vari.base;
   break;
  }
 }
   return 0;
}
