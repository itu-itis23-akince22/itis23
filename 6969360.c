#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_STRING_LENGTH 50 //5 karakter olarak ayarlayıp, 5 input vererek array oluşturalım. En son kısımda \0 olmayacağı için, bunu bastırdığımızda çöp değerler de basılacak.

void swap(char *first, char*second){
  *first  = *first + *second;
  *second = *first - *second;
  *first  = *first - *second;
}

char* inttostring(int input,char* string)
{

    //Use ASCII values to convert the integer to string (completed)
	
	int i=0;
	do {
		
		string[i++] = input % 10 + '0';
		
	} while ((input /= 10) != 0);
	
	string[i] = '\0';
	int str_len = i;
	for (i=0;i<str_len/2;i++){
		swap(&string[i],&string[str_len - i - 1]);
	}
	
  	return string;
}

int strlength(char* string)
{
    int length = 0;
	//Find the length of the string (completed)
	
	for (int i=0; i<MAX_STRING_LENGTH; i++){
		if (string[i]== '\0') {
			break;
		}
		length++;
	}
	
    return length;
}

char* strcopy(char* source_string, char* destination_string)
{
	//Copy the source string to the destination string (completed)
	
	for (int i=0; i<strlength(source_string); i++){
		destination_string[i] = source_string[i];
	}
	
	destination_string[strlength(source_string)] = '\0';
	
    return destination_string;
}

char* strconcatenate(char* add_string, char* base_string)
{   
    //
	int base_length = strlength(base_string);
	base_string+=base_length;
	return strcopy(add_string,base_string);
}

char* substring(char* source_string, char* destination_string, int start, int size)
{
	//Copy the substring of the source string to the destination string (completed)
	
	int j = 0;
	for (int i=start; i<start+size; i++){
		destination_string[j] = source_string[i];
		j++;
	}
	destination_string[j] = '\0';
		
    return destination_string;
}

void generateCandidateEmails(char* name,char* surname,int year)
{
	char candidate1[MAX_STRING_LENGTH]="";//initial of name + surname + last two digits of year
	char candidate2[MAX_STRING_LENGTH]="";//first two from name + first two surname + randomnumber(4 digits)
	char candidate3[MAX_STRING_LENGTH]="";//surname + name + year
	char ending[MAX_STRING_LENGTH]="@itu.edu.tr";
	char temp[MAX_STRING_LENGTH]="";

    char choice;
    char sure;

	strconcatenate(substring(name,temp,0,1),candidate1); //send temp to substring, modify and return back. Then concatenate it to candidate1
	strconcatenate(surname,candidate1);
	strconcatenate(inttostring(year%100,temp),candidate1);
	strconcatenate(ending,candidate1);

	strconcatenate(substring(name,temp,0,2),candidate2);
	strconcatenate(substring(surname,temp,0,2),candidate2);
	strconcatenate(inttostring(rand()%1000,temp),candidate2);
	strconcatenate(ending,candidate2);

	strconcatenate(surname,candidate3);
	strconcatenate(name,candidate3);
	strconcatenate(inttostring(year,temp),candidate3);
	strconcatenate(ending,candidate3);
	
	printf("Email Candidate a): %s\n",candidate1);
	printf("Email Candidate b): %s\n",candidate2);
	printf("Email Candidate c): %s\n",candidate3);
	
	printf("Which one do you want to use? (a,b,c): ");
	scanf(" %c",&choice);
	printf("Are you sure? (y/n): ");
	scanf(" %c",&sure);
	
	if (sure == 'y') {
		printf("Your email is: ");
		if (choice == 'a') {
			printf("%s\n",candidate1);
		}
		else if (choice == 'b') {
			printf("%s\n",candidate2);
		}
		else if (choice == 'c') {
			printf("%s\n",candidate3);
		}
	}
	else if (sure == 'n') {
		
	}

	//Fill the missing printf/scanf parts by checking the test file.
}

int main()
{
	srand(time(NULL));
	//char name //perform dynamic memory allocation
	
	char* name = (char*)malloc(MAX_STRING_LENGTH*sizeof(char));
	
	//char surname //perform dynamic memory allocation
	
	
	
	char* surname = (char*)malloc(MAX_STRING_LENGTH*sizeof(char));
	
	int year;

	//Get the name, surname and year information from the user
	
	printf("Enter Your Name:");
	scanf("%s",name);
	printf("The name is: %.10s\n",name);
	printf("Enter Your Surname:");
	scanf("%s",surname);
	printf("The surname is: %.10s\n",surname);
	printf("Enter Your Birthyear:");
	scanf("%d",&year);

	//reallocate the memory you previously allocated for name and surname
	
	name = (char*)realloc(name,strlength(name)* sizeof(char)+1);
	surname = (char*)realloc(surname,strlength(surname)* sizeof(char)+1);
	
	//you may be using less space now, thus reduce your allocated memory based on the string sizes.

	generateCandidateEmails(name,surname,year);

	//What to do here? HINT: You dynamically allocated a memory part... 
	//Prevent memory leak.
	
	free(name);
	free(surname);
	name = NULL;
	surname = NULL;

	return 0;
}