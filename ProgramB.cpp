// ProgramB.cpp : Defines the entry point for the console application.
//

#include<iostream>
using namespace std;


		//returns true iff n is a positive prime >=2
		bool isPrime(int n){
			if (n <= 1){ return false; }
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
			cout << "primePower - ERROR: -  (we shouldsnt arrive here) - no divisors found. n= " << n << '\n';
			return false;
		}


		//basic gcd algorithm
		int gcd(int a, int b){
			if (b>0){
				return gcd(b, a%b);
			}
			else{
				return a;
			}
		}


		//returns true iff n is a prime power >=2
		bool primePower(int n){
			if (n <= 1){ return false; }
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
			cout << "primePower - ERROR:  (We should not arrive here) - no divisors found. n= " << n << '\n';
			return false;
		}








int main(int argc, char* argv[])
		{



			//we want to find if the spectrum for  all m values less than MAX_M_PT2
			//we know the spectrum for all values less than MAX_M_PT1
			int MAX_M_PT2 = 1024 * 64*4 + 1;
			int MAX_M_PT1 = 5619 + 1;// 1024 * 4;


			bool* B = new bool[MAX_M_PT2];

			for (int m = 0; m<MAX_M_PT2; m++){
				B[m] = false;
			}

			for (int m = 0; m<MAX_M_PT1; m++){
				B[m] = true;
			}



			B[194] = false;
			B[158] = false;
			B[146] = false;
			B[134] = false;
			B[122] = false;
			B[106] = false;
			B[94] = false;
			B[86] = false;
			B[82] = false;
			B[74] = false;
			B[62] = false;
			B[59] = false;
			B[58] = false;
			B[53] = false;
			B[46] = false;
			B[43] = false;
			B[41] = false;
			B[38] = false;
			B[37] = false;
			B[34] = false;
			B[31] = false;
			B[29] = false;
			B[26] = false;
			B[23] = false;
			B[22] = false;
			B[13] = false;
			B[10] = false;
			B[6] = false;
			B[4] = false;
			B[3] = false;
			B[2] = false;
			B[1] = false;
			B[0] = false;






			//Implements Lemma 3.1 
			//for each value of m in 4 -> 2^12, if the spectrum is complete for m, then the spectrum is complete for all multiples of m (except multiples of 2)
			for (int m = 10; m< MAX_M_PT1; m++){
				if (B[m]){
					for (int n = 3; n <= (MAX_M_PT2 - 1) / m; n++){
						if (n==6 && m< 20){
							//do nothing, as in this case, the lemma requires 5 <= m/4, which is not true
						}
						else{
							B[m*n] = true;
						}
					}
				}
			}


			//Implements Corollary 3.13, with gamma either 0 or 1 
			//This yields the upper portion of the spectrum for any particular m a prime or twice a prime.
			for (int alpha = 16; alpha<sqrt(MAX_M_PT2) + 1; alpha++){
				
				//In the case gamma = 0, we need B[alpha] && B[alpha-1] to be true in order to apply Corollary 3.13
				//In the case gamma = 1, we need, B[alpha] && B[alpha-1] && B[alpha-2] to be true in order to apply Corollary 3.13
				//When the following condition is true, the required 3-way Latin trades needed for Corollary 3.13 exist for both gamma= 0 or 1
				if (B[alpha] && B[alpha - 1] && B[alpha - 2]){
					for (int n = alpha; n <= MAX_M_PT2 / (alpha - 2); n++){  //this upper bound is chosen as n*alpha -2(n-7) < MAX_M_PT2, yields n<(MAX_M_PT2-14)/(alpha-2), which we round up.

						//this next bit has gamma=0 and 1, which is done implicitly by taking uDash = gamma*(n-7) + u
						if (primePower(n)){
							
							for (int uDash = 0; uDash<2 * (n - 7); uDash++){
								int m = n*alpha - uDash;
								//Currently the antecedent of Corollary 3.13 is true, and yields (3,k,m)-Latin trades for  k\in {8n-u-1,...,m}
								if (m< MAX_M_PT2 && B[m] == false && (isPrime(m)|| (m%2 ==0 && isPrime(m/2)))){

									//Implements Theorem 4.2 to yield the lower portion of the spectrum:
									int lambda = floor(sqrt(((double)(m))));
									bool test = true;
									int a = -1;
									int b = -1;
									while (test){
										if (gcd(m, lambda) == 1){
											b = m%lambda;
											a = (m - b) / lambda - lambda;
											if (a>b){
												test = false;
											}
											else{
												lambda--;
											}
										}
										else{
											lambda--;

										}
										if (lambda <= 4){
											cout << "Lambda is not allowed to be below 5";
											int aa;
											cin >> aa;
										}

									}


									if (8 * n - uDash - 1 <= (lambda)*(lambda)){ 
										B[m] = true;
									}
								}
							}
						}
					}
				}
			}


			////////////////////////////////////////////////////////////////////////////////////////////////////
			//Repeated to fill in composite values from primes that we did not know to exist before the above///
			////////////////////////////////////////////////////////////////////////////////////////////////////
			//Implements Lemma 3.1 
			//for each value of m in 4 -> 2^12, if the spectrum is complete for m, then the spectrum is complete for all multiples of m (except multiples of 2)
			for (int m = 10; m< MAX_M_PT2; m++){
				if (B[m]){
					for (int n = 3; n <= (MAX_M_PT2 - 1) / m; n++){
						if (n == 6 && m< 20){
							//do nothing, as in this case, the lemma requires 5 <= m/4, which is not true
						}
						else{
							B[m*n] = true;
						}
					}
				}
			}


			//Done now

			//Print those that did not have there spectrum completed
			cout << "Printing those m that DO NOT have a complete spectrum, from m=0 to m=2^18"<<'\n';
			for (int i = 0; i<MAX_M_PT2; i++){
				if (B[i] == false){
					cout << i << " -  isprime: " << isPrime(i) <<  '\n';
					if (isPrime(i) == false){
						cout << "    ";
						for (int j = 1; j <= i; j++){
							if (i%j==0){
								cout << j << ' ';
							}
						}
						cout << '\n';
					}
				}
			}
			int a;
			cin >> a;
			return 0;
	}
	




	


