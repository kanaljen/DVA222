## Assignment 1 - The N-Puzzle

<img align="right" src="http://www.danielhedin.net/dva222/lab1/resources/npuzzle.png">

The N-Puzzle is a sliding puzzle that consists of a frame of numbered square tiles in random order with one tile missing. The object of the puzzle is to place the tiles in order (see image) by making sliding moves that use the empty space.

### Your task

In this assignment, you are asked to design a set of C# classes to represent an N-Puzzle game, where N is a perfect square (16, 25, 36, ...). Use the designed set of classes to develop a playable game with a simple console user interface. The player initially starts with a shuffled board and uses the keyboard to move the empty space up, down, left or right if applicable.

There are many different ways this assignment can be solved with different merits. It is important that you are able to discuss your solution with respect to the different design concepts of the course.

### Steps

To complete this assignment follow the steps below.

1. Design a class diagram detailing the different classes and their connections. Discuss your design with the assistants.
2. Implement the game based on the design. Revise the design if needed - iteration may be necessary.
3. Demo your game for one of the assistants and get an ok.
4. Send in your solution plus the class diagram on Canvas. Please package it using zip. Even though it may not be your first choice it makes it easier on my end.
5. Await feedback on your solution.

### Resources

You might find the following resources helpful.

* Use your preferred version of **Visual Studio**
* If you want to use a program to draw class diagrams **StarUML** is free (but it will nag you to buy a license).
* To shuffle the board use **Random** class. How can you make sure that the shuffled board is solvable?
* To print the user interface of the game use the **Console** class. If you want color have a look at the **Console.BackgroundColor** and **Console.ForegroundColor** properties.
* To wait for a keypress use the **Console.ReadKey(boolean)** method. The boolean controls whether the pressed key is echoed to the console or not. The returned **ConsoleKeyInfo** has a **Key** property which allows you to check if `UpArrow`, `DownArrow`, `LeftArrow` or `RightArrow` was pressed.
