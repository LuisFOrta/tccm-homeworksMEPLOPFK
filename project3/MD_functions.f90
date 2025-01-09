MODULE MD_functions
    IMPLICIT NONE

    CONTAINS

    INTEGER FUNCTION read_Natoms(input_file) RESULT(Natoms)
        IMPLICIT NONE
        CHARACTER(len=*), INTENT(IN) :: input_file

        ! Open input file in read mode
        OPEN(unit=1, file=input_file, action='read', status='old', form='formatted')
        READ(1, *) Natoms ! Read first line, and store number of atoms in Natoms
        CLOSE(unit=1) ! Close file after reading
    END FUNCTION read_Natoms

    ! Subroutine to get coordinates and masses of the input molecule
    SUBROUTINE read_molecule(input_file, Natoms, coord, mass)
        IMPLICIT NONE
        CHARACTER(len=*), INTENT(IN) :: input_file
        INTEGER, INTENT(IN) :: Natoms
        DOUBLE PRECISION, INTENT(OUT) :: coord(Natoms, 3)
        DOUBLE PRECISION, INTENT(OUT) :: mass(Natoms)
        INTEGER :: i

        ! Open input file in read mode
        OPEN(unit=1, file=input_file, action='read', status='old', form='formatted')
        READ(1, *) ! Read first line to skip it

        ! Iterate over the lines of the file and store the coordinates and masses
        DO i = 1, Natoms
            READ(1, *) coord(i, 1), coord(i, 2), coord(i, 3), mass(i)
        END DO
        CLOSE(unit=1) ! Close file after reading
    END SUBROUTINE read_molecule

    ! Subroutine to get a distance matrix between atoms
    SUBROUTINE compute_distances(Natoms, coord, distance)
        IMPLICIT NONE
        INTEGER, INTENT(IN) :: Natoms
        DOUBLE PRECISION, INTENT(IN) :: coord(Natoms, 3)
        DOUBLE PRECISION, INTENT(OUT) :: distance(Natoms, Natoms)
        INTEGER :: i, j

        DO i = 1, Natoms
            DO j = 1, Natoms
                distance(i, j) = SQRT((coord(i, 1) - coord(j, 1))**2 &
                                     + (coord(i, 2) - coord(j, 2))**2 &
                                     + (coord(i, 3) - coord(j, 3))**2)
            END DO
        END DO
    END SUBROUTINE compute_distances

    DOUBLE PRECISION FUNCTION V(epsilon, sigma, Natoms, distance) RESULT(V_tot)
        IMPLICIT NONE
        DOUBLE PRECISION, INTENT(IN) :: epsilon, sigma
        INTEGER, INTENT(IN) :: Natoms
        DOUBLE PRECISION, INTENT(IN) :: distance(Natoms, Natoms)
        DOUBLE PRECISION, PARAMETER :: zero = 0.0
        INTEGER :: i, j

        ! Initialize V_total to zero
        V_tot = zero

        ! Iterate over all pairs of atoms and add each contribution to V_tot
        DO i = 1, Natoms
            DO j = 1, Natoms
                IF (j .gt. i) THEN
                    V_tot = V_tot &
                        + 4 * epsilon * ((sigma / distance(i, j))**12 - (sigma / distance(i, j))**6)
                END IF
            END DO
        END DO
    END FUNCTION V

    DOUBLE PRECISION FUNCTION T(Natoms, velocity, mass) RESULT(total_kinetic_energy)
        IMPLICIT NONE
        INTEGER, INTENT(IN) :: Natoms
        DOUBLE PRECISION, INTENT(IN) :: velocity(Natoms, 3)
        DOUBLE PRECISION, INTENT(IN) :: mass(Natoms)
        INTEGER :: i, j
        DOUBLE PRECISION :: velocity_squared

        ! Initialize the total kinetic energy to zero
        total_kinetic_energy = 0.0d0

        ! Loop over each atom
        DO i = 1, Natoms
            velocity_squared = 0.0d0

            ! Sum the squares of velocity components
            DO j = 1, 3
                velocity_squared = velocity_squared + velocity(i, j)**2
            END DO

            ! Add the kinetic energy of the atom to the total
            total_kinetic_energy = total_kinetic_energy + 0.5d0 * mass(i) * velocity_squared
        END DO
    END FUNCTION T

END MODULE MD_functions
