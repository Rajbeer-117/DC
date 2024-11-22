#include <mpi.h>
#include <stdio.h>
#include <stdlib.h> 

int main(int argc, char *argv[]) {
    int rank, size;
    int data[7] = {1,2,3,4,5,6,7};
    int recv_data;
    double scatter_start_time, scatter_end_time, scatter_time;
    double reduce_start_time, reduce_end_time, reduce_time;

    MPI_Init(&argc, &argv);             
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    if (rank == 0) {
        printf("Original array: ");
        for (int i = 0; i < 4; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
    }

   
    scatter_start_time = MPI_Wtime();
    MPI_Scatter(data, 1, MPI_INT, &recv_data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    scatter_end_time = MPI_Wtime();

    scatter_time = scatter_end_time - scatter_start_time;
    printf("Process %d received value %d\n", rank, recv_data);
    MPI_Barrier(MPI_COMM_WORLD);
    reduce_start_time = MPI_Wtime();
    
    int total_sum;
    MPI_Reduce(&recv_data, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    reduce_end_time = MPI_Wtime();
    reduce_time = reduce_end_time - reduce_start_time;

    double *all_scatter_times = NULL;
    double *all_reduce_times = NULL;
    if (rank == 0) {
        all_scatter_times = (double*) malloc(size * sizeof(double));
        all_reduce_times = (double*) malloc(size * sizeof(double));
    }

    MPI_Gather(&scatter_time, 1, MPI_DOUBLE, all_scatter_times, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Gather(&reduce_time, 1, MPI_DOUBLE, all_reduce_times, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0) {
    
       printf("\nScatter times for each process :\n");
        for (int i = 0; i < size; i++) {
            printf("Process %d - Scatter time: %.6f seconds\n", i, all_reduce_times[i]);
        }
        printf("\nReduce times for each process :\n");
        for (int i = 0; i < size; i++) {
            printf("Process %d - Reduce time: %.6f seconds\n", i, all_scatter_times[i]);
        }


        double average = total_sum / 7.0; 
        printf("\nSum of all values: %d\n", total_sum);
        printf("Average of all values: %.2f\n", average);

        free(all_scatter_times);
        free(all_reduce_times);
    }

    MPI_Finalize(); 
    return 0;
}
