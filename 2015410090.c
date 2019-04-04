// #define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>



#define MAX_TERMS 101
#define COMPARE(x,y)( ((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

typedef struct {
	float coef;
	int expon;
} polynomial;
// definition of polynomial


polynomial terms[MAX_TERMS];
int avail = 0;		// front of available index in terms

void attach(float coefficient, int exponent) {
	if (avail >= MAX_TERMS) {
		printf("Too many terms in the polynomial\n");
		return;
	}
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}

void padd(int startA, int endA, int startB, int endB, int *startD, int *endD) {
	float coefficient;
	*startD = avail;
	while (startA <= endA && startB <= endB) {							// we have to see from start to end
		switch (COMPARE(terms[startA].expon, terms[startB].expon)) {
		case -1:														// A's degree < B's degree
			attach(terms[startB].coef, terms[startB].expon);			// bigger degree computaion
			startB++;													// because we have to see next term of B
			break;
		case 0:															// A's degree == B's degree
			coefficient = terms[startA].coef + terms[startB].coef;		// if A or B's coef is null, coefficient is null
			if (coefficient)											// if coefficient is not null
				attach(coefficient, terms[startA].expon);				// sum of coef A and B attach to D
			startA++;													// because we have to see next term of A
			startB++;													// because we have to see next term of B
			break;
		case 1:															// A's degree > B's degree
			attach(terms[startA].coef, terms[startA].expon);			// bigger degree computaion
			startA++;													// because we have to see next term of A
		}
	}
	for (; startA <= endA; startA++) {									// if we finish seeing B
		attach(terms[startA].coef, terms[startA].expon);				// remaining terms of A attach to D
	}
	for (; startB <= endB; startB++) {									// if se finish seeing A
		attach(terms[startB].coef, terms[startB].expon);				// remaining terms of B attach to D
	}
	*endD = avail - 1;
	

}



int main() {

	int startA, endA, startB, endB;				// indices in terms
	int startD, endD;							// index of answer
	char c;										// tool of detecting '\n'

	printf("첫번째 다항식을 입력하세요.\n");
	startA = 0;									// A starts at 0
	endA = startA;								// At first, endA is same with startA
	
	while(1) {
		
		scanf("%f", &terms[avail].coef);		
		scanf("%d", &terms[avail].expon);
		endA++;									// if input is not null, endA becomes endA + 1
		avail++;								// because avail slot is full, avail has to be added by one
		if ( (c = fgetc(stdin)) == '\n') {		// if input is '\n', we have to stop while loof
			break;
		}
	}
	endA--;										// at last, endA has to be subtracted by 1
	
	printf("두번째 다항식을 입력하세요.\n");
	
	startB = avail;								// B starts at avail
	endB = startB;								// At first, endB is same with startB
	
	while (1) {
		scanf("%f", &terms[avail].coef);
		scanf("%d", &terms[avail].expon);
		endB++;
		avail++;
		if ((c = fgetc(stdin)) == '\n') {
			break;
		}
	}
	endB--;

	padd(startA, endA, startB, endB, &startD, &endD);





	int indexD = startD;

	while (1) {												// print D
		if (terms[indexD].expon != 0)
			printf("%.3fx^%d", terms[indexD].coef, terms[indexD].expon);
		else if (terms[indexD].expon == 0)
			printf("%.3f", terms[indexD].coef);
		
		if (indexD == endD) {								// end of print at endD
			break;
		}
		indexD++;
		printf(" + ");
	}

	// system("pause");

}