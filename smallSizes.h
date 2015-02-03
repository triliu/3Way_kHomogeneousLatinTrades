
//	Implements Theorem 4.1
static void smallSizes(){
	cout << "Generating From smallSizes" << '\n';
	//k=4
	A[5][4] = true;
	A[10][4] = true;
	for (int m = 15; m<MAX_M; m += 5){
		A[m][4] = true;
	}
	//k=5
	A[7][5] = true;
	A[8][5] = true;
	A[9][5] = true;
	A[11][5] = true;
	A[12][5] = true;
	A[14][5] = true;
	A[15][5] = true;
	A[16][5] = true;
	A[17][5] = true;
	A[18][5] = true;
	A[19][5] = true;
	A[20][5] = true;

	//k=6
	A[7][6] = true;
	A[8][6] = true;
	A[9][6] = true;
	A[10][6] = true;
	A[11][6] = true;
	A[12][6] = true;
	A[13][6] = true;



	//k=7->18
	for (int k = 7; k <= 18; k++){
		for (int m = k + 1; m<MAX_M; m++){
			A[m][k] = true;
		}
	}


	cout << "Finished Generating From smallSizes" << '\n';
}
