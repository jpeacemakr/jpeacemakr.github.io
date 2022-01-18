//source : https://linux.die.net/man/3/sscanf
//source: https://stackoverflow.com/questions/27677063/scanning-until-new-line. to figure out how to get it to stop reading at new line.
//source: https://www.tutorialspoint.com/c_standard_library/ctype_h.htm

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


int main() 
{

	char sentence[1000];
	char pig_word[256];
	char punctuation_front[256];
	char punctuation_back[256];

	//memset( word, '\0', sizeof(word) );
	memset( pig_word, '\0', sizeof(pig_word) );
	memset( punctuation_front, '\0', sizeof(punctuation_front) );
	memset( punctuation_back, '\0', sizeof(punctuation_back) );
	memset( sentence, '\0', sizeof(sentence) );


	//change each word to pig latin and print
	while (fgets(sentence, 1000, stdin)) //could be used to read an entire file until buffer is closed
	{
		fflush(stdin);

		//printf("Debug: sentence: %s-\n", sentence);

		//split word up into word pieces
		char *word;
		word = strtok(sentence, " ");

		//printf("Debug: first word check: %s\n", word);
		//printf("Debug: first word length check: %i\n", (int)strlen(word));

		while( word != NULL ) 
		{	
			//copy punctuation at the beginning of the word and store in punctuation_front
			int i = 0;
			while (isalnum(word[i])==0) {
				punctuation_front[i] = word[i];
				i++;
			}

			//printf("Debug: second word check: %s-\n", word);
			//printf("Debug: second word length check: %i\n", (int)strlen(word));

			//copy punctuation at the end of the word and store in punctuation_back
			//count number of punctuation marks at end of the word
			int j = (int)strlen(word)-1;
			int k = 0; //length of punctuation_back
			while (isalnum(word[j])==0 && j >= 0){
				j--;
				k++;
			}

			//printf("Debug: third word check: %s\n", word);
			//printf("Debug: third word length check: %i\n", (int)strlen(word));

			//copy the punctuation marks to punctuation_back
			for (int n = 0; n < k ; n++){
				punctuation_back[n] = word[strlen(word)-k+n];
			}

			//printf("Debug: fourth word check: %s\n", word);
			//printf("Debug: fourth word length check: %i\n", (int)strlen(word));

			//printf("Debug: punctuation front: %s\n", punctuation_front);
			//printf("Debug: punctuation_front length check: %i\n", (int)strlen(punctuation_front));

			//if punctuation_front length is the same as word, clear punctuation_front
			if ((int)strlen(word)==(int)strlen(punctuation_front)) 
			{
				memset(punctuation_front, '\0', sizeof(punctuation_front));
				//printf("Debug: resetting punctuation_front\n");
			}
			
			//printf("Debug: punctuation front: %s\n", punctuation_front);
			//printf("Debug: punctuation end: %s\n", punctuation_back);
			
			//if punctuation_end is the same length as word, clear punctuation_back
			if ((int)strlen(word)==(int)strlen(punctuation_back)) 
			{
				memset(punctuation_back, '\0', sizeof(punctuation_back));
				//printf("Debug: resetting punctuation_back\n");
			}

			//printf("Debug: punctuation end: %s\n", punctuation_back);
			//printf("Debug j: %i\n", j);
			//printf("Debug i: %i\n", i);
			//printf("Debug k: %i\n", k);


			//copy word without beginning and end punctuation to pig_word
			for (int l = 0; l < ((int)strlen(word)-(int)strlen(punctuation_front)-(int)strlen(punctuation_back)); l++)  
			{
				pig_word[l] = word[l+(int)strlen(punctuation_front)];
			}

			//if word starts with a digit, don't shift letters or add "ay"
			if (isalpha(pig_word[0])) 
			{
				//printf("Debug: not a number\n");
				
				//check to see if first letter is uppercase
				int upper_case = 0; //false is default 
				if (isupper(pig_word[0]))
				{
					upper_case = 1; //set to true
					pig_word[0] = tolower(pig_word[0]);
				}

				//if there are vowels in the word and is more than one letter
				if (strpbrk(pig_word,"aeiouAEIOU") && (int)strlen(pig_word)>1)
				{
					//move letters to the rear of the word until it starts with a vowel
					while (pig_word[0]!='a' && pig_word[0]!='e' && pig_word[0]!='i' && pig_word[0]!='o' && pig_word[0]!='u' && pig_word[0]!='A' && pig_word[0]!='E' && pig_word[0]!='I' && pig_word[0]!='O' && pig_word[0]!='U') 
					{
						//printf("Debug: rearranging letters\n");
						char first_letter = pig_word[0];
						//put first letter at the end of pig_word and shift letters
						for(int m=0; m<(int)strlen(pig_word)-1; m++)
						{
							pig_word[m]=pig_word[m+1];
						}
						pig_word[(int)strlen(pig_word)-1] = first_letter;
					}
				} 
				//but if there is only a y as a vowel
				else if (strpbrk(pig_word,"y") && (int)strlen(pig_word)>1)
				{
					//move letters to the rear of the word until it starts with a y
					while (pig_word[0]!='y' && pig_word[0]!='Y') 
					{
						//printf("Debug: rearranging letters\n");
						char first_letter = pig_word[0];
						//put first letter at the end of pig_word and shift letters
						for(int m=0; m<(int)strlen(pig_word)-1; m++)
						{
							pig_word[m]=pig_word[m+1];
						}
						pig_word[(int)strlen(pig_word)-1] = first_letter;
					}
				}

				//make new first letter uppercase if it was uppercase before
				if (upper_case)
				{
					pig_word[0] = toupper(pig_word[0]);
				}

				//put ay at the end of pig_word
				strcat(pig_word, "ay");

			}

			//put punctuation back at the end of pig_word 
			strcat(punctuation_front, pig_word);
			strcpy(pig_word, punctuation_front);

			//put punctuation back at the front of pig_word 
			strcat(pig_word, punctuation_back);

			//printf("Debug: word: %s \n-", word);
			//printf("Debug: pig_word: %s \n-", pig_word);

			printf("%s", pig_word);
			//print space after pig_word if not new line is in the word
			if (strcspn(pig_word, "\n") == strlen(pig_word))
			{
				printf(" ");
			}
 			fflush(stdout);

			//reset the words
			memset( pig_word, '\0', sizeof(pig_word) );
			memset( punctuation_front, '\0', sizeof(punctuation_front) );
			memset( punctuation_back, '\0', sizeof(punctuation_back) );

			//get next word from sentence
	    	word = strtok(NULL, " ");
	    	//printf("\nDebug: next word: %s\n-", word);
			//printf("Debug: loop-----------------------\n\n");
	
		}
	}
	printf("\n");
}
