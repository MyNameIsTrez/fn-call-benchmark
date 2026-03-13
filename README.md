# fn call benchmark

For grug, we wanted to compare the overhead of calling a fn pointer from the executable in a shared library, compared to linking against the fn dynamically using `-rdynamic`.

It turns out that calling the function directly using `-rdynamic` is roughly 2.5x faster for 1 billion calls of `void bar(void) { counter++; }`:
```
$ bash run.sh
direct: 2.436099 s (counter=1000000000)
fn ptr: 0.981680 s (counter=1000000000)
```
