
bool primePower(int n){
	int quotient = 2;
	while (quotient <= n){
		if (n%quotient == 0){
			while (n>1){
				if (n%quotient == 0){
					n = n / quotient;
				}
				else{
					return false;
				}
			}
			return true;
		}
		quotient++;
	}
	cout << "primePower - ERROR ERROR - no divisors found. n= " << n << '\n';
	return false;
}


static bool isPrime(int n){
	int quotient = 2;
	while (quotient <= n){
		if (n%quotient == 0){
			if (n == quotient){
				return true;
			}
			else{
				return false;
			}
		}
		quotient++;
	}
	cout << "primePower - ERROR ERROR - no divisors found. n= " << n << '\n';
	return false;
}



static int gcd(int a, int b){
	if (b>0){
		return gcd(b, a%b);
	}
	else{
		return a;
	}
}


static bool* setPower(bool* k_old, bool* k_new, bool* k_base, int MAX_K, int power){


	//k_new at n=1;
	for (int k = 0; k <= MAX_K; k++){
		k_old[k] = k_base[k];
		k_new[k] = k_base[k];
	}



	for (int n = 2; n <= power; n++){ //MAX_M
		//cout << n);
		//k_new at n;

		for (int i = 0; i < MAX_K; i++){
			if (k_base[i]){
				for (int j = 0; j < MAX_K - i; j++){
					if (k_old[j])
						k_new[i + j] = true;
				}
			}
		}
		for (int k = 0; k<MAX_K; k++){
			k_old[k] = k_new[k];
		}
	}
	return k_new;
}
