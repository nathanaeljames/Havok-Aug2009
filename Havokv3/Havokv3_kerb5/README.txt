Havokv3_kerb5

a Kerberos 5 pre authentication cracker, written by Nathanael Warren, 2009

supports cracking of a single hash, fed in on the command line
	hash is a 104-character hex string encrypted timestamp
	in Cain, this is referred to as a 'Kerberos 5 PreAuth Hash'

The advantage of using Havokv3_kerb5 over Havokv3_kerb5_multihash is that,
if you are only targeting a single hash, Havokv3_kerb5 may outperform
Havokv3_kerb5_multihash by a little.

You will need to know the year that the encrypted timestamp was recovered.

I suggest using Cain (http://www.oxid.it/) to sniff the Kerberos 5 Pre Auth
exchange off the network. This can be done using Cain's APR feature.