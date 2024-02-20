In order to execute this program, you must compile and link all 3 program files, main.cpp, forwardchaining.cpp, and backwardchaining.cpp. Here are the commands:

# Compile each file separately
g++ -c main.cpp -o main.o
g++ -c backwardchaining.cpp -o backwardchaining.o
g++ -c forwardchaining.cpp -o forwardchaining.o

# Link the object files to create the executable
g++ main.o backwardchaining.o forwardchaining.o -o myprogram

# Execute the program
./myprogram

#NOTE: when prompted to enter a conclusion for Backward chaining, type "ATTACK" as that is the variable you want to identify. For forward chaining, type "PREVENTION", as you are trying to find a prevention