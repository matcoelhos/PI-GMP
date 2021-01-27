#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>
#include<string.h>
#include<tgmath.h>
#include<gmp.h>

int main(int argc, char * argv[])
{

	mpf_set_default_prec(10*1024*1024);

	int num_iterations = atoi(argv[1]);
	int print_progress = atoi(argv[2]);
	mpf_t sum;
	mpf_t t1, t2, t3, t4, t5, t6, t7, aux, k4, k10, m1;
	mpf_t i;
	
	mpf_init(sum);
	mpf_init(i);
	mpf_init(t1);
	mpf_init(t2);
	mpf_init(t3);
	mpf_init(t4);
	mpf_init(t5);
	mpf_init(t6);
	mpf_init(t7);
	mpf_init(k4);
	mpf_init(k10);
	mpf_init_set_si(m1,-1);
	mpf_init(aux);

	int iter = 0;
	while(iter <= num_iterations)
	{
		mpf_set_si(i,iter);

		mpf_mul_2exp(k4,i,2);
		mpf_mul_ui(k10,i,10);

		mpf_add_ui(aux,k4,1);
		mpf_ui_div(t1,32,aux);
		//t1 = -32/(4*i+1);

		mpf_add_ui(aux,k4,3);
		mpf_ui_div(t2,1,aux);
		//t2 = -1/(4*i+3);

		mpf_add_ui(aux,k10,1);
		mpf_ui_div(t3,256,aux);
		//t3 = 256/(10*i+1);

		mpf_add_ui(aux,k10,3);
		mpf_ui_div(t4,64,aux);
		//t4 = -64/(10*i+3);

		mpf_add_ui(aux,k10,5);
		mpf_ui_div(t5,4,aux);
		//t5 = -4/(10*i+5);

		mpf_add_ui(aux,k10,7);
		mpf_ui_div(t6,4,aux);
		//t6 = -4/(10*i+7);

		mpf_add_ui(aux,k10,9);
		mpf_ui_div(t7,1,aux);
		//t7 = 1/(10*i+9);

		mpf_set_si(aux,0);
		mpf_sub(aux,aux,t1);
		mpf_sub(aux,aux,t2);
		mpf_add(aux,aux,t3);
		mpf_sub(aux,aux,t4);
		mpf_sub(aux,aux,t5);
		mpf_sub(aux,aux,t6);
		mpf_add(aux,aux,t7);
		mpf_div_2exp(aux,aux,10*iter);

		if (iter%2 == 1)
			mpf_mul(aux,aux,m1);
		
		mpf_add(sum,sum,aux);
		//sum += (-1^n)*mult*(t1+t2+t3+t4+t5+t6+t7)
		iter++;
	}
	mpf_div_2exp(sum,sum,6);
	gmp_printf("%.10000000Ff\n", sum);

	mpf_clear(sum);
	mpf_clear(i);
	mpf_clear(t1);
	mpf_clear(t2);
	mpf_clear(t3);
	mpf_clear(t4);
	mpf_clear(t5);
	mpf_clear(t6);
	mpf_clear(t7);
	mpf_clear(k4);
	mpf_clear(k10);
	mpf_clear(aux);
	return 0;
}