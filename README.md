# ChessGame

A functional game of chess made with Qt. Completed in the context of our final project for an OOP class (INF1015, H2021) at Polytechnique Montréal. This project is meant to sum up the most important and fundamental concepts of the course content. 

---

### Inheritance
Inheritance in our project helps to organize our code in a comprehensive manner, and it helps us respect the DRY principles in many cases. 

Some example of how inheritancce is used in this project :
* Each **type of piece** (Pawn, King, Bishop, ...) is a **piece** ; therefore, it inherits from a 'Piece' class containg common attribute, like color, or common functions.
* A **queen** is a type of piece that inherits the movements of both a **bishop** and a **rook**.


### Abstract Classes and Virtual Methods 
Abstract Classes encapsulate certain general aspects of how we want the program to work. These abstract classes declare virtual methods that are overriden in the objects that we want to treat. This ensure that the right operations will be done on the object that we want to manipulate.

Some example of how these concepts are used in this project :
* An abstract class dedicated to the **logic** of our game, named *ClasseVirtuelleLogique*, contains a pure virtual function, named *calculerMouvements()*, that is meant to find which movements are possible for a type of chess piece on a board with other pieces on it. The virtual function is then **overriden** in each class that represents a type of piece.
* An abstract class dedicated to the **UI** of our game, named *ClasseVirtuelleUI*, declares a pure virtual function, named *obtenirImage()*, that associates an image to each piece that is on the board. This function is then **overriden** in the classes for the types of pieces according it's color.


### Static variables and Thrown Exceptions

* A static varibale that **counts the number of instances** of a king is used in order to ensure that there are no more than 2 instances of a king on one chessboard. A simple try/catch allows us to throw an exception and delete the last created instance of a king if there were 3 kings on the board.

---

### Below, a snippet of the project in action : 

https://user-images.githubusercontent.com/46169956/117669379-d30b7c00-b174-11eb-8a0e-d7e574741faa.mp4
