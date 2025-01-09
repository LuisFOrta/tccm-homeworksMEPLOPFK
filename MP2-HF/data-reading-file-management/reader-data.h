// data_reader.h
#ifndef DATA_READER_H
#define DATA_READER_H

#include <trexio.h>

void read_nuclear_repulsion(trexio_t* file);
void read_electron_up_num(trexio_t* file);
void read_mo_data(trexio_t* file, int32_t* mo_num, double** mo_energy);
void read_one_electron_integrals(trexio_t* file, int32_t mo_num, double* core_hamiltonian);
void read_two_electron_integrals(trexio_t* file, int64_t* n_integrals, int32_t* index, double* value);

#endif
