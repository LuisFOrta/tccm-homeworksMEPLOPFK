#include <stdio.h>
#include <stdlib.h>
#include <trexio.h>

//declaration of functions to read specific data from TREXIO Library 
void read_nuclear_repulsion(trexio_t* file);
void read_electron_up_num(trexio_t* file);
void read_mo_data(trexio_t* file, int32_t* mo_num, double** mo_energy);
void read_one_electron_integrals(trexio_t* file, int32_t mo_num, double* core_hamiltonian);
void read_two_electron_integrals(trexio_t* file, int64_t* n_integrals, int32_t** index, double** value);


int main() {
    //Variable to store the return code from TREXIO functions.
    trexio_exit_code rc;
    //Open TREXIO file in read mode with an automatic backend detection
    trexio_t* file = trexio_open("c2h2.h5", 'r', TREXIO_AUTO, &rc);
    // Check if the file was opened successfully
    if (rc != TREXIO_SUCCESS) {
        printf("Error opening file.\n");
        return 1; //Exit the program with an error code if the file cannot be opened
    }
// Read the nuclear repulsion energy from the TREXIO file
    read_nuclear_repulsion(file);
// Read the number of spin-up electrons from the TREXIO file
    read_electron_up_num(file);
// Declare variables to store molecular orbital (MO) data
    int32_t mo_num;   // Number of molecular orbitals
    double* mo_energy; // Array to store MO energies
    
    //Read the number of MOs and their energies
    read_mo_data(file, &mo_num, &mo_energy);
    // allocate memory for core Hamiltonian matrix 
    double* core_hamiltonian = malloc(mo_num * mo_num * sizeof(double));
    // Read one-electron integrals (core Hamiltonian) from TREXIO
    read_one_electron_integrals(file, mo_num, core_hamiltonian);
    //Print core hamiltonian                                                      TESTLINES
    printf("Core Hamiltonian: \n");
    printf("%f %f \n", *core_hamiltonian, *(core_hamiltonian + (mo_num*8 + 8)));
    // Free the memory allocated for the core hamiltonian
    free(core_hamiltonian);
// Declaring variables to store two-electron integral data
    int64_t n_integrals; //Number of non-zero two-electron integrals
    int32_t* index;     // Array to store indices of the integrals
    double* value;     // Array to store values of the integrals
    // Read two-electron integrals from the TREXIO file
    read_two_electron_integrals(file, &n_integrals, &index, &value);
    // Print values stored                                                        TESTLINES
    //int32_t n = 38;
    printf("Number of two electron integrals: %ld \n", n_integrals);
    
    for (int n = 0; n < n_integrals; n++){
	if (index[4*n]==1 && index[4*n+1]==0 && index[4*n+2]==1 && index[4*n+3]==0){
    		printf("Indeces %d: %d %d %d %d \n", n, index[4*n], index[4*n+1], index[4*n+2], index[4*n+3]);
        	printf("Value: %f \n", value[n]);
	} else if (index[4*n]==1 && index[4*n+1]==1 && index[4*n+2]==0 && index[4*n+3]==0){
    		printf("Indeces %d: %d %d %d %d \n", n, index[4*n], index[4*n+1], index[4*n+2], index[4*n+3]);
        	printf("Value: %f \n", value[n]);

	}
    }
    //printf("Value: %f \n", value[n]);
    
    // Free the memory allocated for the two-electron integrals
    free(index);
    free(value);
    // Free the memory allocated for molecular orbital energies
    free(mo_energy);
// Close the TREXIO file to release resources
    trexio_close(file);
//exit
    return 0;
}