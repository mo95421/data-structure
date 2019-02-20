#include<stdio.h>
#include<stdlib.h>

typedef struct{
	int coef;
	int expn;
}PolyTerm;

typedef struct PolyNode{
	PolyTerm data;
	struct PolyNode *next;
}PolyNode, *PolyLink;

void AddPoly(PolyTerm *A, int n, PolyTerm *B, int m, PolyLink &C)
{
	int i, j;
	PolyLink p, tc;

	i = j = 0;
	C = tc = (PolyLink)malloc(sizeof(PolyNode));
	while(i<n && j<m){
		if(A[i].expn < B[j].expn){
			p = (PolyLink)malloc(sizeof(PolyNode));
			p->data.coef = A[i].coef;
			p->data.expn = A[i].expn;
			tc->next = p;
			tc = p;
			i++;
		}
		else if(A[i].expn > B[j].expn){
			p = (PolyLink)malloc(sizeof(PolyNode));
			p->data.coef = B[j].coef;
			p->data.expn = B[j].expn;
			tc->next = p;
			tc = p;
			j++;
		}
		else{
			if(A[i].coef + B[j].coef != 0.0){
				p = (PolyLink)malloc(sizeof(PolyNode));
				p->data.coef = A[i].coef + B[j].coef;
				p->data.expn = B[j].expn;
				tc->next = p;
				tc = p;
			}
			i++;
			j++;
		}
	}
	while(i<n){
		p = (PolyLink)malloc(sizeof(PolyNode));
		p->data.coef = A[i].coef;
		p->data.expn = A[i].expn;
		tc->next = p;
		tc = p;
		i++;
	}
	while(j<m){
		p = (PolyLink)malloc(sizeof(PolyNode));
		p->data.coef = B[j].coef;
		p->data.expn = B[j].expn;
		tc->next = p;
		tc = p;
		j++;
	}
	tc->next = NULL;
}

void PrintPoly(PolyLink P)    
{
	PolyLink q;

	q=P->next; 
	if(q == NULL){
		printf("0");  
		return;
	}
	while(q){
		if(q->data.coef>1 || q->data.coef<-1)
			printf("%d", q->data.coef);
		if(q->data.expn==0 && (q->data.coef==1 || q->data.coef==-1))
			printf("%d", q->data.coef);
		else if(q->data.expn!=0 && q->data.coef==-1)
			printf("-");

		if(q->data.expn==1)
			printf("x");
		else if(q->data.expn>1)
			printf("x^%d", q->data.expn);

		if(q->next && (q->next->data.coef>0))
			printf("+");
		q=q->next;  
	}
   
}   

void main()
{
	PolyTerm *A;
	PolyTerm *B;
	PolyLink C,p;

	int n,m;
	scanf("%d %d",&n,&m);
	A = (PolyTerm *)malloc(n*sizeof(PolyTerm));
	B = (PolyTerm *)malloc(m*sizeof(PolyTerm));

	for(int i=0; i<n; i++)
		scanf("%d %d",&A[i].coef, &A[i].expn);
	for(int i=0; i<m; i++)
		scanf("%d %d",&B[i].coef, &B[i].expn);

	AddPoly(A, n, B, m, C);
	PrintPoly(C); 
	
	free(A);
	free(B);
	p = C;
	while(C){
		C = C->next;
		free(p);
		p = C;
	}
}