### Basic LRU Impl

``` 
Bash
g++ -std=c++23 main.cpp -o lru && ./lru                                                                                                                                0  4 ms

```

```
Bash

Creating LRU Cache with capacity 2
put(1,1)
put(2,2)
get(1): 1
put(3,3) -- evicts key 2
Evicting key 2
get(2): -1
put(4,4) -- evicts key 1
Evicting key 1
get(1): -1
get(3): 3
get(4): 4
Program ending, destructor frees memory.

```
