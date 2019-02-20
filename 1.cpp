#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
//����״̬�붨��
#define TRUE       1
#define FALSE      0
#define OK         1
#define ERROR      0
#define INFEASIBLE -2
typedef int Status;

#define initstackmax 100;
typedef struct bittree {
 char data;
 bittree *left; //����ָ��
 bittree *right; //�Һ���ָ��
}bittree,*bit; //����������
struct stack{
 bit *base;//��ջ����֮ǰ������֮��base��ֵΪNULL
 int top;//ջ��ָ��
 int stacksize;//��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
}; //ջ����


//���к���������α���㷨����:
void initstack(stack &s)
{ //����һ����ջs
 s.base=new bit[100];
 s.top=-1;
 s.stacksize=initstackmax;
}

void push(stack &s,bit &s1)
{
 //����Ԫ��s1Ϊ�µ�ջ��Ԫ��
 s.top++;
 s.base[s.top]=s1;
 }

char gettop(stack &s)
{
//��s����ջ��Ԫ��
  return s.base[s.top]->data;
}

bit pop(stack &s)
{
//ɾ����ջ��Ԫ�أ�����s������ֵ
   s.top--;
   return s.base[s.top+1];
}

char compa(char a,char b)
{ 
//�����ȼ��ĸߵ�˳����������
  char pri[6][7]={
   ' ','|','&','~','(',')','#',
   '|','>','<','<','<','>','>',
   '&','>','>','<','<','>','>',
   '~','>','>','>','<','>','>',
   '(','<','<','<','<','=',' ',
   '#','<','<','<','<',' ','=' //��һ�ν�ջʱ���бȶ�
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
  //��������� 
  initstack(vari);
  initstack(symbol);
  bit m,n;
  bit exam;
 exam=new bittree;
 exam->data='#';
 push(symbol,exam);
 while(*p!='#'||(gettop(symbol)!='#'))//��һ��������ʱ��*P��=#��(gettop()->data=='#')�Ժ����෴
 { 
  if((int(*p)>=65)&&(int(*p)<=90))//�Ǳ���
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
//���ݱ�����ȡֵ��ϲ������߼����ʽ�����ʶ���������ֵ 
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
//���û��Ա��ʽ��Ԫȡ��һ��ֵ��������������ʾ�߼����ʽ��ֵ
int a[30];int n;
   for(int k=0;k<=m;k++)
   {
     printf("������n��ֵ\n");
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
//����ʽ���б�
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
   printf("���������ֵ,c���������e����ֹͣ");
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
//3��������
int main(int argc, char* argv[])
{

	char str[300],str1[100],*p;int n,len=0,j;int k=0,m,count=0;
    stack vari,symbol;
    bit root;
printf("������0��1��0--��ֹ����  1--��������\n");
scanf("%d",&m);
while(m)
 {
    count++;
  if(m==1)
  {
     if(count>1) delete []vari.base;
    k=0;
       printf(" ��������ʽ(�����Դ�д��ʽ����)");         
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
