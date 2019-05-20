import sys
import re
import string
import operator

filecontent = ""
swapstring = ""
with open(sys.argv[1], 'r') as file:
    for i, line in enumerate(file):
        if i == 0:
            swapstring = line.replace('\n', '')
        else:
            filecontent += line.replace('\n', '')
filecontent = filecontent.lower()
swapstring = swapstring.lower()
def histogram(data):
    data = re.sub('[^A-Za-z]', '', data).lower()
    mapped = list(set(string.ascii_lowercase))
    pairs = {x : data.count(x) for x in mapped}
    sortedpairs = list(reversed(sorted(pairs.items(), key=operator.itemgetter(1))))
    print(sortedpairs)
    return ''.join(list(x[0] for x in sortedpairs))
retval = histogram(filecontent)
transpos = str.maketrans(swapstring, retval)
print(filecontent.translate(transpos))
