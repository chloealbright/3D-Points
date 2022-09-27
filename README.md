Parts of Project completed:
```
The Big 5: default constructor, destructor, copy constructor, copy assignment,
move constructor, move assignment.
One parameter constructor.
size_t function type.
operator[] to get index.
operator+ to add sum.
Overload Output operator <<
Overload Input operator >>
```

Any bugs that you have encountered: 
```
bool if statement gave errors for the sum + operator 
de-allocation for the instream provided from class lecture, gave errors.
```

The input file (if any) and the output files (if any):
```
None needed for this assignment assuming you submit the points3d.h file and 
READ.md file.
```

Complete instructions of how to run your program(s):
To compile on terminal, type: 
```
g++ test_points3d.cc -std=c++17 
./a.out
```

```bash
make clean
make all
```

To delete executables and object files, type:

```bash
make clean
```

To run, type:

```bash
./test_points3d
```

## Providing Input from Standard Input

To run with a given file that is redirected to standard input:

```bash
./test_points3d < test_input_file.txt
```

