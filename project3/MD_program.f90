PROGRAM MD_program
    USE MD_functions
    IMPLICIT NONE

    INTEGER :: Natoms
    DOUBLE PRECISION, ALLOCATABLE :: coord(:, :), mass(:), distance(:, :)
    CHARACTER(len=100) :: input_file
    DOUBLE PRECISION :: epsilon, sigma, V_tot
    DOUBLE PRECISION, ALLOCATABLE :: velocity(:, :)
    DOUBLE PRECISION :: total_kinetic_energy

    ! Initialize parameters
    input_file = "inp.txt"   ! Replace with your actual input file
    epsilon = 0.01                 ! Example Lennard-Jones epsilon parameter
    sigma = 3.4                    ! Example Lennard-Jones sigma parameter

    ! Read the number of atoms
    Natoms = read_Natoms(input_file)
    PRINT *, "Number of atoms:", Natoms

    ! Allocate arrays based on number of atoms
    ALLOCATE(coord(Natoms, 3), mass(Natoms), distance(Natoms, Natoms), velocity(Natoms, 3))

    ! Read molecule data
    CALL read_molecule(input_file, Natoms, coord, mass)

    ! Compute distances
    CALL compute_distances(Natoms, coord, distance)

    ! Compute potential energy
    V_tot = V(epsilon, sigma, Natoms, distance)
    PRINT *, "Potential energy:", V_tot

    ! Example: Initialize velocities and compute kinetic energy
    velocity = 0.01  ! Replace with actual velocity initialization
    total_kinetic_energy = T(Natoms, velocity, mass)
    PRINT *, "Total kinetic energy:", total_kinetic_energy

    ! Deallocate arrays
    DEALLOCATE(coord, mass, distance, velocity)
END PROGRAM MD_program
