 Gemini said

Here is the breakdown of each principle:
**1. Single Responsibility Principle (SRP)**

"A class should have one, and only one, reason to change."

A component should do one thing and do it well. If a class handles both database logic and email notifications, it is "tightly coupled." If the email API changes, you risk breaking the database logic.

    Example: Instead of a User class that saves itself to a database, create a UserRepository for data persistence and a UserService for business logic.

**2. Open/Closed Principle (OCP)**

"Software entities should be open for extension, but closed for modification."

You should be able to add new functionality without touching existing, tested code. This is usually achieved using interfaces or abstract classes.

    Example: If you have a PaymentProcessor, don't use if/else for "CreditCard" or "PayPal." Instead, create a Payment interface and implement new classes for each method.

**3. Liskov Substitution Principle (LSP)**

"Objects of a superclass should be replaceable with objects of its subclasses without breaking the application."

If Class B is a subclass of Class A, you should be able to pass B into any function that expects A without unexpected behavior. This ensures that inheritance hierarchies are logically sound.

    Classic Violation: A Square inheriting from Rectangle. If you set the width and height independently on a Rectangle, it works; if you do it on a Square, you break the mathematical definition of a square.

**4. Interface Segregation Principle (ISP)**

"No client should be forced to depend on methods it does not use."

It is better to have **many specific interfaces** than one general-purpose "fat" interface. In Go, this is why we prefer small interfaces like io.Reader.

    Example: Instead of a Worker interface with Work() and Eat(), split them. A Robot class shouldn't be forced to implement an Eat() method it can't use.

**5. Dependency Inversion Principle (DIP)**

"Depend upon abstractions, not concretions."

High-level modules should not depend on low-level modules; both should depend on interfaces. This "inverts" the control, making your code modular and easy to test with mocks.

    Example: A BookingService shouldn't depend on a MySQLDatabase class. It should depend on a Database interface. This way, you can swap MySQL for PostgreSQL or a Mock DB for testing without changing the service logic.