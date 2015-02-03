
//Implements Theorem 2.9. 
static void Transversals3(){
	cout << "Generating From Transversals3\n";
	for (int m = 33; m<MAX_M; m += 2){
		int d1 = (m - 9) % 18 / 2;
		int d2 = (m - 11) % 22 / 2;
		for (int k = 6; k <= min(m - min(d1, d2 + 3), m - 1); k++){
			if ((m == 51 && k == 22) || (m == 53 && k == 23)){
				//the two exceptional cases; dont do anything
			}
			else{
				A[m][k] = true;
			}
		}

	}

	cout << "Finished Generating From Transversals3\n";
}


