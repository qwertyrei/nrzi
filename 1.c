#include <stdio.h>
#include <stdlib.h>

static int i;
static int size;
static int enc_do;
static int dec_do;
FILE *in, *dec, *fopen();

int main(){
	if((in=fopen("input.txt", "r"))==NULL){
		printf("Err!");
		exit(1);
	}
	size = 17;
	int *enc_di=(int*)malloc(size*sizeof(int));
	for(i=0; i<size; i++)
		fscanf(in, "%1d", &enc_di[i]);

	if((dec=fopen("output.txt", "w"))==NULL){
		printf("Err!");
		exit(1);
	}
	fprintf(dec,"(1) Исходный код, считанный из файла input.txt:\t");
	for(i=0;i<size;i++)
		fprintf(dec, "%1.1x", enc_di[i]);
	fprintf(dec,"\n");

	fprintf(dec,"(2) Encode result:\t");
	int *dec_di=(int*)malloc((size+1)*sizeof(int));
	enc_do=1;
	dec_di[0]=enc_do;
	fprintf(dec,"%1.1x", enc_do);
	for(i=0;i<size;i++){
		if(enc_di[i]==0x00)
			enc_do=!enc_do;
		fprintf(dec, "%1.1x", enc_do);
		dec_di[i+1]=enc_do;
	}
	fprintf(dec,"\n");
	fprintf(dec,"(3) Decode result:\t");
	dec_do=1;
	int *end=(int*)malloc((size+2)*sizeof(int));
	end[0]=dec_do;
	end[1]=dec_do;
	fprintf(dec, "%1.1x",dec_do);
	fprintf(dec, "%1.1x",dec_do);
	for(i=0; i<size; i++){
		if((dec_di[i]^dec_di[i+1])==1)
			dec_do=0;
		else
			dec_do=1;
		fprintf(dec, "%1.1x",dec_do);
		end[i+2]=dec_do;
	}
	fprintf(dec,"\n");
	fprintf(dec,"Графики, соответствущие кодам (1)-(3):\n");
	fprintf(dec,"(1):\t");
	for(i=0;i<size;i++){
		if(enc_di[i]==0)
			fprintf(dec, "_");
		else
			fprintf(dec,"-");
	}
	fprintf(dec,"\n");
	fprintf(dec,"(2):\t");
	for(i=0;i<(size+1);i++){
		if(dec_di[i]==0)
			fprintf(dec, "_");
		else
			fprintf(dec,"-");
	}
	fprintf(dec,"\n");
	fprintf(dec,"(3):\t");
	for(i=0;i<(size+2);i++){
		if(end[i]==0)
			fprintf(dec, "_");
		else
			fprintf(dec,"-");
	}
	fclose(in);
	fclose(dec);
}

