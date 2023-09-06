#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>

const int MAX = 100;
const int BLOCK_SIZE = 16; 

int A[MAX][MAX];
int B[MAX][MAX];
int C[MAX][MAX];

void 
matrix_multiplication_classic(int A[][MAX], int B[][MAX], int C[][MAX]) {
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < MAX; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void 
matrix_multiplication_blocked(int A[][MAX], int B[][MAX], int C[][MAX]) {
    for (int i = 0; i < MAX; i += BLOCK_SIZE) {
        for (int j = 0; j < MAX; j += BLOCK_SIZE) {
            for (int k = 0; k < MAX; k += BLOCK_SIZE) {
                for (int ii = i; ii < std::min(i + BLOCK_SIZE, MAX); ++ii) {
                    for (int jj = j; jj < std::min(j + BLOCK_SIZE, MAX); ++jj) {
                        for (int kk = k; kk < std::min(k + BLOCK_SIZE, MAX); ++kk) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

void 
initialize_random_matrix(int matrix[][MAX], int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = rand() % 100;
        }
    }
}

int 
main() {
    srand(static_cast<unsigned>(time(0)));
    
    initialize_random_matrix(A, MAX);
    initialize_random_matrix(B, MAX);
    
    std::ios_base::sync_with_stdio(false);
    auto start1 = std::chrono::high_resolution_clock::now();

    matrix_multiplication_classic(A, B, C);

    auto end1 = std::chrono::high_resolution_clock::now();
    auto start2 = std::chrono::high_resolution_clock::now();

    matrix_multiplication_blocked(A, B, C);
    
    auto end2 = std::chrono::high_resolution_clock::now();
    
    double time_taken1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1).count();
    double time_taken2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2).count();

    std::cout << "Time taken in first: " << time_taken1 << std::endl;
    std::cout << "Time taken in second: " << time_taken2 << std::endl;
    return 0;
}
