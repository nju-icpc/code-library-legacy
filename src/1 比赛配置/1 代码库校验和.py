# 代码库校验用于检查代码库录入是否正确，忽略每行的空白字符和注释(//)
# 使用方法: python checksum.py < 1001.cpp
# 输出: 每一行代码及其校验和(md5)
import re, sys, hashlib

def digest_line(s):
	return hashlib.md5(re.sub(r'\s|//.*', '', s)).hexdigest()[-4:]

for line in sys.stdin.read().strip().split("\n"):
	print digest_line(line), line
