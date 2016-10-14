import re, sys, hashlib

def digest_line(s):
    return hashlib.md5(re.sub(r'\s|//.*', '', s)).hexdigest()[-4:]

for line in sys.stdin.read().strip().split("\n"):
    print digest_line(line), line
