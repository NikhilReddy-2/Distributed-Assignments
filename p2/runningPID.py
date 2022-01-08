import os
import re
import sys
import pprint


pp = pprint.PrettyPrinter(indent=4)

try:
    op = sys.argv[1]
    if op == 'rf' or op == '-rf':
        stream = os.popen('ps -rf')
        output = stream.read()
        match = re.findall(r'(\d{1,5}) pts', output)
        print("Running process IDs :")
        pp.pprint(match)
    elif op == 'ef' or op == '-ef':
        stream = os.popen('ps -ef')
        output = stream.read()
        match = re.findall(r'[a-zA-Z]+\s+(\d{1,5})\s+\d', output)
        print("All process IDs :")
        pp.pprint(match)
except:
    print("Syntax - Pass '-rf' for running process ids or '-ef' for all process ids")
