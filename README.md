# ChessGame

A functional game of chess made with Qt. Completed in the context of our final project for an OOP class (INF1015, H2021) at Polytechnique Montréal. This project is meant to sum up the most important and fundamental concepts of the course content. 

### Inheritance

* Each type of piece (Pawn, King, Bishop, ...) inherits from a 'Piece' class.
* A queen inherits of the movements of both a bishop and a rook.

### Virtual Methods and Abstract Classes
Virtual methods and abstract classes set the foundation for the logic of the game. Here are some example of how they are used in this project :

* each piece has a method to determine where it can move, and this method is different depending a=on how each piece travels along the board.  

### Static variables and Thrown Exceptions

* a static varibale to count the number of instances of a king was created in order to ensure that there were no more than 2 instances of a king on one chessboard.

##### Below, a snippet of the project in action : 

https://user-images.githubusercontent.com/46169956/117669379-d30b7c00-b174-11eb-8a0e-d7e574741faa.mp4
