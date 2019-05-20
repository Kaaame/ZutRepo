import sys
import argparse
import os
import time
from pwd import getpwuid
from stat import *

parser = argparse.ArgumentParser(description='ls, but retarded.')
parser.add_argument('-a', dest='hiddenflag', action='store_true', help='Show all files')
parser.add_argument('-l', dest='longflag', action='store_true', help='Show additional information')
parser.add_argument('dirz', nargs='*', type=str, default='.')
args = parser.parse_args()

rightsval = ('x', 'w', 'r')
for i in range(0, len(args.dirz)):
    for filename in os.listdir(args.dirz[i]):
        if args.dirz[i] != ".":
            fh = args.dirz[i] + filename
        else:
            fh = filename
        if not args.hiddenflag and filename[0] == '.':
            #print(repr(args.hiddenflag) + " + " + filename[0])
            continue
        # print(fh + ' = ' + filename + ':')
        #print(statinfo[ST_MODE])
        if args.longflag:
            statinfo = os.stat(fh)
            print(filename, end=' ')
            print(statinfo.st_size, end=' ')
            print(getpwuid(statinfo.st_uid).pw_name, end = ' ')
            #print(time.strftime('%Y-%m-%-d %H-%M-%S', statinfo.st_mtime), end=' ')
            print(time.ctime(statinfo.st_mtime), end=' ')
            rights = ""
            if os.path.isdir(fh):
                rights += "d"
            for i in range(8,-1,-1):
                pos = i % 3
                if statinfo[ST_MODE] & 1<<i:
                    rights += rightsval[pos]
                else:
                    rights += '-'
            print(rights, end=' ')
            print("")
        else:
            print(filename, end=' ')
print("")


