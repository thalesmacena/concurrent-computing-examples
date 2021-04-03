# Benchmark

The benchmark is made using the two programs contained in that folder. The performance gain (acceleration) obtained is calculated by the following formula: `Tsequential / Tconcurrent`. Where `Tsequential` is the execution time of the sequential algorithm and `Tconcurrent` is defined by the equation `ts + tp(P)` where `ts` is the time of the sequential part of the program (which will not be divided between threads) and `tp(P)` is the time of the parallel part of the program using `P` processors.

## Matrix 500x500

### Sequencial 
Total time os execution is 0.8086883 seconds

### Concurrent
N# Threads | Data Init | Thread Execution | Data Free | Total
--- | --- | --- | --- | ---
**1** | 0.0022917s | 0.6588997s | 0.0001507s | 0.6613421s
**2** | 0.0022530s | 0.3727306s | 0.0001731s | 0.3751567s
**4** | 0.0022480s | 0.3092350s | 0.0001582s | 0.3116412s

### Performance gain
N# Threads | Sequential | Concurrent | gain
--- | --- | --- | --- | ---
**1** | 0.8086883s | 0.6613421s | ~1.223 
**2** | 0.8086883s | 0.3751567s | ~2.156
**4** | 0.8086883s | 0.3116412s | ~2.595

## Matrix 1000x1000

### Sequencial 
Total time os execution is 6.6071820 seconds

### Concurrent
N# Threads | Data Init | Thread Execution | Data Free | Total
--- | --- | --- | --- | ---
**1** | 0.0070221s | 5.3489130s | 0.0002575s | 5.3561930s
**2** | 0.0069378s | 3.2106170s | 0.0002654s | 3.2178200s
**4** | 0.0070187s | 2.5522740s | 0.0002698s | 2.5595620s

### Performance gain
N# Threads | Sequential | Concurrent | gain
--- | --- | --- | ---
**1** | 6.6071820s | 5.3561930s | ~1.236 
**2** | 6.6071820s | 3.2178200s | ~2.053
**4** | 6.6071820s | 2.5595620s | ~2.581

## Matrix 2000x2000
### Sequencial 
Total time os execution is 51.416380 seconds

### Concurrent
N# Threads | Data Init | Thread Execution | Data Free | Total
--- | --- | --- | ---
**1** | 0.0320750s | 44.408060s | 0.0003312s | 44.440460s
**2** | 0.0220708s | 25.268670s | 0.0004684s | 25.291210s
**4** | 0.0219156s | 25.292510s | 0.0003210s | 25.314740s

### Performance gain
N# Threads | Sequential | Concurrent | gain
--- | --- | --- | ---
**1** | 51.416380s | 44.440460s | ~1.157 
**2** | 51.416380s | 25.291210s | ~2.033
**4** | 51.416380s | 25.314740s | ~2.031

## Conclusion