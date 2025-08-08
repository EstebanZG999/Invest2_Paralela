// paralelo_runtime.c
// Compilar: gcc -fopenmp paralelo_runtime.c -o paralelo_runtime -lm
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

static inline double heavy(long i) {
    long iters = 1000 + (i % 1000);
    double x = 0.0;
    for (long k = 0; k < iters; ++k) {
        x += sin((i + 1) * (k + 1) * 1e-6);
    }
    return x;
}

int main(int argc, char** argv) {
    long N = (argc > 1) ? atol(argv[1]) : 200000;
    int T = (argc > 2) ? atoi(argv[2]) : 4; // hilos
    omp_set_num_threads(T);

    // Alternativamente, también podrías:
    // omp_set_schedule(omp_sched_dynamic, 8);

    double t0 = omp_get_wtime();
    double total = 0.0;

    #pragma omp parallel for schedule(runtime) reduction(+:total)
    for (long i = 0; i < N; ++i) {
        total += heavy(i);
    }

    double t1 = omp_get_wtime();
    omp_sched_t kind; int chunk;
    omp_get_schedule(&kind, &chunk);
    printf("Paralelo runtime: hilos=%d schedule(runtime) (chunk=%d) total=%.6f tiempo=%.3f s\n",
           T, chunk, total, t1 - t0);
    return 0;
}
