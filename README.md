# Resizable-Tables

The overall dimensions of the Table data structure can be modified with functions similar in syntax to the
STL vector push back and pop back functions. The rows and cols variables are updated as needed, all
affected arrays are reallocated to be exactly as big as needed, the data is copied into the new arrays, and
all old replaced arrays are deleted. The push back row and push back column functions take in a single
argument, an STL vector, that contains the data values for the new row or column in the table. For example,
if new row is a vector of 5 chars: A, B, C, D, and E, then a call to push back row(new row) will result in the
new data structure diagram below left. Note that the top level array of pointers is reallocated, copied, &
deleted, but the existing row data arrays can be reused.

If the user next calls pop back column() on this example each row is shortened by one entry by allocating
new smaller arrays, copying data, and cleaning up the unused memory. This is shown in the figure above
right. The push back column and pop back row member functions work similarly. It is an error to attempt
to push back a row or column using a vector of data that is the wrong size (too long or too short). It is
also an error to attempt to pop back a row if rows==0 or to pop back a column if cols==0. Your program
should check for these cases and print a message to std::cerr and call exit(1).

![1](https://user-images.githubusercontent.com/71351207/111543346-4f6f7900-8749-11eb-9c42-151da85c6a8d.PNG)
