#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NUM_HW 6
#define NUM_EXAM 2
#define MAX_ENROLL 5

typedef char* string;
typedef struct {
	string name;// char*)=> string name; dynamic allocation
	int hw[NUM_HW]; //hw[6]
	int exams[NUM_EXAM]; //exams[2]
	double hwAvg;
	double examAvg;
}studentT;

typedef struct {
	studentT students[MAX_ENROLL]; //students[5]
	int numEnrolled; //the number students
}courseT;


courseT co;

int main(int argc, char* argv[]) 
{
	int i = 0, j;
	FILE *fp1 = fopen(argv[1], "r");
	if (fp1 == NULL) {
		//puts("파일 오픈 실패!!");
		return -1;
	}
	else {
		fscanf(fp1, "%d", &co.numEnrolled);
		while (1) {
			if (i == co.numEnrolled)
				break;
			else {
				// input name not allowed 30
				co.students[i].name = (string)malloc(sizeof(char) * 30);
				fscanf(fp1, "%s", co.students[i].name);
				for (j = 0; j < NUM_HW; j++)
					fscanf(fp1, "%d", &co.students[i].hw[j]);
				//fscanf(fp1, "%d %d %d %d %d %d", &co.students[i].hw[0], &co.students[i].hw[1], &co.students[i].hw[2], &co.students[i].hw[3], &co.students[i].hw[4], &co.students[i].hw[5]);
				fscanf(fp1, "%d %d", &co.students[i].exams[0], &co.students[i].exams[1]);
				i++;
			}
		}
	}
	FILE *fp2 = fopen(argv[2], "w");
	double sum1 = 0;
	double sum2 = 0;
	double avg1 = 0;
	double avg2 = 0;
	for (i = 0; i < co.numEnrolled; i++) {
		fprintf(fp2, "%s\n", co.students[i].name);
		for (j = 0; j < NUM_HW; j++) {
			sum1 += co.students[i].hw[j];
			co.students[i].hwAvg = sum1 / (double)NUM_HW;
		}
			fprintf(fp2,"HwAvg %.2lf\n",co.students[i].hwAvg); // fprintf(fd, "", var) fd = 0, 1, 2 0=stdin, 1 stdout 2 stderror
			// fprintf(stdout, "",&var)=printf("%d", var);
		
		for (j = 0; j < NUM_EXAM; j++) {
			sum2 += co.students[i].exams[j];
			co.students[i].examAvg = sum2 / (double)NUM_EXAM;
		}
			fprintf(fp2,"HwExam %.2lf\n", co.students[i].examAvg);
			sum1 = 0;
			sum2 = 0;
	}
			fprintf(fp2,"\nCourse\n");
			for (i = 0; i < co.numEnrolled; i++) {
				sum1 += co.students[i].hwAvg;
			}
			avg1 = sum1 / (double)co.numEnrolled;
			fprintf(fp2, "HwAvg %.2lf\n", avg1);
			
			for (j = 0; j < co.numEnrolled; j++) {
				sum2 += co.students[j].examAvg;
			}
				avg2 = sum2 / (double)co.numEnrolled;
				fprintf(fp2, "ExamAvg %.2lf", avg2);
				
				fclose(fp1);
				fclose(fp2);
			for(i=0;i<co.numEnrolled;i++)	
				free(co.students[i].name);

			return 0;
}

