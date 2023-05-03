#!/usr/bin/env python3
import re, os, hashlib, yaml

line_count = 1

with open("scl.yaml", "r") as file:
    scl = yaml.load(file, Loader=yaml.SafeLoader)

LANGS = {"c": "C", "cpp": "C++", "py": "Python", "pl": "Perl",
     "sh": "sh", "java": "Java"}

def lang(ext):
  if not ext: return "{}"
  ext = ext.lower()
  return LANGS[ext] if ext in LANGS else "{}"

def gen_section(sect_yaml):
  global line_count

  name = sect_yaml['name']
  dirname = sect_yaml['dir']
  files = sect_yaml['files']

  sect = []
  sect.append("\\section{%s}" % name)

  for (idx, f) in enumerate(files):
    title = f['title']
    fname = f['fname']
    desc = f.get('desc', None)

    with open("src/%s/%s" % (dirname, fname), "r") as fp:
      code = fp.read()

    extension = fname.split('.')[-1]

    sect.append("\\subsection{%s}" % title)

    def digest_line(s):
      return hashlib.md5(re.sub(r'\s|//.*', '', s).encode('utf-8')).hexdigest()[-4:]

    for line in code.split("\n"):
      sect.append("\\createlinenumber{%d}{%s}" % (line_count, digest_line(line)))
      line_count += 1

    if desc:
      sect.append('\\begin{mdframed}[hidealllines=true,backgroundcolor=blue!5]')
      sect.append(desc.strip())
      sect.append('\\end{mdframed}\\vspace{-10pt}')
    sect.append("\\begin{lstlisting}[language=%s]" % lang(extension))
    sect.append(code)
    sect.append("\\end{lstlisting}")

  return "\n".join(sect)

for section in scl:
  print(gen_section(section))
