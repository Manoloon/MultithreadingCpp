# Threads pool
- when a thread is created it has a huge overhead, it would take 10000 times as long as calling the function directly.
- This is because when a thread is created it lead to this tasks : 
    - Create an execution task for the thread
    - call system API
    - the OS must create the internal data to manage the thread.
    - the scheduler must execute the thread
    - a context switch occurs to run the thread.
- So to avoid this, a thread pool is create.
    - its a fixed size container of thread objects
    - And a queue of tasks (functions objects)
- The advantage of using thread pools are easy to scaling and efficient uses of resources.
# Things to improve on this implementation
- This thread pool handle only functions without arguments, to fix this we can use std::packaged_task
- 