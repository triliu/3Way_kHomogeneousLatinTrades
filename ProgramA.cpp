
#include<iostream>
#include<algorithm>
using namespace std;




bool verbose = false;

const int MAX_M = 5618+10;
int PRINT_M = MAX_M;
int MAX_K = MAX_M;
bool** A = new bool*[MAX_M];

#include "smallSizes.h"
#include "basicFunctions.h"
#include "Transversals3.h"
#include "basicConstructions.h"
#include "RPB_Construction.h"


#include "packingConstruction.h"







int main(int argc, char* argv[])
{
	cout << "This program will compose the known existence properties of 3-way k-homogeneous Latin trades" << '\n';
	int mu = 3;

	for (int m = 0; m < MAX_M; m++){

		A[m] = new bool[MAX_M];
	}




	//////////////////////PART 1/////////////////////
	for (int m = 0; m<MAX_M; m++){
		//Clear A[][]
		for (int k = 0; k<MAX_K; k++){

			A[m][k] = 0;
		}
		A[m][0] = true;
	}
//Theorem 3.5
	mTake1(mu);
//Theorem 3.10
	Transversals3();	
//Theorem 4.1
	smallSizes();
//Theorem 4.7
	packingConstruction();


//Theorem 3.9 (m_2 = 2)
	cout << "doubling construction start" << '\n';
	doublingConstruction();
//Theorem 3.9 (m_2 != 2)
	cout << "DirectProductConstruction start" << '\n';
	DirectProductConstructionSpecific();




	//////////////////////PART 2/////////////////////
	//Theorem 3.1
	cout << "addition construction start" << '\n';
	additionConstruction(mu);
	//Theorem 3.3
	cout << "MOLS construction start" << '\n';
	MOLSConstruction(20, MAX_M);



	//////////////////////PART 3/////////////////////
	RPB_Constructionx5(80);
	RPB_ConstructionNew_Gamma0(80);



	//////////////////////PART 4/////////////////////
	//Theorem 3.1
	additionConstruction(mu);


	


	//////////////////////FINISHED/////////////////////


	cout << "Printing those m that DO NOT have a complete spectrum, from m=0 to m=2^12" << '\n';
	//Print(0, PRINT_M);

	Print(0, PRINT_M);
	int aaa;
	cin >> aaa;




	int a;
	cin >> a;
	return 0;
}




