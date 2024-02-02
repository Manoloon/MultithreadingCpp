# Data structure Safety Guarantee
## A data structure is accessed by two threads concurrently
### For each of these scenarios, state whether there is a potential data race
- Thread A writes to the first element of a linked list and thread B reads the second element
  - I dont see data race here.
- Thread A removes the first element of a single-linked list and thread B reads the second element
  - No data race. Removing a node does not affect the data in a different node
- Thread A removes the second element of a double-linked list and thread B reads the first element
  - No data race.
- Thread A removes the first element of a single-linked list and thread B removes the second element
  - Data Race, B will need to read first before get to the second and that lead to an invalid memory read.
- Thread A removes the second element of a double-linked list and thread B removes the first element
  - data race. Thread A needs to read first element before getting to the second.
- Thread A removes the second element of a double-linked list and thread B removes the fifth element
  - no data race, removing a node only affects its immediate neighbours.

- When two threads can access the same STL container object, what guarantees do we have?
  - its safe for the threads to concurrently access the object, and ensure that they do not modify it.
  - its safe for one thread to modify the object, meanwhile no other threads access the object concurrently.
  - Depending of the container , it may be safe to make concurrent modifications to different parts of the object.
# "coarse-grained" locking
- What is meant by "coarse-grained" locking?
  - Any thread that accesses an element of the object must Lock the entire memory object.
- What are the advantages of coarse-grained locking?
  - no chance to have data race.
  - Require zero change to the code.
- What are the disadvantages of coarse-grained locking?
  - Concurrency and parallelism go out the window.
  - turn the whole task single threaded.
# "fine-grained" locking
- What is meant by "fine-grained" locking?
  - Choose which part of the object to lock.
- What are the advantages of fine-grained locking?
  - Allows concurrent access to the data. 
- What are the disadvantages of fine-grained locking?
  - Require extra code.
  - Require careful design
  - Its add overhead by using mutex.