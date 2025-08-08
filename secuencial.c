// secuencial.c
// Compilar: gcc secuencial.c -o secuencial -lm
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

static inline double heavy(long i) {
    // Trabajo variable: ~1000..1999 iteraciones de sin()
    long iters = 1000 + (i % 1000);
    double x = 0.0;
    for (long k = 0; k < iters; ++k) {
        x += sin((i + 1) * (k + 1) * 1e-6);
    }
    return x;
}

int main(int argc, char** argv) {
    long N = (argc > 1) ? atol(argv[1]) : 200000;
    clock_t t0 = clock();
    double total = 0.0;
    for (long i = 0; i < N; ++i) {
        total += heavy(i);
    }
    clock_t t1 = clock();
    double secs = (double)(t1 - t0) / CLOCKS_PER_SEC;
    printf("Secuencial: total=%.6f tiempo=%.3f s\n", total, secs);
    return 0;
}
