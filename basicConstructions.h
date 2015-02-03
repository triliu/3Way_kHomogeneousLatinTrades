

//Implemented Thm 3.5
static void mTake1(int mu){   //LargeSetIdemp

	cout << "Generating From mTake1 a.k.a. idempotent (mu,m-1,m)-LTs" << '\n';
	for (int m = mu + 2; m<MAX_M; m++){
		A[m][m - 1] = true;
	}
	A[6][5] = false;
	cout << "Finished Generating From mTake1 a.k.a. (mu,m-1,m)" << '\n';
}


//	Construction 3.1 from our paper (originally thm7 in predecessor paper)
static void additionConstruction(int mu){
	//for each k, and each m (=m1plusm2), so see if there is two integers m1 and m2 with A[m1][k] and A[m2][k] with m1+m2=m
	for (int k = mu; k < MAX_M; k++){
		for (int m1plusm2 = k+1; m1plusm2 < MAX_M; m1plusm2++){
			if (A[m1plusm2][k] == false){
				for (int m1 = k+1; m1<m1plusm2-m1; m1++){
					if (A[m1][k]){
						if (A[m1plusm2 - m1][k]){
							A[m1plusm2][k] = true;
							
						}
					}

				}
			}
		}
		/*
	for (int m1 = mu; m1<MAX_M; m1++){
		cout << m1 << ' ';
		for (int m2 = m1; m2<MAX_M - m1; m2++){
			for (int k = mu; k < min(m1, m2); k++){
				if (A[m1][k] && A[m2][k]){
					if (m1 + m2<MAX_M){
						A[m1 + m2][k] = true;
					}
				}
			}
		}*/
	}
}


//	Implements Const2.4 between an idempotent (2,k_1,m_1)-Latin trade and a (2,k_2,m_2)-Latin trade (See theorem 2.1)- but we do not implement when m1 or m2 can be 2...see below 
static void DirectProductConstructionSpecific(){ //multiplicationConstruction
	for (int m1 = 5; m1<MAX_M; m1 += 2){
		for (int m2 = 3; m2<MAX_M / m1 + 1; m2++){
			if (m1*m2<MAX_M){
				for (int k1 = 3; k1 < m1; k1++){
					if (m1 == 5 && k1 == 3){
						//do nothing, as no known idempotent (2,3,5)-Latin Trade
					}
					else{
						for (int k2 = 3; k2 <= m2; k2++){
							A[m1*m2][k1*k2] = true;
						}
					}
				}
			}
		}
	}
}


//Implements the second part of Const2.4, when k2=2 and so only a (2,2,2*k2)-Latin trade exists. 
static void doublingConstruction(){ //DirectProductConstruction-part2
	for (int m1 = 5; m1<MAX_M / 2 + 1; m1 += 2){
		for (int k1 = 3; k1 < m1; k1++){
			if (m1 == 5 && k1 == 3){
				//do nothing, as no idempotent (2,3,5)-Latin Trade
			}
			else{
				for (int m2 = 1; m2 < MAX_M / (2 * m1); m2++)
					if (m1 * 2 * m2< MAX_M){
						A[m1 * 2 * m2][k1 * 2] = true;
					}
			}
		}
	}
}






// Implements Construction 2.5
static void MOLSConstruction(int max_l, int max_m){



	for (int l = 3; l <= max_l; l++){

		//cout << l << '\n';
		bool* k_base;
		bool* k_baseIdemp;
		bool* resulting1;
		bool* resulting2;

		bool* k_old = new bool[MAX_K];
		bool* k_new = new bool[MAX_K];



		//cout << l);
		if (l == 6){
			//do nothing in this case
		}
		else{
			for (int m = 5; m < max_m; m++){
				k_base = new bool[MAX_M];
				for (int i = 0; i < MAX_M; i++){
					k_base[i] = A[m][i];
				}
				k_baseIdemp = A[m];
				k_base[m] = true; //there exists a (mu,m,m)-Latin trade.
				if (m == 6){
					k_base[5] = true; //there exists a (3,5,6)-LT, but not an idempotent one
				}

				if (m*l<MAX_M){


					resulting1 = setPower(k_old, k_new, k_base, m*l, l - 1);
					resulting2 = new bool[m*l + 1];
					for (int i = 0; i <= m*l; i++){
						resulting2[i] = false;
					}
					for (int i = 0; i <= m*l; i++){
						if (k_baseIdemp[i] == true){
							for (int j = 0; j <= m*l; j++){
								if (resulting1[j] == true){
									if (i + j <= m*l){
										resulting2[i + j] = true;
									}
								}
							}
						}
					}
					for (int k = 0; k<m*l; k++){
						if (resulting2[k]){
							A[m*l][k] = true;
						}
					}
					delete[] resulting2;
				}
				delete[] k_base;
			}
		}
	}
}








static void Print(int min_to_print, int max_to_print){
	string out;
	bool test;
	for (int m = min_to_print; m <= max_to_print; m++){
		test = false;
		for (int k = 5; k < m; k++){ //k=6
			if (m<MAX_M){
				if (A[m][k] == false){ test = true; }
			}
		}
		if (test){
			cout << m << ": ";
			for (int k = 0; k <= m; k++){
				if (A[m][k]){}//out+=" "+1;}
				else{ cout << " " << k; };
			}
			cout << '\n';
			//cout << out.c_str() << '\n';
		}
	}
}


static void PrintTwicePrime(int min_to_print, int max_to_print){
	string out;
	bool test;
	for (int m = min_to_print; m <= max_to_print; m++){
		if (m<MAX_M && m % 2 == 0 && isPrime(m / 2)){
			test = false;
			for (int k = 4; k <= m; k++){
				if (A[m][k] == false){ test = true; }
			}
			if (test){
				cout << m << ": ";
				for (int k = 0; k <= m; k++){
					if (A[m][k]){ out += " " + 1; }
					else{ cout << " " << k; };
				}
				cout << '\n';
				//cout << out.c_str() << '\n';
			}
		}
	}
}




static void PrintNotTwicePrime(int min_to_print, int max_to_print){
	string out;
	bool test;
	for (int m = min_to_print; m <= max_to_print; m++){
		if (m<MAX_M && (m % 2 == 1 || (m % 2 == 0 && isPrime(m / 2) == false))){
			test = false;
			for (int k = 4; k <= m; k++){
				if (A[m][k] == false){ test = true; }
			}
			if (test){
				cout << m << ": ";
				for (int k = 0; k <= m; k++){
					if (A[m][k]){ cout << " " << 1; }
					else{ cout << " " << k; };
				}
				cout << '\n';
				//cout << out.c_str() << '\n';
			}
		}
	}
}






