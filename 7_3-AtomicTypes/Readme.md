Atomic Operations
- load() : will load the value of the atomic var.
- store() : will store a given value into the atomic var.
- exchange() : will swap values with other non atomic var.
- std::atomic_flag class : this class function like a bool, it could be use to create an spinlock. if this flag return true this mean that other thread is already using it otherwise it is usable by this thread.
  