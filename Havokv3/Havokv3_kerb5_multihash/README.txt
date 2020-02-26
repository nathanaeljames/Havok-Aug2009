Havokv3_kerb5_multihash

a Kerberos 5 pre-authentication cracker, written by Nathanael Warren, 2009

supports cracking of multiple hashes (up to 25) in lists
	hash list format is one 104-character hex string encrypted timestamp per line
	in Cain, this is referred to as a 'Kerberos 5 PreAuth Hash'

If you are only targeting one hash, you may want to look at using Havokv3_kerb5
rather than Havokv3_kerb5_multihash, as Havokv3_kerb5 may provide a small speed
advantage.

You will need to know the year that the encrypted timestamps were recovered.
Havok assumes that all timestamps in the list were recovered in the same year,
so no sniffing on new year's eve :(

I suggest using Cain (http://www.oxid.it/) to sniff the Kerberos 5 Pre Auth
exchange off the network. This can be done using Cain's APR feature.