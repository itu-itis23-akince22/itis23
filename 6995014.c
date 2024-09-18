#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum bool {
	FALSE,
	TRUE
} BOOL;

BOOL read_from_text_file    (FILE* text_file,   char*, char*, int*, char*);
BOOL write_into_text_file   (FILE* binary_file, char*, char*, int*, char);
int main (int argc, char*argv[]) {
	
	if(argc!=4) {
		printf("Enter:\n");
		printf("%s ", argv[0]);
		printf("\"Source Text File Name\" ");
		printf("\"Destination Text File Name\" ");
		printf("\"The Number of Students\"\n");
		return 1;
	}
	char* src_text_file_name = argv[1];
	char* dst_text_file_name = argv[2]; 
	int number_of_students = atoi(argv[3]);
	FILE* text_file;
	FILE* text_file_2;
	char student_name[26];
	char student_id[4];
	int student_grades[6];
	char letter_grade;
	
	printf("\nRead From Text File and Write Into Binary File Started...\n ");
	if (!(text_file=fopen(src_text_file_name, "r"))) {
        printf("\n cannot open %s\n",dst_text_file_name);
        return 1;
    }
    if (!(text_file_2= fopen(dst_text_file_name,"w"))){
        printf("\n cannot open %s\n",dst_text_file_name);
        return 1;
    }

    while (read_from_text_file(text_file,student_name,student_id,student_grades,&letter_grade)){
        write_into_text_file(text_file_2,student_name,student_id,student_grades,letter_grade);
    }
    fclose(text_file);
    fclose(text_file_2);

    printf("\nread from text file and write into text file comleted\n");

    int** grades_matrix;
    grades_matrix= (int*)malloc(number_of_students*sizeof(int));
    if (!(text_file=fopen(src_text_file_name,"r"))){
        printf("\n cannot open %s\n",dst_text_file_name);
        return 1;
    }

    for(int i=0; i<number_of_students;i++){
        read_from_text_file(text_file,student_name,student_id,student_grades,&letter_grade);
        grades_matrix[i]=(int*)malloc(6*sizeof(int));
        for (int j=0; j<6; j++) {
            grades_matrix[i][j] = student_grades[j];
        }
    }

    printf("num of students: %d",number_of_students);

    for (int i=0; i<number_of_students; i++){
        for (int j=0; j<6; j++) {
            printf("%d",grades_matrix[i][j]);
        }
        printf("\n");
    }

    for (int i=0; i<number_of_students; i++){
        
        free(grades_matrix[i]);

    }
    free(grades_matrix);



	return 0;
}; 
	

BOOL read_from_text_file(FILE* text_file, char* student_name, char* student_id, int* student_grades, char* letter_grade) {
    int amount_read;
    amount_read=fscanf(text_file,"%s %s %d %d %d %d %d %d %c",
                            student_name, student_id,
                            &student_grades[0],&student_grades[1],&student_grades[2],&student_grades[3],&student_grades[4],&student_grades[5],
                            letter_grade);
    if (amount_read==9) return TRUE;
    else                return FALSE;    


};

BOOL write_into_text_file (FILE* text_file, char* student_name, char* student_id, int* student_grades, char letter_grade) {
    int amount_written;
    amount_written=fscanf(text_file,"%s %s %d %d %d %d %d %d %c",
                            student_name, student_id,
                            &student_grades[0],&student_grades[1],&student_grades[2],&student_grades[3],&student_grades[4],&student_grades[5],
                            &letter_grade);
    if (amount_written<0) return TRUE;
    else                  return FALSE;    

   
}