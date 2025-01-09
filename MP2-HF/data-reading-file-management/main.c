#include <stdio.h>
#include <stdlib.h>
#include <trexio.h>

int main() {
    trexio_exit_code rc;
    trexio_t* file = trexio_open("sample_data.trexio", 'r', TREXIO_AUTO, &rc);

    if (rc != TREXIO_SUCCESS) {
        printf("Error opening file.\n");
        return 1;
    }

    read_nuclear_repulsion(file);
    read_electron_up_num(file);

    int32_t mo_num;
    double* mo_energy;
    read_mo_data(file, &mo_num, &mo_energy);

    double* core_hamiltonian = malloc(mo_num * mo_num * sizeof(double));
    read_one_electron_integrals(file, mo_num, core_hamiltonian);
    free(core_hamiltonian);

    int64_t n_integrals;
    int32_t* index;
    double* value;
    read_two_electron_integrals(file, &n_integrals, &index, &value);
    free(index);
    free(value);

    free(mo_energy);
    trexio_close(file);

    return 0;
}
