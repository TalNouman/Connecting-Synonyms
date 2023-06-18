# Connecting-Synonyms


Connecting-Synonyms is a multithreaded C++ program that reads input files and finds synonyms based on the word pairs present in the files. It groups the synonyms together and outputs the results to a file.

## Requirements

- C++ compiler with C++11 support
- CMake (for building the program)

## Usage

Run the program by executing the generated binary. The program requires three input files containing word pairs separated by an equals sign ('='). Each pair should be on a new line. For example:
apple=fruit
car=vehicle

To run the program, provide the paths to the input files as command-line arguments:
./Connecting_Synonyms input1.txt input2.txt input3.txt

The program will process the files concurrently using three threads. Once the processing is complete, the resulting synonym groups will be saved to an output file called "result.txt" in the same directory.

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgements

The Connecting-Synonyms program was developed by me as a sample project.


