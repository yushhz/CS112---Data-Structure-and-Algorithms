1. What is the purpose of object oriented programming?

Ans: OOP organizes code around objects (data + behavior bundled together) rather than separate functions and logic, making programs easier to design, maintain, and reuse by using principles like encapsulation (hiding data), inheritance (reusing/extending code), polymorphism (flexible behavior via a common interface), and abstraction (hiding complexity behind simple interfaces).

2. How do you instantiate an abstract class?

ans: You can't instantiate an abstract class directly—you must create a derived class that overrides all its pure virtual functions, then instantiate that derived class instead.

3. What will you do if a runtime erro is thrown in a try block?

Ans: If a runtime error is thrown in a try block, it should be caught by a matching catch block, which handles the exception (e.g., logs it, displays an error message, or takes corrective action) so the program can continue running or exit gracefully instead of crashing.

Code Example:

try {
int result = 10 / 0; // throws an error
} catch (exception &e) {
cout << "Error occurred: " << e.what() << endl;
}

4. What does the new keyword do in C++?

Ans: The new keyword dynamically allocates memory on the heap at runtime for a variable or object and returns a pointer to that memory, which must later be freed manually using delete to avoid memory leaks.

5. What is the main difference between static and dynamic arrays?

Ans:
Static array: Size is fixed at compile time, stored on the stack, and cannot be resized during program execution.

Dynamic array: Size is determined at runtime (allocated on the heap using new), and can be resized or allocated as needed during program execution, but must be manually deallocated using delete[].
