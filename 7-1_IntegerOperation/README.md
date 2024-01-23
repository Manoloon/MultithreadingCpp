INTEGER OPERATION AND THREADS
- The Counter++ is need 3 stages, pre-fetch the counter var, do the actual count and then publish it.
- without a mutex that lock the counter variable the threads are data racing about the value store on the L1 cache.
- By adding a mutex we avoid data race by locking the thread while doing the operation and then unlocking it.
- so using this : std::lock_guard dataLck(dataMut); we avoid data race.