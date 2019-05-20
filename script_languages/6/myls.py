import sys
import argparse

parser = argparse.ArgumentParser(description='ls, but retarded.')
parser.add_argument('-a', dest='hiddenflag', action='store_true', help='Show all files')
parser.add_argument('-l', dest='longflag', action='store_true', help='Show additional information')
parser.add_argument('infile', nargs='?', default=sys.stdin)
args = parser.parse_args()


#print(args.longflag)
#print(args.hiddenflag)

