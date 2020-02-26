The parameters for operating hbademo properly are very specific.

HBAdemo takes one argument: the password file being analyzed.

This password file must contain plaintext passwords, 1 password per line. All passwords must be of the same length.
ALL passwords must fall into ALL of the charsets specified in the 'charsets.txt' file.

HBAdemo is hard-coded to read charets from a text file ('charsets.txt'). This file must be in the same directory as the HBAdemo executable.
'charsets.txt' must contain the charsets for each position of the password, one charset string per line. For example:
if the password file contains passwords of length '6', then there must be 6 or more lines in the 'charsets.txt' file, containing the charsets
for each position of the password. The first line will be the charset for the first char of the password, and so on.

All charsets in 'charsets.txt' must be the same. They can only vary by ordering of elements (chars), but all charset strings must contain the same
chars.

You can rewrite 'charsets.txt' with charsets that order their characters in a manner that respects human behavior analysis. Then run HBAdemo
to demonstrate the advantages your character sets provide over standard non-HBA respecting charsets.