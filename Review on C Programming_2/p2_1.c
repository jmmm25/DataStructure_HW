#include <stdio.h>
#include <stdlib.h>
void swap(char *a, char *b);	//make swap function
void perm(char *list, int i, int n, FILE* fp){	//make perm function
	int j;
	if(i == n){
		for(j = 0; j <= n; j++){
			if(j == 0)
				fputc('{', fp);	//if j's value is 0, print '[' to fp
			fputc(list[j], fp);	//print list in fp.

			if(j != n){
				fputs(", ", fp);
			}
		}
		fputc('}', fp);	//print '}' in fp.
		fputc('\n', fp);
	}
	else{
		for(j=i; j<=n; j++){
			swap(list+i, list+j);
			perm(list, i+1, n, fp);
			swap(list+i, list+j);
		}
	}
}

int main(int argc, char* argv[]){

	FILE* fp1, *fp2;
	char list[100];
	int num = 0;
	char ch = '\0';
	
	fp1 = fopen(argv[1], "rt");		//Read input.txt(argv[1]).

	while((ch = fgetc(fp1)) != '}'){
		if(ch >= 'a' && ch <= 'z'){
			list[num] = ch;
			num++;
		}
}
	fp2 = fopen(argv[2], "wt");	//write output.txt(argv[1] File i/o)
	perm(list, 0, num-1, fp2);	//call perm function.
	fclose(fp1);
	fclose(fp2);	//close fp1, fp2.

	return 0;
}
void swap(char *a, char *b){	// make swap function.
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

