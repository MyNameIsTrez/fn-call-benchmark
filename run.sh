gcc -O3 -shared libbench.c -o libbench.so
gcc -O3 -rdynamic bench.c -o bench
./bench
