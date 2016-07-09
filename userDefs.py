import argparse

userDefsParser = argparse.ArgumentParser(add_help=False)
userDefsParser.add_argument('--userDefsOverride', default="userDefsDefault", help='Override Userdefs')

userDefArgs, userDefUnknown = userDefsParser.parse_known_args()

try:
	userDefsOverrideModule = __import__ (userDefArgs.userDefsOverride)
	try:
		attrlist = userDefsOverrideModule.__all__
	except AttributeError:
		attrlist = dir (userDefsOverrideModule)
	for attr in attrlist:
		globals()[attr] = getattr (userDefsOverrideModule, attr)
except:
	print "Unknown userDefsOverride"
	exit()
