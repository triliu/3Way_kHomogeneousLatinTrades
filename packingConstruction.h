
//	Implements Theorem 5.1
static void packingConstruction(){

	cout << "Generating from the Packing construction" << '\n';
	for (int lambda = 6; lambda<sqrt(MAX_M); lambda++){
		for (int b = 1; b<lambda; b++){
			for (int a = b + 1; a<(MAX_M - lambda*lambda) / lambda; a++){
				int m = lambda*(lambda + a) + b;
				if (gcd(m, lambda) == 1){
					for (int k = 15; k <= lambda*lambda; k++){
						A[m][k] = true;
					}
					int k = 9;
					A[m][k] = true;
					k = 12;
					A[m][k] = true;
				}
				else{
				}
			}
		}
	}
	int lambda = 3;
	for (int b = 1; b<lambda; b++){
		for (int a = b + 1; a<(MAX_M - lambda*lambda) / lambda; a++){
			int m = lambda*(lambda + a) + b;
			if (gcd(m, lambda) == 1){
				int k = 9;
				A[m][k] = true;
			}
			else{
			}
		}
	}
	lambda = 4;
	for (int b = 1; b<lambda; b++){
		for (int a = b + 1; a<(MAX_M - lambda*lambda) / lambda; a++){
			int m = lambda*(lambda + a) + b;
			if (gcd(m, lambda) == 1){
				int k = 9;
				A[m][k] = true;
				k = 12;
				A[m][k] = true;
				k = 15;
				A[m][k] = true;
				k = 16;
				A[m][k] = true;
			}
			else{
			}
		}
	}
	lambda = 5;
	for (int b = 1; b<lambda; b++){
		for (int a = b + 1; a<(MAX_M - lambda*lambda) / lambda; a++){
			int m = lambda*(lambda + a) + b;
			if (gcd(m, lambda) == 1){
				for (int k = 18; k <= 25; k++){
					A[m][k] = true;
				}
				int k = 9;
				A[m][k] = true;
				k = 12;
				A[m][k] = true;
				k = 15;
				A[m][k] = true;
				k = 16;
				A[m][k] = true;
			}
			else{
			}
		}
	}

	cout << "Finished generating from the Packing construction" << '\n';
}
