import sys
import hashlib
import os
BLOCKSIZE = 65536
result = {}
for i in range(1, len(sys.argv)):
    for root, dirs, files in os.walk(sys.argv[i]):
        if root[-1] != '/':
            root+='/'
        for file in files:
            filepath = ''.join([root,file])
            with open(filepath, 'rb') as hashfile:
                hasher = hashlib.sha1()
                buf = hashfile.read(BLOCKSIZE)
                while len(buf) > 0:
                    hasher.update(buf)
                    buf = hashfile.read(BLOCKSIZE)
            result[filepath] = hasher.hexdigest()
same = {}
for k, v in result.items():
    same.setdefault(v, set()).add(k) 
same = [print(k, ' = ', v, '\n') for k, v in same.items() if len(v) > 1] 
print(same)