

//setwise adds D_SUM and  D, and places the result into D_SUM
void DSumPlusD(bool* D_SUM_TEMP, bool* D_SUM, bool* D){
	for (int i = 0; i<MAX_M; i++){
		D_SUM_TEMP[i] = false;
	}

	//Set D_SUM_TEMP[d] true if d = d_n + (Sum_{i=1}^{n-1} d_i) + d_{\infty}, for some j=d_n, i =  (Sum_{i=1}^{n-1} d_i) + d_{\infty}
	for (int i = 0; i<MAX_M; i++){
		if (D_SUM[i]){
			for (int j = 0; j < MAX_M - i; j++){
				if (D[j]){
					D_SUM_TEMP[i + j] = true;
				}
			}
		}
	}
	//Set D_SUM[d] true if d = (Sum_{i=1}^{n} d_i) + d_{\infty}
	for (int i = 0; i<MAX_M; i++){
		D_SUM[i] = D_SUM_TEMP[i];
	}
}




//Implements Corollary 3.13, when d_{infinity} is 1
static void RPB_Constructionx5(int max_n){
	cout << "Generating From RPB_Construction's Construction" << '\n';


	//D_SUM will be the the set D added n times, and adding 1, for the R_{\infty} Resolution class
	bool* D_SUM = new bool[MAX_M];
	bool* D_SUM_TEMP = new bool[MAX_M];
	bool* D = new bool[MAX_M];


	for (int alpha = 8; alpha<max_n; alpha++){
		cout << "alpha = " << alpha << '\n';
		//over all gamma, up to alpha-8 (Those gamma with values from alpha-7 to alpha are not useful, so are skipped)
		for (int gamma = 0; gamma<=alpha - 8; gamma++){


			for (int i = 0; i<MAX_M; i++){
				D[i] = false;
				D_SUM[i] = false;
				D_SUM_TEMP[i] = false;
			}
			bool test;

			//If there exists a (3,b-d,b)-LT for each possible block size b,
			//	set D[d]=true. Otherwise set it to false.
			for (int d = 1; d <= alpha - (gamma + 1) - 5; d++){ //this goes over the possible d, s.t. there exists a trade with k=b-d for each relevant b
				test = true;
				for (int i = 0; i <= gamma + 1; i++){
					if (alpha - (gamma + 1) - d + i >= 3){	//this goes over the possible lengths of blocks
						if (A[alpha - (gamma + 1) + i][alpha - (gamma + 1) - d + i] == false){
							test = false;
							break;
						}
					}
				}
				D[d] = test;
			}




			//Set D_SUM to be Sum_{i=1}^1 d_i + d_{\infty}, where d_{\infty}={1} 
			for (int i = 0; i<MAX_M - 1; i++){
				if (D[i]){
					D_SUM[i + 1] = true;
				}
			}

			for (int n = 2; n <= max_n; n++){
				DSumPlusD(D_SUM_TEMP, D_SUM, D);

				//If the conditions of Corollary 314 are satisfied, we can apply it to yield a (3,k,m)-Latin trade with m=alpha*n-(n-5)*gamma-u, and k = m+n-d, with 1 <= u <= n-5
				if (primePower(n) && n >= alpha){
					for (int u = 1; u <= n - 5; u++){
						if (n - u != 6){ //as there does not exist s (3,5,6)-LT
							int m = alpha*n - (n - 5)*gamma - u;
							if (m < MAX_M){
								for (int d = 0; d < m; d++){
									if (D_SUM[d] && m < MAX_M && m + n - d >= 0){
										if (n - d > 0){ cout << "ERROR: RPB_ConstructionNew - d can not be such a low value -- d= " << d << "  m= " << m << "  alpha= " << alpha << " gamma = " << gamma << "  n = " << n << '\n'; }
										A[m][m + n - d] = true;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	cout << "Finished Generating From RPB_Construction News Construction" << '\n';
}








//Implements Corollary 3.13, when gamma=0 and d_{infinity} can be >=1
static void RPB_ConstructionNew_Gamma0(int max_n){
	cout << "Generating From RPB_Construction's Construction _ Gamma=0" << '\n';


	for (int alpha = 8; alpha<max_n; alpha++){
		cout << "alpha = " << alpha << '\n';
		// for gamma = 0 (we keep this loop for consistency with previous program).
		for (int gamma = 0; gamma<1; gamma++){
			bool* D_SUM = new bool[MAX_M];
			bool* D_SUM_TEMP = new bool[MAX_M];
			bool* D = new bool[MAX_M];
			bool* D_INFINITY = new bool[MAX_M];

			for (int i = 0; i<MAX_M; i++){
				D[i] = false;
				D_SUM[i] = false;
				D_SUM_TEMP[i] = false;
				D_INFINITY[i] = false;
			}
			bool test;

			//If there exists a (3,m-d,m)-LT for each possible block size m,
			//	set D[d]=true. Otherwise set it to false.
			for (int d = 1; d <= alpha - (gamma + 1) - 3; d++){ //this goes over the possible d, s.t. there exists a trade with k=|b|-d for each relevant b
				test = true;
				for (int i = 0; i <= gamma + 1; i++){
					if (alpha - (gamma + 1) - d + i >= 3){	//this goes over the possible lengths of blocks
						if (A[alpha - (gamma + 1) + i][alpha - (gamma + 1) - d + i] == false){
							test = false;
							break;
						}
					}
				}
				D[d] = test;
			}


			//Set D_SUM to be Sum_{i=1}^1 d_i    (for this case, we will add d_{\infty} later)
			for (int i = 0; i<MAX_M - 1; i++){
				if (D[i]){
					D_SUM[i] = true;
				}
			}



			for (int n = 2; n <= max_n; n++){

				for (int i = 0; i<MAX_M; i++){
					D_SUM_TEMP[i] = false;
				}


				//Set D_SUM_TEMP[d] true if d = d_n + (Sum_{i=1}^{n-1} d_i), for some b=d_n, a =  (Sum_{i=1}^{n-1} d_i)
				for (int a = 0; a<MAX_M; a++){
					for (int b = 0; b<MAX_M; b++){
						if (D_SUM[a] && D[b] && a + b<MAX_M){
							D_SUM_TEMP[a + b] = true;
						}
					}
				}

				//Set D_SUM[d] true if d = (Sum_{i=1}^{n} d_i)
				for (int i = 0; i<MAX_M; i++){
					D_SUM[i] = D_SUM_TEMP[i];
				}

				//If the conditions of Corollary 314 are satisfied, we can apply it to yield a (3,k,m)-Latin trade with m=alpha*n-(n-5)*gamma-u, and k = m+n-d, with 1 <= u <= n-5
				if (primePower(n) && n >= alpha){
					for (int u = 1; u <= n - 5; u++){
						//resets D_INFINITY
						for (int i = 0; i<MAX_M; i++){
							D_INFINITY[i] = false;
						}


						//Fills in D_INFINITY with possible values
						for (int d = 1; d <= n - u; d++){
							if (A[n][n - d] && A[n - u][n - u - d]){
								D_INFINITY[d] = true;
							}
						}

						int m = alpha*n - (n - 5)*gamma - u;
						if (m<MAX_M){
							for (int nn = 0; nn<n; nn++){
								for (int d = 0; d<m; d++){
									//The conditions of Corollary 3.14 are satisfied with nn = d_{\infty} and d = (Sum_{i=1}^{n} d_i)
									if (D_SUM[d] && D_INFINITY[nn] && m<MAX_M && m + n - d >= 0){
										if (n - d>0)
										{
											cout << "ERROR: RPB_ConstructionNewGamma0 - d can not be such a low value -- d= " << d << "  m= " << m << "  alpha= " << alpha << " gamma = " << gamma << "  n = " << n << '\n';
										}
										A[m][m + n - d - nn] = true;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	cout << "Finished Generating From RPB_Construction New Gamma0 Construction" << '\n';
}
