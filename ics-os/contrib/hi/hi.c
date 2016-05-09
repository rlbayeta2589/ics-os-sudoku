
#include "../../sdk/dexsdk.h"

int main(){	
	char name[30];
	printf("Your Name? ");
	fgets(name, 30, stdin);
	printf("You are %s \n", name);

	return 0;
}
