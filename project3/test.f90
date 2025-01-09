PROGRAM test
        USE MD_functions

        IMPLICIT NONE

        CHARACTER(len=100) :: input_file
        INTEGER :: Natoms, i
        DOUBLE PRECISION, ALLOCATABLE :: coord(:,:), mass(:), distances(:,:)

        input_file = 'inp.txt'
        Natoms = read_Natoms(input_file)

        WRITE(*,*) 'Number of atoms: ', Natoms

        !Allocate coord and mass arrays
        ALLOCATE(coord(Natoms,3)) 
        ALLOCATE(mass(Natoms))

        CALL read_molecule(input_file, Natoms, coord, mass)
        
        WRITE(*,*) 'Read coordinates and masses:'
        DO i=1,Natoms
                WRITE(*,*) coord(i,1), coord(i,2), coord(i,3), mass
        END DO

        !Allocate distance matrix
        ALLOCATE(distances(Natoms, Natoms))
        CALL compute_distances(Natoms, coord, distances)

        WRITE(*,*) 'Distance Matrix:'
        DO i=1,Natoms
                WRITE(*,*) distances(i,:)
        END DO        

END PROGRAM
