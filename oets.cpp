/**
 * @file oets.cpp
 * @author Dinara Garipova (xgarip00)
 * @brief Odd-Even Transposition Sort using MPI (PRL Project 1)
 * @date 2025-04-02
 */
#include <iostream>
#include <fstream>
#include <mpi.h>

/**  @brief Exchanges values between the current process and its neighbor.
 *   Keeps either the smaller or larger value based on the `keepMin` flag.
 *   @param number Local value of the current process (modified in place)
 *   @param partnerRank MPI rank of the neighbor process
 *   @param keepMin If true, keep the smaller value; otherwise, keep the larger
 */

void compareAndSwap(int& number, int partnerRank, bool keepMin) {
    int neighbour;
    MPI_Status status;

    MPI_Sendrecv(&number, 1, MPI_INT, partnerRank, 0,&neighbour, 1, MPI_INT, partnerRank, 0,MPI_COMM_WORLD, &status);

    if ((keepMin && neighbour < number) ||
        (!keepMin && neighbour > number)) {
        number = neighbour;
    }
}

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Total number of processes

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Unique ID of this process

    // Open binary input file
    std::ifstream infile("numbers", std::ios::binary);
    if (!infile.is_open()) {
        std::cerr << "Error: file didn't open!" << std::endl;
        return 1;
    }
    
    // Read one byte from the file at position equal to the process rank
    unsigned char byte;
    infile.seekg(rank,std::ios_base::beg);
    infile.read(reinterpret_cast<char*>(&byte), 1);
    int number = static_cast<int>(byte); // Convert to int for sorting

    // Print the original (unsorted) sequence on a single line
    for (int i = 0; i < size; i++) {
        if (rank == i && i != size -1) {
            std::cout << number << " " ;
        }
        else if (rank == i && i == size - 1){
            std::cout << number << std::endl;
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    
     // Perform odd-even transposition sort
    for (int phase = 1; phase < size + 1; phase++){
        if (phase % 2 == 0){
            if (rank % 2 == 0 && (rank + 1 < size)){
                compareAndSwap(number, rank + 1, true);
            }
            else if (rank % 2 == 1)
            {
                compareAndSwap(number, rank - 1, false);
            }   
        }
        else{
            if (rank % 2 == 1 && (rank + 1 < size)){
                compareAndSwap(number, rank + 1, true);
            }
            else if (rank % 2 == 0 && (rank > 0))
            {
                compareAndSwap(number, rank - 1, false);
            }  
        }
    }

    // Print the final sorted sequence (one number per line)
    for (int i = 0; i < size; i++) {
        if (rank == i) {
            std::cout << number << std::endl;
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    
    // Finalize MPI
    MPI_Finalize();
    return 0;
}