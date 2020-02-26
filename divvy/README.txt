divvy is a program to find the commands to distribute Havok and other compatible crackers to a specified number of computers/threads.
Cain (http://www.oxid.it) is the only other cracker I know of which is compatible with distribution in this manner.

command-line syntax is:

divvy <number of processes to spawn> <password length> <charset file>

a little different from the older version. Makes it a little harder for people to screw it up when they have to supply each charset file
manually.

There are two folders in the 'divvy' directory:
	default - use these files to find the distribution start words for Cain if Cain is using the default charsets. Be sure to use the
		charset file which corresponds with Cain's brute force charset configuration.
	last-character - use these files to find the distribution start words for Havokv3. Havokv3's character sets are hard-coded in,
		so a last-character routine is all that is possible without source code modification. You can also use a last-character
		routine for Cain, but you must eneter a last-character frequency analysis string into the 'custom charset' box in Cain's
		cracker window.

for more information on distributing Cain using divvy, see http://www.cerberusgate.com/Distributing_exhaustive_attack_using_Cain.htm

you can also play with other charset configurations (like my research into full position-respective frequency analysis), but make sure you
know what you're doing. Using the wrong start words can cause large chunks of words to be skipped, potentially causing unneccssary failure to
recover a password.

NOTE: charsets cannot contain over 99 chars!