#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "domain.h"

int main(int argc, char **argv)
{
	int i;
	int t=0;
	int x,y,ind;
	int N[2];
	int err;
	char cmd[BUFSIZ];
	domain *Dom;
	Dom = new domain();
	cart_vector orig;
	orig.Vx = 0;
	orig.Vy = 0;
	orig.Vz = 0;
	cart_vector global_size;
	global_size.Vx = 400;
	global_size.Vy = 400;
	global_size.Vz = 1;
	int size = 400;
	Dom->set_params(orig,size,2,global_size,0,1);
	Dom->allocate_memory();
	Dom->initialize_domain();

	printf("time : %d\n",-1);
	sprintf(cmd,"mkdir ./data/output_%d",0);
	system(cmd);

	FILE *fp=NULL;
	char filename[BUFSIZ];
	sprintf(filename,"./data/output_%d/region_%d",t,0);
	fp = fopen(filename,"w");
	Dom->output_domain_avg(t,fp,5);
	if(fp != NULL)
		fclose(fp);

	//****Build communication requests from the domains
	//****Communication calls using assembled requests


	printf("***************** BEGIN TIME ********************\n");
	for(t=1;t<1000;t++)
	{

		Dom->calcprePhi();
		Dom->calcdPdt();
		Dom->calcpreC();
		Dom->calcdCdt();
		Dom->step();
		if(t%100 ==0)
		{
			printf("time : %d\n",t);
			sprintf(cmd,"mkdir ./data/output_%d",t);
			system(cmd);
			sprintf(filename,"./data/output_%d/region_%d",t,0);
			fp = fopen(filename,"w");
			Dom->output_domain_avg(t,fp,5);
			if(fp != NULL)
				fclose(fp);
		}
	}

	printf("Finished run\n");

	return 0;
}
