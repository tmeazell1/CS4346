In order to execute this program, you must compile and link all 3 program files, main.cpp, forwardchaining.cpp, and backwardchaining.cpp. Here are the commands:

# Compile each file separately
g++ -c main.cpp -o main.o
g++ -c backwardschaining.cpp -o backwardschaining.o
g++ -c forwardschaining.cpp -o forwardschaining.o

# Link the object files to create the executable
g++ main.o backwardschaining.o forwardschaining.o -o myprogram

# Execute the program
./myprogram