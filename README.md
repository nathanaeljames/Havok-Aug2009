# Havok-Aug2009
Havok and its various tools are part of a cryptography research project which I coded in C++ when I was 18 years old. The goal of the project was not to develop the fastest or best password cracking tool, but to demonstrate various cracking algorithm optimization techniques, experiment with distributed computing, and measure the benefits of human behavior analysis. The program was run on a homemade computer cluster.

Havokv3 - the main project program, Havok version 3 is a distributed password recovery tool. Its various modules support recovery of MD4, MD5, NTLM, MSCACHE, and Kerberos 5 passwords for single and multiple simultaneous hashes. The Kerberos 5 module experimented with various timesaving techniques in the encryption algorithm, namely saving 26% recovery time by preemptively checking the time stamp before computing the entire checksum. 

divvy - divvy is a program designed to calculate distribution of the password cracking task to multiple computers and can be used for Havok as well as other crackers. divvy allowed for the distribution to be done with custom character sets and parameters for research purposes.

HBAdata - hbadata is a program that analyzes character frequencies and positions in a list of passwords. This tool allows the user to analyze a list of dumped passwords to see what types of constructions are most common. This data can then be used to  reduce crack time with Havok and other recovery tools which can make use of custom character sets.

HBAdemo - hbademo receives a plaintext password dump and a characterset file and determines the time saved by frequency analysis. This tool can be used to demonstrate the cryptanalytic advantages of frequency and human behavior analysis in multiple different scenarios.
 
shmoosh - a wordlist tool, shmoosh takes two wordlist files at once, joins them, and removes duplicate words. This minimizes the ammount of time wasted in scanning multiple wordlists during a dictionary attack.

chunky - chunky is a suite of wordlist manipulation tools which can be linked together using a powerful piping structure to create wordlists exactly like you want them. Prefixing, suffixing, case toggling, and various other mangling rules can be performed using this structure. The results can then be piped into a text file to create a dictionary or directly into chunky's brute force testing modules.
