//© 2019 Mohammad Julashokri
#include<iostream.h>
#include<string.h>
#include<fstream.h>
#include<conio.h>
#include<malloc.h>
#define max_tm_size 100
#define max_tape_size 400
char ch;
char sm1[4],sm2[4];
char tm[max_tm_size];
char tape[max_tape_size];
void change(char,char *);
//-------------------------------------
typedef struct aa *aa_p;
typedef struct aa {
	int al;
   aa_p link;
   } aa;
aa_p ptr_st = NULL;
aa_p ptr_v = NULL;
void add(aa_p *,int);
//------------------------------------------------------------------------------
int main(){
clrscr();
ifstream fp1("p4.in");
if(!fp1){
	cout<<"can not open file\n";
   getch();
   }
fp1>>tm;
fp1.close();
int ll = strlen(tm);
for(int i=0;i<ll;i++){
	ch = tm[i];
   change(ch,sm1);
   strcat(tape,sm1);
}
//check the turing machine------------------------------------------------------
bool test = true;
char c = tape[0];
int ic = 0;
while(c == '0'){
   ic++;
   c = tape[ic];
   }
int z=0;
char c2;
int lt = strlen(tape);
for(int i=ic;i<lt;i++){
	c = tape[i];
   c2 = tape[i+1];
   if (c == '0')
   	z++;
   if (c=='0' && c2=='0')
   	test = false;
   }
if (tape[lt-1] != '0')
	test = false;
if (z%5 != 0)
	test = false;
//writing p4.out----------------------------------------------------------------
ofstream fp2("p4.out");
if (test) {
char tc;
int cst=0,cv=0,nst=0,nv=0,tcc=0;
for(int i2=ic;i2<lt;i2++){
	tc = tape[i2];
   if (tc == '0')
      	tcc++;
         else {
         if(tcc==0)
            	cst++;
     	   if(tcc==1)
         		cv++;
			if(tcc==2)
         		nst++;
      	if(tcc==3)
         		nv++;
      	}
      if (tcc==5)
         {
         add(&ptr_v,cv);
         add(&ptr_v,nv);
         add(&ptr_st,cst);
         add(&ptr_st,nst);
         cst=0;cv=0;nst=0;nv=0;tcc=0;
         }
}
if(ptr_st){
fp2<<'q'<<ptr_st->al;
ptr_st = ptr_st->link;
for(;ptr_st;ptr_st=ptr_st->link)
 fp2<<",q"<<ptr_st->al;
}
fp2<<"\n";
if(ptr_v){
fp2<<'a'<<ptr_v->al;
ptr_v = ptr_v->link;
for(;ptr_v;ptr_v=ptr_v->link)
 fp2<<",a"<<ptr_v->al;
}
fp2<<"\n";
char co;
int c_st=0,c_v=0,n_st=0,n_v=0,lr=0,cc=0;
for(int i2=ic;i2<lt;i2++){
	co = tape[i2];
   if (co == '0')
      	cc++;
         else {
         if(cc==0)
            	c_st++;
     	   if(cc==1)
         		c_v++;
			if(cc==2)
         		n_st++;
      	if(cc==3)
         		n_v++;
      	if(cc==4)
         		lr++;
         }
      if (cc==5)
         {
			if(lr==1)
			  fp2<<"d(q"<<c_st<<','<<"a"<<c_v<<")=(q"<<n_st<<",a"<<n_v<<",L)\n";
			  else
 			  fp2<<"d(q"<<c_st<<','<<"a"<<c_v<<")=(q"<<n_st<<",a"<<n_v<<",R)\n";
         c_st=0;c_v=0;n_st=0;n_v=0;lr=0;cc=0;
         }
}
} else
	fp2<<"No Turing Machine"<<endl;

fp2.close();
return 0;
}
//------------------------------------------------------------------------------
void change(char a,char *st){
switch (a) {
	case '0' : strcpy(st,"0000");break;
   case '1' : strcpy(st,"0001");break;
   case '2' : strcpy(st,"0010");break;
   case '3' : strcpy(st,"0011");break;
   case '4' : strcpy(st,"0100");break;
   case '5' : strcpy(st,"0101");break;
   case '6' : strcpy(st,"0110");break;
   case '7' : strcpy(st,"0111");break;
   case '8' : strcpy(st,"1000");break;
   case '9' : strcpy(st,"1001");break;
   case 'A' : strcpy(st,"1010");break;
   case 'B' : strcpy(st,"1011");break;
   case 'C' : strcpy(st,"1100");break;
   case 'D' : strcpy(st,"1101");break;
   case 'E' : strcpy(st,"1110");break;
   case 'F' : strcpy(st,"1111");break;
   }
}
//------------------------------------------------------------------------------
void add (aa_p *ptr,int h1)
{
aa_p te = *ptr,tt= *ptr,te2;
bool find = false;
if (*ptr) {
for(;te;te=te->link){
	if((te->al)==h1)
	    	find = true;
   te2 = te;
   }
if (!find){
      tt = (aa_p) malloc(sizeof(aa));
      tt->link = NULL;
      tt->al = h1;
      te2->link = tt;
   	}
}
else{
  *ptr = (aa_p) malloc(sizeof(aa));
  (*ptr)->al = h1;
  (*ptr)->link = NULL;
   	}
}

