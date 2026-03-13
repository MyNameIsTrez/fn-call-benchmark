#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <dlfcn.h>

#define N 1000000000

typedef void (*call_bar_direct_fn)(uint64_t);
typedef void (*call_bar_ptr_fn)(uint64_t, void (*)(void));

volatile uint64_t counter = 0;

void bar(void) {
    counter++;
}

static double get_elapsed_seconds(struct timespec start, struct timespec end) {
    return (double)(end.tv_sec - start.tv_sec) + 1.0e-9 * (double)(end.tv_nsec - start.tv_nsec);
}

int main() {
    void *handle = dlopen("./libbench.so", RTLD_NOW);
    if (!handle) {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
        return 1;
    }

    call_bar_direct_fn call_bar_direct =
        (call_bar_direct_fn)dlsym(handle, "call_bar_direct");

    call_bar_ptr_fn call_bar_ptr =
        (call_bar_ptr_fn)dlsym(handle, "call_bar_ptr");

    if (!call_bar_direct || !call_bar_ptr) {
        fprintf(stderr, "dlsym failed\n");
        return 1;
    }

    struct timespec start, end;

    counter = 0;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    call_bar_direct(N);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    printf("direct: %.6f s (counter=%lu)\n",
           get_elapsed_seconds(start, end), counter);

    counter = 0;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    call_bar_ptr(N, bar);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    printf("fn ptr: %.6f s (counter=%lu)\n",
           get_elapsed_seconds(start, end), counter);
}
