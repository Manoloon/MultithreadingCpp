Lock-free Programming
# Why does the constructor create an element which is not used for anything?
+ We need to create an object so the head and tail are not pointing to the same item inside
# Explain why the data race occurs
+ Both iterators (iHead and iTails) are being accessed by differents threads
# Can the race condition be avoided by using atomic variables?
+ No, because both (iHead and iTails) are not trivial objects. Remember that only trivial objects (int,char,float, T*) can be atomics