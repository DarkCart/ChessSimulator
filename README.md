# Chess Simulator
My console-based chess simulator, parses PGN files and prints each board position to the console.

Uses ANSI for coloring, should work on Windows 10 but no promises. It works on Linux, at least, and presumably Mac OS as well.

All written in standard C++ with no external libraries for PGN parsing/simulation/display.

### Screenshot
![ss1](https://darkcart.co/chess_example_wip.png)

*Fig. 1: The final move of Garry Kasparov's final game against Deep Blue in 1997, which he lost, inching us just that-much-closer to Skynet's creation.*

### Building
Obviously this project originally targeted Windows, but I did 90% of the development on Linux with `g++`. You should just be able to type something like
`g++ *.cpp -o csim` to build it.
