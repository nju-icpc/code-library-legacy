#!/usr/bin/python
import re, os, hashlib


line_count = 1

def digest_line(s):
	return hashlib.md5(re.sub(r'\s|//.*', '', s)).hexdigest()[-4:]

langs = {"c": "C", "cpp": "C++", "py": "Python", "pl": "Perl",
		 "sh": "sh", "java": "Java"}

def lang(ext):
	if not ext: return "{}"
	ext = ext.lower()
	return langs[ext] if ext in langs else "{}"

def gen_section(name, dirname):
	global line_count
	sect = []
	sect.append("\\section{%s}" % name)

	files = []
	for src in os.listdir("./%s/" % dirname):
		fp = open("./%s/%s" % (dirname, src), "r") # read the file
		code = fp.read().strip()
		fp.close()

		match = re.search(r'^((\d+) )?(.*?)(\.([^.]*))?$', src)
		index = int(match.group(2)) if match.group(1) else 99999
		title = match.group(3)
		extension = match.group(5)

		files.append( (index, title, extension, code) )
		
	for (index, title, extension, code) in sorted(files):
		sect.append("\\subsection{%s}" % title)

		for line in code.split("\n"):
			sect.append("\\createlinenumber{%d}{%s}" % (line_count, digest_line(line)))
			line_count += 1

		sect.append("\\begin{lstlisting}[language=%s]" % lang(extension))
		sect.append(code)
		sect.append("\\end{lstlisting}")
	
	return "\n".join(sect)

doc = []
os.chdir("./src/")
for section in os.listdir("."):
	match = re.search(r'^(\d+) (.*)$', section)
	(index, name) = (int(match.group(1)), match.group(2)) if match else (99999, section)
	doc.append((index, name, section))

print "\n\n".join([gen_section(item[1], item[2]) for item in sorted(doc)])
