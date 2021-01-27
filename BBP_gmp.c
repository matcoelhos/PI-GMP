#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>
#include<string.h>
#include<tgmath.h>
#include<gmp.h>

int main(int argc, char * argv[])
{

	mpf_set_default_prec(8000000);

	int num_iterations = atoi(argv[1]);
	int print_progress = atoi(argv[2]);
	mpf_t sum;
	mpf_t t1, t2, t3, t4, aux, k8;
	mpf_t i;
	
	mpf_init(sum);
	mpf_init(i);
	mpf_init(t1);
	mpf_init(t2);
	mpf_init(t3);
	mpf_init(t4);
	mpf_init(k8);
	mpf_init(aux);

	int iter = 0;
	while(iter < num_iterations)
	{
		mpf_set_si(i,iter);

		mpf_mul_2exp(k8,i,3);

		mpf_add_ui(aux,k8,1);
		mpf_ui_div(t1,4,aux);
		//t1 = 4.0/(8.0*i+1.0);

		mpf_add_ui(aux,k8,4);
		mpf_ui_div(t2,2,aux);
		//t2 = -2.0/(8.0*i+4.0);

		mpf_add_ui(aux,k8,5);
		mpf_ui_div(t3,1,aux);
		//t3 = -1.0/(8.0*i+5.0);

		mpf_add_ui(aux,k8,6);
		mpf_ui_div(t4,1,aux);
		//t4 = -1.0/(8.0*i+6.0);

		mpf_sub(aux,t1,t2);
		mpf_sub(aux,aux,t3);
		mpf_sub(aux,aux,t4);
		mpf_div_2exp(aux,aux,4*iter);

		mpf_add(sum,sum,aux);
		//sum += mult*(t1+t2+t3+t4);

		if (print_progress)
		{
			gmp_printf("%Ff\t%Ff\t%Ff\t%Ff\t%Ff\n",t1,t2,t3,t4,k8);
			gmp_printf("iter %Ff, pi = %Ff \n\n",i,sum);
		}
		
		iter++;
	}
	gmp_printf("%.10000000Ff\n", sum);

	mpf_clear(sum);
	mpf_clear(i);
	mpf_clear(t1);
	mpf_clear(t2);
	mpf_clear(t3);
	mpf_clear(t4);
	mpf_clear(k8);
	mpf_clear(aux);
	return 0;
}