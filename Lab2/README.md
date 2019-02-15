# Assignment 2 - Bounce!
In order to practice concept of Inheritance and its related topics, we are going to create a simple graphical application that only consists of circles, lines and boxes. The idea is to have several moving balls (drawn as simple circles) and several stationary boxes that can affect the moving balls.

You will be given a small skeleton C# solution as a starting point. The solution should work under Windows, Mac OS X and Linux. It uses Windows Forms to provide the graphics.
<img src="http://www.danielhedin.net/dva222/lab2/resources/Bounce.png">

The above image shows different objects that will be added to the program and will be visible to the user. Your program must look like this when done. Of course it will also have some moving balls that move around.

1. As you can see there are 2 types of lines: Vertical lines (yellow) and Horizontal lines (green). Vertical lines reflect the ball back by changing their X-speed. Horizontal lines reflect it by changing the Y-speed.
2. The red boxes are SpeedUp Boxes. They allow the balls to pass through them but meanwhile increase their speed. The direction of the ball does not change while moving through them.
3. The blue boxes are SpeedDown Boxes. They allow the balls to pass through them but meanwhile decrease their speed. The direction of the ball does not change while moving through them.

### Steps

To complete this assignment follow the steps below.

1. Download and run the skeleton C# solution. It should draw some moving balls. WARNING: the first start on MacOS takes about a minute before the window shows. I have no idea why...
2. Read the code. Analyze the design and implementation.
3. Design a class diagram detailing the different classes and their connections. Discuss your design with the assistants.
4. Implement the assignment based on the design. Revise the design if needed - iteration may be necessary.
5. Demo your solution for one of the assistants and get an ok.
6. Send in your solution plus the class diagram on Canvas. Please package it using zip. Even though it may not be your first choice it makes it easier on my end.
7. Await feedback on your solution.

### Resources

You might find the following resources helpful.

* Use your preferred version of Visual Studio
* If you want to use a program to draw class diagrams StarUML is free (but it will nag you to buy a license).
* See the Graphics Class for more information on the drawing primitives.
* For information on collision detection you can have a look at Circle/Rectangle intersection and Circle/Line intersection.
