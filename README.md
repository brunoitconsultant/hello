##  RUN IN BASH
### > GET SOURCES
git clone https://github.com/brunoitconsultant/words.git ~/words ; cd ~/words

### > COMPILE CODE
clear ; make clear ; make -s ; ./words

### > DEBUG CODE (using GDB)
#### 1. Starting & Exiting

- ***gdb ./program***: Launches GDB with your compiled executable (must be compiled with -g).
- ***run (or r)***: Starts executing the program from the beginning until it hits a breakpoint or finishes.
- ***quit (or q)***: Exits GDB and returns to your terminal.

#### 2. Breakpoints

- ***break func_name (or b func_name)***: Sets a pause point at the start of a specific function (e.g., b tokenize).
- ***break 92 (or b 92)***: Sets a pause point at line 92 in the current file.
- ***break file.c:92***: Sets a pause point at line 92 in a specific source file.
- ***info breakpoints (or i b)***: Lists all active breakpoints with their ID numbers and line locations.
- ***delete 1 (or d 1)***: Deletes breakpoint number 1.
- ***delete***: Deletes all active breakpoints.

#### 3. Stepping & Execution Control

- ***next (or n)***: Executes the current line of code and steps over function calls to the next line.
- ***step (or s)***: Steps inside a function call on the current line to debug it line by line.
- ***finish***: Runs until the current function finishes and returns to its caller.
- ***continue (or c)***: Resumes normal program execution until the next breakpoint is hit.
- ***Enter (blank line)***: Repeats the previous command (ideal for stepping through loops repeatedly with n).

#### 4. Viewing Source Code

- ***lay next***: Another way to display the source in assembly (press Enter to display source in c too).
- ***ref***: Refreshes the screen in case the text shows all scrambled.
- ***list (or l)***: Displays 10 lines of source code centered around your current pause location.
- ***list 80,100***: Displays lines 80 through 100 of your source file.
- ***tui enable / tui disable***: Toggles GDB's built-in split-screen Terminal UI showing your live source code above the command prompt.

#### 5. Inspecting Variables & Arrays

- ***info locals***: Displays the current values of all local variables in the active function.
- ***print var (or p var)***: Prints the value of a variable (e.g., p prev).
- ***print/x var***: Prints a variable's value in hexadecimal.
- ***print &var***: Prints the exact RAM memory address where a variable is stored.
- ***display var***: Automatically prints var after every single step (next or step).
- ***undisplay 1***: Stops auto-displaying item number 1.
- ***print arr@10***: Prints the first 10 elements of a 1D array (or the first 10 rows of a 2D array).
- ***set print pretty on***: Formats multi-dimensional arrays and structs across indented lines for readability.
- ***set print repeats 3***: Collapses long sequences of identical array values into <repeats N times>.

#### 6. Examining Raw Memory (x Command)

The syntax is ***`x/<count><format><size> <address>`***:
- Formats: x (hex), d (signed decimal), u (unsigned decimal), c (char), s (string).
- Sizes: b (byte = 1 byte), h (halfword = 2 bytes / short), w (word = 4 bytes / int), g (giant = 8 bytes / long).
Common Examples:
- ***x/16xb &prev***: Dumps 16 raw bytes in hexadecimal starting at prev's memory address.
- x/12hu token: Dumps the first 12 unsigned short values in decimal from the token array.
- x/s input: Reads and prints input as a null-terminated C string.
