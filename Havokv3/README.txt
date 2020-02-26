Author: Nathanael Warren - http://www.cerberusgate.com
------------------------------------------------------
Havokv3 is a distributed password recovery tool. It currently supports MD4, MD5, NTLM, MSCACHE, and Kerberos 5 algorithms for single and
multiple simultaneous hashes. You will have to choose which program to use depending on your hash type. All programs are compiled for Windows
with source code included.

Distribution is done with the tool 'divvy', available on my website. Havok only supports cracking passwords of length 5-10 as of this release.

I attempted to create Linux makefiles for this release, but after a great mess decided that most avid Linux enthusiasts are probably familiar
with WINE.

What's new?
-----------
last-character frequency analysis used - easier to distribute, better than Havokv2's fml model
mscache algorithm support added for single and multihash
all modules significantly accelerated using fast crypto routines rather than OpenSSL library
for single hash, at least the process which recovers the password will terminate upon recovery
single hash versions of MD4, MD5, and NTLM added while I work on fixing multihash versions

Bugs:
-----
if you find any, please report them to nathanael_warren@cerberusgate.com

also, if you have any suggestions/optimizations/code, I would be glad to talk with you

Thanks :)