################################################################################
# Updated version of userDefs
################################################################################
# If no special commandline arguments are give:
#    it just loads userDefsDefault
#
# If "--userDefsOverride userDefsXYZ" is added to the executing command:
#    searches pwd the source code directory for userDefsXYZ and loads it
#    if there is no such file: exit()
# 
# Needs:
#    userDefsDefault.py
#
# For correct help functions add to standalone scripts:
# userDefsParser.add_argument('--userDefsOverride', default="userDefsDefault", help='Override Userdefs')
#
###############################################################################


import argparse
import os
import sys


userDefsParser = argparse.ArgumentParser(add_help=False)
userDefsParser.add_argument('--userDefsOverride', default="userDefsDefault", help='Override Userdefs')

userDefArgs, userDefUnknown = userDefsParser.parse_known_args()

try:
	# adding present working directory to path
	# in oder to find userDef files in source code directory as well as pwd:
	pwd = os.getcwd()
	sys.path.insert(0,pwd)

	userDefsOverrideModule = __import__ (userDefArgs.userDefsOverride)

	# loads all elements of the userDefs:
	try:
		attrlist = userDefsOverrideModule.__all__
	except AttributeError:
		attrlist = dir (userDefsOverrideModule)
	for attr in attrlist:
		globals()[attr] = getattr (userDefsOverrideModule, attr)

except:
	print "Unknown userDefsOverride: "+userDefArgs.userDefsOverride
	exit()
