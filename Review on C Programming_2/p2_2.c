#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct student{
	char *name;
	int literature;
	int math;
	int science;
}Student;	//make structure student 

int main(int argc, char* argv[]){
	Student *s;			//make structure Student s.
	int buf[100];
	int n=0,i=0;
	FILE *fp1 = fopen(argv[1],"r");			// Read input.txt

	if(fp1==NULL){
		puts("파일오픈 실패!!\n");
		return -1;						//if input.txt is NULL, print this text.
	}
	
	fscanf(fp1,"%d",&n);
	s = (struct student*)malloc(sizeof(struct student)*n);		//make dynamic allocation.
	while(1){
	if(i==n)
		break;
	else
		fscanf(fp1,"%s %d %d %d", buf, &(s+i)->literature, &(s+i)->math, &(s+i)->science);
	(s+i)->name = (char*)malloc(sizeof(char)*30);			//make dynamic allocation name[30].
	strcpy((s+i)->name,buf);			//input buf's value to name.
	i++;
	}

	fclose(fp1);

	FILE *fp2 = fopen(argv[2],"w");

	if(fp2 ==NULL){
		puts("파일오픈 실패!!\n");
		return -1;			//if output.txt's value is NULL, print this text. 
	}

	fprintf(fp2,"   Name");
	for(i=0 ; i<n ; i++)
		fprintf(fp2," %10s",(s+i)->name);
		for(i=0;i<2;i++)
		fprintf(fp2,"\n");
	fprintf(fp2,"Literature");
	for(i=0 ; i<n ; i++)
		fprintf(fp2,"  %5d    ",(s+i)->literature);
		for(i=0;i<2;i++)
		fprintf(fp2,"\n");

	fprintf(fp2,"   Math");
	for(i=0 ; i<n ; i++)
		fprintf(fp2,"%10d ",(s+i)->math);
		for(i=0;i<2;i++)
		fprintf(fp2,"\n");
	fprintf(fp2," Science");
	for(i=0 ; i<n ; i++)
		fprintf(fp2,"%9d  ",(s+i)->science);
	fclose(fp2);
	for(i=0; i<n;i++)	
		free((s+i)->name);				//free dynamic allocation name.
	free(s);		//free dynamic allocation s
	return 0;


}


