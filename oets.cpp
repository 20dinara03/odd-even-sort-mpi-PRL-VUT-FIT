#include <iostream>
#include <fstream>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::ifstream infile("numbers", std::ios::binary);
    if (!infile.is_open()) {
        std::cerr << "Error: file didn't open!" << std::endl;
        return 1;
    }
    
    unsigned char byte;
    infile.seekg(rank,std::ios_base::beg);
    infile.read(reinterpret_cast<char*>(&byte), 1);
    int number = static_cast<int>(byte);
    std::cout << "Hello from processor " << rank;
    std::cout << " my number is  " << number << std::endl;
    return 0;
}