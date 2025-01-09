// data_reader.c
#include <stdio.h>
#include <stdlib.h>
#include <trexio.h>
#include <reader_data.h>

void read_nuclear_repulsion(trexio_t* file) {
    double energy;
    if (trexio_read_nucleus_repulsion(file, &energy) != TREXIO_SUCCESS) {
        printf("Error reading nuclear repulsion energy.\n");
        exit(1);
    }
    printf("Nuclear Repulsion Energy: %f\n", energy);
}

void read_electron_up_num(trexio_t* file) {
    int32_t n_up;
    if (trexio_read_electron_up_num(file, &n_up) != TREXIO_SUCCESS) {
        printf("Error reading number of occupied orbitals.\n");
        exit(1);
    }
    printf("Number of Occupied Orbitals: %d\n", n_up);
}

void read_mo_data(trexio_t* file, int32_t* mo_num, double** mo_energy) {
    if (trexio_read_mo_num(file, mo_num) != TREXIO_SUCCESS) {
        printf("Error reading molecular orbitals number.\n");
        exit(1);
    }

    *mo_energy = malloc(*mo_num * sizeof(double));
    if (*mo_energy == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    if (trexio_read_mo_energy(file, *mo_energy) != TREXIO_SUCCESS) {
        printf("Error reading molecular orbital energies.\n");
        exit(1);
    }
}

void read_one_electron_integrals(trexio_t* file, int32_t mo_num, double* core_hamiltonian) {
    if (trexio_read_mo_1e_int_core_hamiltonian(file, core_hamiltonian) != TREXIO_SUCCESS) {
        printf("Error reading core Hamiltonian.\n");
        exit(1);
    }
}

void read_two_electron_integrals(trexio_t* file, int64_t* n_integrals, int32_t* index, double* value) {
    if (trexio_read_mo_2e_int_eri_size(file, n_integrals) != TREXIO_SUCCESS) {
        printf("Error reading two-electron integrals size.\n");
        exit(1);
    }

    *index = malloc(4 * (*n_integrals) * sizeof(int32_t));
    *value = malloc((*n_integrals) * sizeof(double));

    if (*index == NULL || *value == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    if (trexio_read_mo_2e_int_eri(file, 0, n_integrals, *index, *value) != TREXIO_SUCCESS) {
        printf("Error reading two-electron integrals.\n");
        exit(1);
    }
}
