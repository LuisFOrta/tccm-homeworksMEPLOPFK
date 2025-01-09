//C function to obtain the HF energy
//STILL NEEDS TO BE TESTED!!
double HF(int32_t N_occ, int32_t N_mo, double E_NN, double* const one_e_int, \
		int_64t nInts, int32_t* index, double* const two_e_int){

	//Initialize one-and two-electron summations to zero
	double one_e_sum = 0;
	double two_e_sum = 0;

	//Add iteratively the one-electron terms
	for (int i = 0; i < N_occ; i++) {
		//Add new term to the one electron summation
		one_e_sum += *(one_e_int + (N_mo * i + i)); //Reading diagonal of array
	}

	//Add iteratively the two-electron terms
	for (int n = 0; n < nInts; n++) { //Iterate over integral array just once to make memory read process more efficient
		//Define indeces for the integral "n"
		int i = index[4*n];
		int j = index[4*n+1];
		int k = index[4*n+2];
		int l = index[4*n+3];

		//Only use if all indeces belong to occupied orbitals
		if (i < N_occ && j < N_occ && k < N_occ && l < N_occ) {
			//Case 1: All indeces are equal
			if (i == j && j == k && k == l){
				two_e_sum += two_e_int[n]
			}
			//Case 2: Columb integral
			else if (i == k && j == l){
				two_e_sum += 4*two_e_int[n]
			}
			//Case 3: Exchange integral
			else if (i == j && k == l){
				two_e_sum -= 2*two_e_int[n]
			}
		}
	}

	//Obtain the HF Energy by summing all the terms
	double E_HF = E_NN + 2 * one_e_sum + two_e_sum;

	return E_HF;
}
