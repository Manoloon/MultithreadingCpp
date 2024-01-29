# Testing Async policies
- async : running this code on async as option : execute the task on a different thread than main, then called the get() and then shows the result.
- deferred : on deferred run the task with main thread id but first called the get() and then execute the task (which could lead to undefined behavior) , then show results
- default : and without selecting an option it execute first the task with a different id than main, then called get() and show results.

# use async launch when :
- the task must execute on a separate thread
- the task must start right away.
- the task will use a thread-local storage
- the task function must be execute, even if get() is not called
- the thread receiving the future will call wait_for() or wait_until()
# use the deferred launch when :
- the task must be run in the thread which calls get()
- the task must be executed, even if no more threads can be created
- Want lazy execution of the task
# Otherwise, let the implementation choose.