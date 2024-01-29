PackagedTasks
# Briefly describe the std::packaged_task class
+ Its a wrapper class that provide higher level of abstraction to run funtors, lambdas and callable objects can be invoke async. The result is return in a form of std::future.
# Write a program which creates a packaged_task. The packaged_task's callable object member will take two int arguments and add them together.
# Imagine you want to create a container whose elements are runnable threads
# Which class would you use for the elements?
+ Packaged_tasks are a good choice for this because the thread objects can start running whenever you need given a better choice than threads,as these run at the time they are created.