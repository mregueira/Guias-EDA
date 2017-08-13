#include <stdio.h>

#define OPTION '-'
#define EOW '\0'
#define SPACE ' '

typedef struct 
{
	int u;
	int v;
} tparams;

typedef int (*pCallback) (char *, char*, void *);

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData);

int process(char *key, char *value, void *Data);

int main(int argc, char *argv[])
{
	tparams P;
	int test;
	char *arr1[]={"NAME", "-key","val", "param"}; // OK
	char *arr2[]={"NAME", "- key","val", "param"}; // Error
	char *arr3[]={"NAME", "-","val", "param"}; // Error
	char *arr4[]={"NAME", "-key","val", "-key"}; // Error
	char *arr5[]={"NAME", "-key","val", "-"}; // Error
	char *arr6[]={"NAME", "-key","val", "- key"}; // Error
	char *arr7[]={"NAME", "-key","-key", "param"}; // Error

	test = parseCmdLine(4, arr1, process, &P);

	if((test == -1)||(test == 0))
		printf("\n ->Error\n");
	else
		printf("\n ->Successful: %d\n", test);

	test = parseCmdLine(4, arr2, process, &P);

	if((test == -1)||(test == 0))
		printf("\n ->Error\n");
	else
		printf("\n ->Successful: %d\n", test);

	test = parseCmdLine(4, arr3, process, &P);

	if((test == -1)||(test == 0))
		printf("\n ->Error\n");
	else
		printf("\n ->Successful: %d\n", test);

	test = parseCmdLine(4, arr4, process, &P);

	if((test == -1)||(test == 0))
		printf("\n ->Error\n");
	else
		printf("\n ->Successful: %d\n", test);

	test = parseCmdLine(4, arr5, process, &P);

	if((test == -1)||(test == 0))
		printf("\n ->Error\n");
	else
		printf("\n ->Successful: %d\n", test);

	test = parseCmdLine(4, arr6, process, &P);

	if((test == -1)||(test == 0))
		printf("\n ->Error\n");
	else
		printf("\n ->Successful: %d\n", test);

	test = parseCmdLine(4, arr7, process, &P);

	if((test == -1)||(test == 0))
		printf("\n ->Error\n");
	else
		printf("\n ->Successful: %d\n", test);

	return 0;
}

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData){

	int i = 1, ret; 
	int opt_and_params = 0;

	while(i < argc){
		if(*argv[i] == OPTION){ // is option
			if((i+1 != argc)&&( *(argv[i]+1) != EOW)&&(*(argv[i]+1) != SPACE)){
				if(*argv[i+1] != OPTION){
					printf("%s\n", argv[i]+1);
					printf("%s\n\n", argv[i+1]);
					ret = p(argv[i]+1, argv[i+1], userData);
					i += 2;
				}
				else{
					ret = -1;
				}
			}
			else{
				ret = -1;
			}
		}
		else{ // is parameter
			printf("%s\n\n", argv[i]);
			ret = p(NULL, argv[i], userData);
			i++;
		}

		if((ret == -1)||(ret == 0)) // any error
			return ret;
		else
			opt_and_params++; // count options and parameters
	}

	return opt_and_params;
}

int process(char *key, char *value, void *Data){
	return 1;

}