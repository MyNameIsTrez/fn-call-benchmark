#include <stdint.h>

extern void bar(void);

void call_bar_direct(uint64_t n) {
    for (uint64_t i = 0; i < n; i++) {
        bar();
    }
}

void call_bar_ptr(uint64_t n, void (*fn)(void)) {
    for (uint64_t i = 0; i < n; i++) {
        fn();
    }
}
