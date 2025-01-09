function T(Natoms, velocity, mass) result(total_kinetic_energy)
    implicit none
    integer, intent(in) :: Natoms
    double precision, intent(in) :: velocity(Natoms, 3)
    double precision, intent(in) :: mass(Natoms)
    double precision :: total_kinetic_energy
    integer :: i, j
    double precision :: velocity_squared

    ! Initialize the total kinetic energy to zero
    total_kinetic_energy = 0.0d0

    ! Loop over each atom
    do i = 1, Natoms
        velocity_squared = 0.0d0

        ! Sum the squares of velocity components
        do j = 1, 3
            velocity_squared = velocity_squared + velocity(i, j)**2
        end do

        ! Add the kinetic energy of the atom to the total
        total_kinetic_energy = total_kinetic_energy + 0.5d0 * mass(i) * velocity_squared
    end do
end function T
