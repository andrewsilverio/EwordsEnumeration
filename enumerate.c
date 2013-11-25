#include <stdio.h>
#include <stdlib.h>


long cf[256]; /* I just need a global variable */

char generatorA=0;
void push(char generator, int length){
	static int k=0; static char previous=0;

	if(length==0) return;
	if(generator==previous ) k+=length; else {
		if(previous!=0) {putchar((int) previous);
			if(k>1) printf("%d ", k);}
		previous=generator; k=length; 
	}

}

void callorspit(unsigned char k, long ak, char parity)
{
	int i; long j, p,q, motherp,motherq,fatherp,fatherq;
	char pparity[2]; long parentak[2]; unsigned char parentk[2];   int save=0;
	/* if( ak==-2) {push('B',1); return;};
	if(  ak==0) {push(generatorA,1); return;};
/**********INSERT THE TURBOBOOST CODE HERE***********/
	if((k==0) ){ save=ak>>1;push('B', save+(ak&1));push(0,1);push(generatorA,1);push('B', save); return;};
	if((k==1) &&  ( (cf[0]==0) || ak==0)){ save=ak>>1;push(generatorA, save);push(0,1);push('B',1);push(generatorA, save+(ak&1)) ; return;};

/***************************************************/

        if(k==0) { parentk[0]=1; parentak[0]=0;             } else { parentk[0]=k-1; parentak[0]=cf[parentk[0]];
                if(parentak[0]==1 && (k>1)){ parentk[0]--; parentak[0]=cf[k-2]+1;} }; /*** Change this if TURBO is implemented ***/
        parentk[1]=k; parentak[1]=ak -1;
                if((parentak[1]==1) && (k> 0) ){ parentk[1]--; parentak[1]=cf[k-1]+1;};

        p=parentak[0];q=1;
        for(i=parentk[0]-1;i>=0;i--) { j=p; p=cf[i]*p+q; q=j; }

        motherp=p;motherq=q;
        if(motherq!=0) { for(;;) /* compute gcd */ { j = p%q; if(j==0) { j=q; break;} p = q; q = j; };
        motherp=motherp/j;motherq=motherq/j; }

        p=parentak[1];q=1;
        for(i=parentk[1]-1;i>=0;i--) { j=p; p=cf[i]*p+q; q=j; }

        fatherp=p;fatherq=q;
        for(;;) /* compute gcd */ { j = p%q; if(j==0) { j=q; break;} p = q; q = j; }
        fatherp=fatherp/j;fatherq=fatherq/j;

        pparity[0]=(char) (motherp&motherq&1);
        pparity[1]=(char) (fatherp&fatherq&1);

        i=(int) parity^(motherp*fatherq> fatherp*motherq);

	callorspit(parentk[i],parentak[i],pparity[i]);
	callorspit(parentk[!i],parentak[!i],pparity[!i]);
}

int main(int argc, const char **argv)
{
	int i; long j,  p,q, motherp,motherq,fatherp,fatherq,n,d ;
	char parity; char pparity[2]; long parentak[2]; unsigned char parentk[2];
	unsigned char k; const char *parityword[2]={"even","odd"}, *parentsignature[2]={"mother", "father"};

if(argc<3){printf("need parameters\n"); return 1;};
p=atol(argv[1]); n=p;
q=atol(argv[2]); d=q;
if(q==0){ printf("The word corresponding to infinity is B.\n\n"); return 0;};

   	for(;;) /* compute gcd */ { j = p%q; if(j==0) { j=q; break;} p = q; q = j; }
n=n/j;d=d/j;
 printf("The lowest term is %d/%d .\n", n, d);

generatorA='a' & ~(((n<0)^(d<0))<<5) ;

if(n<0) n=-n;
if(d<0) d=-d;

parity=(n&d)&1;

p=n;q=d;
for(i=0;q!=0;i++){ cf[i]=p/q; j=p;p=q;q=j%q;}; k=i-1; /* extract the continued fraction; written from scrach on paper while attending cuny seminar*/

printf("The continued fraction  is [%d;", cf[0]);
for(i=1;i<k;i++) printf("%d,", cf[i]);
printf("%d]\n", cf[k]);
j=0;
for(i=0;i<=k;i++)j=j+cf[i];
printf("The fairy level is %d.\n", j);
printf("The parity is %s.\n", parityword[parity]);
printf("The k is %d.\n", k);


      if( (k==0) && (cf[k]==0) && (parity==0)) {printf("The primitive word of 0 is a."); return 0;};
/*        if( (k==0) && (ak==0) && (parity==1)) {printf("B"); return;}; */

        if(k==0) { parentk[0]=1; parentak[0]=0;             } else { parentk[0]=k-1; parentak[0]=cf[parentk[0]];
                if(parentak[0]==1 && (k>1)){ parentk[0]--; parentak[0]=cf[k-2]+1;} };
        parentk[1]=k; parentak[1]=cf[k] -1;
                if((parentak[1]==1) && (k>0) ){ parentk[1]--; parentak[1]=cf[k-1]+1;};

        p=parentak[0];q=1;
        for(i=parentk[0]-1;i>=0;i--) { j=p; p=cf[i]*p+q; q=j; }


        motherp=p;motherq=q;
        if(motherq!=0) { for(;;) /* compute gcd */ { j = p%q; if(j==0) { j=q; break;} p = q; q = j; }
        motherp=motherp/j;motherq=motherq/j; };


        p=parentak[1];q=1;
        for(i=parentk[1]-1;i>=0;i--) { j=p; p=cf[i]*p+q; q=j; }

        fatherp=p;fatherq=q;
        for(;;) /* compute gcd */ { j = p%q; if(j==0) { j=q; break;} p = q; q = j; }
        fatherp=fatherp/j;fatherq=fatherq/j;

        pparity[0]=(char) (motherp&motherq&1);
        pparity[1]=(char) (fatherp&fatherq&1);

        i=(int) parity^(motherp*fatherq> fatherp*motherq);

printf("The mother is %d/%d.\n", motherp, motherq);
printf("The father is %d/%d.\n", fatherp, fatherq);
printf("The %s comes before the %s.\n",parentsignature[i],parentsignature[!i]);

/* printf("The mother's parity is %s. Her k is %d. Her ak is %d \n", parityword[pparity[0]], parentk[0], parentak[0]);
printf("The father's parity is %s. His k is %d. His ak is %d \n", parityword[pparity[1]], parentk[1], parentak[1]);

printf("The cf[k] is %d.\n",cf[k]); */


printf("\nThe primitive word is ...\n");



/* Here comes the recursion.... 
callorspit(k, cf[k], parity); */
	 callorspit(parentk[i],parentak[i],pparity[i]);
 	 push(0,1);printf(" TIMES ");
	callorspit(parentk[!i],parentak[!i],pparity[!i]); push(0,1);
printf("\n\nThe simplified word is ...\n\n");
callorspit(k, cf[k], parity); push(0,1);
printf("\n\n\n");
return 0;

}
