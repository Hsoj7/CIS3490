Name: Joshua Stone
Student Number: 1013900
Guelph mail: jstone04@uoguelph.ca
Assignment: 3

To compile and run:
My assignment contains 5 '.c' files: P11.c, P12.c, P21.c, P22.c, P23.c
To run them, type 'make' to execute the makefile. This will produce
5 executable files. Then type ./P11, ./P12, ..., etc. to run each of them.

P11 - Prints total anagrams found of the number that the user enters.
Then, it will compare each of the anagrams to each of the 30,000 numbers
in data_4.txt and determine if there are any matches. It any matches are
found, it will print them out then calculate the total run time. This
program is done using brute force. For an eight digit number (10 million
to 99 million) it took me on average, 3 seconds to run. For a nine digit
numbers, it took roughly 30 seconds and for a 10 digit number, 300 seconds.

P12 - Same as P11, it will print total anagrams found for the entered
number. Then, it sorts the 30000 in an array (least to greatest) by using
mergesort and performs binary search on the sorted array. It will print
the number of found matches. On average, an 8 digit number took 8ms, a
9 digit number took 60ms and a 10 digit number took 600ms or 0.6 seconds.

**For both of these programs, I assumed we are to not print out duplicate
matches in data_4.txt. For exmaple, if the number '1234' appear twice in
the text file, it would only be printed and 'found' one time.**

P21 - This program performs brute force pattern matching by comparing every
character in the file to the ones in the string that the user enters. If
there are strlen(userString) characters matches in a row, the program will
increase the match counter by 1. It will then print the # of occurences of
the pattern if found, print total number of shifts and time took to run. It
takes an average, 75ms or 0.75s to run.

P22 - This program performs pattern matching using Horspool's algorithm.
There is a shift table that computes how much each shift should move by.
This program prints out total occurences of the user's pattern that it found,
total number of shifts and time took to run. On average, it took 50ms or
0.05s to run.

P23 - This program performs pattern matching through Boyer-Moore;s algorithm.
It includes a good match and bad match calculation for performing shifts. If
the rightmost character of the user's pattern does not match, it will perform
the shift as would horspools. But, if the rightmost character does match, it
compares characters before the rightmost in the user's string and computes
shifts accordingly. This program will print the total occurences found, total
shifts made and total time took to run. On average, it takes me 50ms or 0.5s
to run.

2.4 - The 10 patterns I chose to use when comparing are: 'a', 'at', 'car',
'econ', 'chose', 'Policy', 'students', 'enrolled', 'secondary' and 'activities'.
For each of the ratios, I use a common time of 100ms for each of the averages.
So, based on the average calculations, I determine the # of shifts per second.

For 2.1:
Time = (74 + 75 + 73 + 75 + 72 + 70 + 76 + 74 + 72 + 74) / 10 = 73.5ms
Shifts = (3300513 * 10) / 10 = 3300513
There are always 3300513 shifts for brute force.
So, 73.5ms * 1.3606 = 100ms, 3300513 shifts * 1.3606 = 4490678
This gets 4,490,678 shifts per 100ms on average


For 2.2:
Time = (86 + 67 + 59 + 54 + 53 + 52 + 57 + 50 + 48 + 49) / 10 = 57.5ms
Shifts = (3300513 + 1688093 + 1142427 + 873838 + 700935 + 590194 + 480639
 + 467114 + 437497 + 380812) / 10 = 1006206.2
So, 57.5ms * 1.7544 = 100ms, 1006206.2 shift * 1.7544 = 1765288
This gets 1,765,288 shifts per 100ms on average

For 2.3:
Time = (79 + 61 + 59 + 54 + 51 + 52 + 50 + 51 + 48 + 48) / 10 = 55.3ms
Shifts = (3088159 + 1722714 + 1171173 + 895051 + 720382 + 592088 + 485509
+ 475145 + 391826) / 10 = 954204.7
So, 55.3ms * 1.8084 = 100ms, 954204.7 * 1.8084 = 1725584
This gets 1,725,584 shifts per 100ms

Now, we can compare the average shifts per 100ms. 2.1 definitely took the
longest on time to run and shifts per second. 2.2 and 2.3 we very close in
execution time and shifts per 100ms. I notcied that 2.3 had around 300,000
less shifts for finding single characters, but 2.2 was around 20,000-30,000
less shifts for every search greater than one character. With that being said,
my boyer-moore algorithm was just shorter on average execution time than
horspool. Overall, if I was attempting to make a functionality for a program
that implements a cntrl + f function, the boyer-moore algorithm would be more
appropriate just based off of execution time. Happy marking :)
