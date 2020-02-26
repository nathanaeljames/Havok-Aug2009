genanal will print some basic data on a password list of arbitrary length, arbitrary charset. Passing the -s flag will sort the password list
into separate files depending on charset and length. These files can then be fed into hbadata for analysis.

hbadata is a program that analyzes character frequency in passwords. It takes a list of passwords, one password per line. Each password
must be the same length. hbadata will allow for a last character frequency analysis, a full frequency analysis, and an arbitrary position
frequency analysis. arbitrary analysis is the -a flag, full is the -f flag, and a last character frequency analysis can be done by using
the -f flag and only reading the string that represents the last position of the password.

MAKE SURE THAT THE PASSWORD FILE HAS NO NEWLINE AT THE END! This can lead to inaccurate results.