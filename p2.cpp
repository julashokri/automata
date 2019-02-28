//© 2019 Mohammad Julashokri
//Mohammad Julashokri St_No : 8250017
#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<malloc.h>
#include<fstream.h>
#include<stdlib.h>
#define max_stack_size 100
#define max_expr_size 100
typedef enum {lparen,rparen,plus,star,dot,eos,operand}precedence;
precedence stack[max_stack_size];
char expr[max_expr_size];
char pos[max_expr_size];
static int isp[] = {0,19,11,13,12,0};
static int icp[] = {20,19,11,13,12,0};
//-------------------------------------
typedef struct element *element_p;
typedef struct element {
	element_p end;
   char c1,c2;
   element_p n1,n2;
   int num;
   int check;
   } element ;
typedef struct pstack *stack_pointer;
typedef struct pstack {
	element item;
   stack_pointer link;
   }pstack;
stack_pointer ptop = NULL;
int s_n = 0;
int sta_s,sta_f;
//-------------------------------------
typedef struct alpha *alpha_p;
typedef struct alpha {
	char al;
   alpha_p link;
   } alpha;
alpha_p ptr_al = NULL;
void ad_al(alpha_p *,char);
//-------------------------------------
void add(int *,precedence);
precedence del(int *);
precedence get_token(char *,int *);
char print_token(precedence);
void padd(stack_pointer *,element);
element pdel(stack_pointer *);
void postfix(void);
void get_node(element *,int *);
void fstar(element,int *,int *);
void funion(element,element,int *,int *);
void fconc(element,element,int *,int *);
void ff(char,int *,int *);
bool check_p(element *);
int alaki[100];
bool alaki_p(int,int [],int *);
int ala=0;
//------------------------------------------------------------------------------
int main(){
clrscr();
ifstream fp1("p2.in");
if(!fp1){
	cout<<"can not open file\n";
   getch();
   }
fp1>>expr;
int ll = strlen(expr);
expr[ll] = ' ';
fp1.close();
postfix();//pos is postfix of re
ll = strlen(pos);
pos[ll] = ' ';
element aa,op1,op2;
int p = 0;
int sta_n = -1;
char ch = pos[p];
element s,f,oo1,oo2;
while (ch != ' '){
if (ch=='*') {
   op1 = pdel(&ptop);
   fstar(op1,&sta_s,&sta_f);
   sta_n += 2;
   }
if (ch == '.') {
      op1 = pdel(&ptop);
      op2 = pdel(&ptop);
      fconc(op1,op2,&sta_s,&sta_f);
      }
if (ch == '+') {
      	op1 = pdel(&ptop);
         op2 = pdel(&ptop);
         funion(op1,op2,&sta_s,&sta_f);
         sta_n += 2;
         }
if((ch!='.')&&(ch!='+')&&(ch!='*')){
            ff(ch,&sta_s,&sta_f);
         	sta_n += 2;
            ad_al(&ptr_al,ch);
    		}
p++;
ch = pos[p];
}
ofstream fp2("p2.out");
if(!fp1){
	cout<<"can not open file\n";
   getch();
   }
if(ptr_al){
fp2<<ptr_al->al;
ptr_al = ptr_al->link;
for(;ptr_al;ptr_al=ptr_al->link)
 fp2<<','<<ptr_al->al;
}
fp2<<"\n"<<"q0";
for(int i=1;i<=sta_n;i++)
	fp2<<",q"<<i;
fp2<<"\nq";
fp2<<sta_s<<"\n";
fp2<<'q'<<sta_f<<"\n";
aa = pdel(&ptop);
element_p lp = &aa;
element ee ;
ee.check = 101;
padd(&ptop,ee);
bool pcheck = false;
while(lp->check!= 101){
if(lp->n1)
  if(check_p(lp->n1))
		padd(&ptop,*(lp->n1));
if(lp->n2)
	if(check_p(lp->n2))
   	padd(&ptop,*(lp->n2));
if(alaki_p(lp->num,alaki,&ala)){
   if (lp->n1)
   	if (lp->n2)
      	if (lp->c1 == lp->c2){
         	fp2<<"d(q"<<lp->num<<','<<lp->c1<<")={q"<<((lp->n1)->num)
            	<<",q"<<((lp->n2)->num)<<"}\n";
            pcheck = true;
            }
if (!pcheck){
   if (lp->n1){
      fp2<<"d(q"<<lp->num<<','<<lp->c1<<")={q"<<((lp->n1)->num)<<"}\n";
   }
  if (lp->n2){
   	fp2<<"d(q"<<lp->num<<','<<lp->c2<<")={q"<<((lp->n2)->num)<<"}\n";
   }
  }
}//for each node
op1 = pdel(&ptop);
lp = &op1;
pcheck = false;
}
fp2.close();
return 0;
}
//------------------------------------------------------------------------------
void add(int *top,precedence item)
{
if (*top >= max_stack_size-1) {
	cout<<"the stack is full\n";
   getch();
   return;
   }
   stack[++*top] = item;
}
precedence del(int *top)
{
if (*top == -1){
   cout<<"the stack is empty\n";
   getch();
	return eos;
   }
return stack[(*top)--];
}
precedence get_token(char *symbol,int *n)
{
*symbol = expr[(*n)++];
switch (*symbol) {
	case '(' : return lparen;
   case ')' : return rparen;
   case '+' : return plus;
   case '*' : return star;
   case '.' : return dot;
   case ' ' : return eos;
   default  : return operand;
   }
}
char print_token(precedence element)
{
switch (element) {
	case plus : return '+';
   case star : return '*';
   case dot  : return '.';
   }
}
void postfix(void)
{
char symbol;
precedence token;
int n = 0;
int top = 0;
int ii = 0;
stack[0] = eos;
for(token = 
get_token(&symbol,&n);token!=eos;token=get_token(&symbol,&n)){
	if(token == operand)
   	pos[ii++] = symbol;
   else if (token == rparen){
   	while(stack[top] != lparen)
      	pos[ii++]=print_token(del(&top));
      del(&top);
   }
   else {
   	while(isp[stack[top]] >= icp[token])
      	pos[ii++] = print_token(del(&top));
      add(&top,token);
   }
}
while((token=del(&top)) != eos)
	pos[ii++] = print_token(token);
cout<<"\n";
}
void padd(stack_pointer *ptop,element item)
{
stack_pointer temp = (stack_pointer) malloc(sizeof(pstack));
temp->item = item;
temp->link = *ptop;
*ptop = temp;
}
element pdel(stack_pointer *ptop){
stack_pointer temp = *ptop;
element item;
if(!temp){
	cout<<"the stack is empty \n";
   getch();
   }
item = temp->item;
*ptop = temp->link;
free(temp);
return item;
}
void get_node(element *oo,int *sn)
{
oo->c1 = '\0';
oo->c2 = '\0';
oo->n1 = NULL;
oo->n2 = NULL;
oo->end = NULL;
oo->num = (*sn)++;
oo->check = -1;
}
void fconc(element operand1,element operand2,int *sta_s,int *sta_f){
element_p o1 = (element_p) malloc(sizeof(element));
element_p o2 = (element_p) malloc(sizeof(element));
*o1 = operand1;
*o2 = operand2;
(o1->end)->c1 = 'L';
(o1->end)->n1 = o2;
*sta_s = o1->num;
*sta_f = (o2->end)->num;
padd(&ptop,*o1);
}
void fstar(element operand1,int *sta_s,int *sta_f){
element_p o = (element_p) malloc(sizeof(element));
element_p s = (element_p) malloc(sizeof(element));
element_p f = (element_p) malloc(sizeof(element));
get_node(&(*s),&s_n);
get_node(&(*f),&s_n);
*o = operand1;
s->end = f;
s->c1 = 'L';
s->n1 = o;
s->c2 = 'L';
s->n2 = f;
f->c2 = 'L';
f->n2 = s;
(o->end)->c1 = 'L';
(o->end)->n1 = f;
*sta_s = s->num;
*sta_f = f->num;
padd(&ptop,*s);
}
void funion(element operand1,element operand2,int *sta_s,int *sta_f){
element_p op1 = (element_p) malloc(sizeof(element));
element_p op2 = (element_p) malloc(sizeof(element));
element_p s = (element_p) malloc(sizeof(element));
element_p f = (element_p) malloc(sizeof(element));
get_node(&(*s),&s_n);
get_node(&(*f),&s_n);
*op1 = operand1;
*op2 = operand2;
s->end = f;
s->c1 = 'L';
s->n1 = op1;
s->c2 = 'L';
s->n2 = op2;
(op1->end)->c1 = 'L';
(op1->end)->n1 = f;
(op2->end)->c1 = 'L';
(op2->end)->n1 = f;
*sta_s = s->num;
*sta_f = f->num;
padd(&ptop,*s);
}
void ff(char ch,int *sta_s,int *sta_f){
element_p s = (element_p) malloc(sizeof(element));
element_p f = (element_p) malloc(sizeof(element));
get_node(&(*s),&s_n);
get_node(&(*f),&s_n);
s->end = f;
s->c1 = ch;
s->n1 = f;
*sta_s = s->num;
*sta_f = f->num;
padd(&ptop,*s);
}
void ad_al (alpha_p *ptr_al,char ch1)
{
alpha_p te = *ptr_al,tt= *ptr_al,te2;
bool find = false;
if (*ptr_al) {
for(;te;te=te->link){
	if((te->al)==ch1)
	    	find = true;
   te2 = te;
   }
if (!find){
      tt = (alpha_p) malloc(sizeof(alpha));
      tt->link = NULL;
      tt->al = ch1;
      te2->link = tt;
   	}
}
else{
  *ptr_al = (alpha_p) malloc(sizeof(alpha));
  (*ptr_al)->al = ch1;
  (*ptr_al)->link = NULL;
   	}
}
bool check_p(element *opr){
bool qq=false;
if(opr->check == -1)
	{
   opr->check = 1;
   qq = true;
   }
return qq;
}
bool alaki_p(int n,int aa[],int *alaki_n  )
{
bool f = false;
bool ff = true;
for(int t=0;t<*alaki_n;t++)
	if (aa[t]==n)
      ff=false;
if (ff){
	f=true;
   aa[(*alaki_n)++]=n;
   }
return f;
}

