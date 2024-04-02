# Description
Unzipper is a C program that implements a decompression algorithm for a secret compression method. The program consists of two main components:

The Decoding Table: The program reads a series of bytes representing a decoding table, which contains the bit sequences used to represent each character in the compressed file. It then outputs this table in a human-readable format.

Decompressing: The program uses the decoding table to decompress a compressed piece of text and outputs the result.

# Compiling
To compile the program, navigate to the unzipper directory and run the following command:

gcc main.c -o unzipper

This will create an executable named unzipper.

# Running the Program
To run the program, use the following command:

./unzipper


# Input Format
The input consists of the following parts:

A single byte denoting the number of entries T in the decoding table.
T lines, each representing a table entry with the character, the length of the encoding, and the encoding itself.
Four bytes encoding the length of the compressed bitstream.
The compressed bitstream (if present).
Output Format
For Problem 1, the output consists of T lines, each representing a table entry in the format C : L E, where C is the character in hexadecimal, L is the length of the encoding, and E is the binary representation of the encoding.
For Problem 2, if the length of the compressed bitstream is not zero, the program outputs the decompressed text.

# Example
Input:
0x0a
0x21 0x30 0x00

0x57 0x42 0x00

0x48 0x43 0x00

0x6c 0x24 0x00

0x6f 0x38 0x00

0x0a 0x3a 0x00

0x65 0x4c 0x00

0x64 0x4d 0x00

0x20 0x4e 0x00

0x72 0x4f 0x00

0x00 0x00 0x00 0x0e

0x3c 0x59 0xc5 0x3d 0xd1 0x68

Output:
Hello World!

# Author
Arash Tashakori (main.c)
Dr. Alexander Brodsky (tests and idea)

# Acknowledgement
This code is an assignment for CSCI2122 Systems Programming at Dalhousie University. The requirements of this assignment is designed by the instructor.

Completed on February 19, 2024
