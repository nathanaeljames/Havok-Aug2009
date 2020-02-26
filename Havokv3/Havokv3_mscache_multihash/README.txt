Havokv3_mscache_multihash

a mscache cracker, written by Nathanael Warren, 2009

supports cracking of multiple hashes (up to 25) in lists
	you will need two lists:
		1) mscache hashes - 32-character hex strings, one per line
		2) corresponding usernames - one username per line, same line as corresponding
			mscache hash is in other file.
	use another program to collect the mscache hashes

I believe it supports cracking for usernames up to 40 characters, but I may be wrong. This should
cover most usernames, if you have some ridiculously long username, you can modify the source code.

if you are only targeting a single hash, you may want to use the single hash version
as it may slightly outperform the multihash version

cachedump and Cain are good tools for dumping mscache hashes.