#!/usr/bin/python
import os
import subprocess
import shutil
import zlib

code_dir = "code"
tmp_dir   = "_tmp_code"   # flat temp dir with space-free names for minted

def sanitize(name):
    """Replace spaces and special chars so LaTeX/minted can handle the filename."""
    return name.replace(' ', '_').replace("'", "").replace('"', '')

def get_sections():
    # Clean and recreate the temp dir
    if os.path.exists(tmp_dir):
        shutil.rmtree(tmp_dir)
    os.makedirs(tmp_dir)

    sections = []
    for (root, dirs, files) in os.walk(code_dir):
        # Sort dirs so traversal order is consistent
        dirs.sort()
        subsections = []
        section_name = os.path.basename(root)
        sections.append((section_name, subsections))
        for file_name in sorted(files):
            subsection_name = os.path.splitext(file_name)[0]
            if subsection_name.startswith('.'):   # Skip hidden files
                continue
            print(subsection_name)
            relative_path = os.path.join(root, file_name)
            data = open(relative_path, 'rb').read()
            number_of_lines = data.count(b'\n')
            # CRC32 as a short hash (replaces the original Windows Hash command)
            hash_value = format(zlib.crc32(data) & 0xFFFFFFFF, '08X')

            # Copy to temp dir with sanitized name (section + file, no spaces)
            safe_section = sanitize(section_name)
            safe_file    = sanitize(file_name)
            tmp_path = os.path.join(tmp_dir, safe_section + '__' + safe_file)
            shutil.copy2(relative_path, tmp_path)
            # Use forward slashes for LaTeX
            tmp_path_fwd = tmp_path.replace('\\', '/')

            subsections.append((tmp_path_fwd, subsection_name, number_of_lines, hash_value))
    return sections[1:]

def get_style(filename):
    ext = filename.lower().rsplit('.', 1)[-1]
    if ext in ['c', 'cc', 'cpp']:
        return 'c++'
    elif ext in ['java']:
        return 'java'
    elif ext in ['py']:
        return 'python'
    else:
        return 'text'

def texify(s):
    # Escape LaTeX special characters that appear in section/subsection names
    for ch in ['&', '%', '$', '#', '_', '{', '}', '~', '^', '\\']:
        if ch == '\\':
            s = s.replace(ch, r'\textbackslash{}')
        else:
            s = s.replace(ch, '\\' + ch)
    return s

def get_tex(sections):
    tex = ''
    for (section_name, subsections) in sections:
        tex += '\\section{%s}\n' % texify(section_name)
        for (tmp_path, subsection_name, number_of_lines, hash_value) in subsections:
            tex += '\\subsection{\\small %s  \\scriptsize [%s lines] - %s}\n' % (
                texify(subsection_name), number_of_lines, hash_value)
            tex += '\\inputminted{%s}{%s}\n' % (get_style(tmp_path), tmp_path)
        tex += '\n'
    return tex

if __name__ == "__main__":
    sections = get_sections()
    tex = get_tex(sections)
    with open('contents.tex', 'w', encoding='utf-8') as f:
        f.write(tex)
    latexmk_options = ["latexmk", "-pdf", "-shell-escape", "-cd", "notebook.tex"]
    subprocess.call(latexmk_options)
