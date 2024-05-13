# read all header files in src and create a markdown file with file names and content in code blocks

import os

def main():
    src_path = 'src'
    md_file = 'src.md'
    with open(md_file, 'w') as md:
        for root, dirs, files in os.walk(src_path):
            for file in files:
                if file.endswith('.h'):
                    with open(os.path.join(root, file), 'r') as f:
                        md.write('### ' + file + '\n')
                        md.write('```cpp\n')
                        for line in f:
                            md.write(line)
                        md.write('```\n\n')

if __name__ == '__main__':
    main()