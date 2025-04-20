# NovaEditor
NovaEditor is a lightweight, terminal-based text editor built from scratch in C. It offers essential text editing features with syntax highlighting for C/C++ files.
# Features

Syntax highlighting for C/C++ files
Line numbering
Status bar with file information
Search functionality
Simple and intuitive keyboard shortcuts
Efficient memory usage
Cross-platform compatibility

# Installation

Requirements:
GCC compiler
Make build system

1. Clone the repository: https://github.com/joel2009gh/novaeditor
2. cd novaeditor
3. make
    
If you want this to work globally on your device:
sudo cp novaeditor /usr/local/bin/novaeditor
sudo chmod +x /usr/local/bin/novaeditor

# Usage:

novaeditor [filename]

If no filename is provided, NovaEditor will start with an empty buffer.

# Keyboard Shortcuts

Ctrl+S = Save file
Ctrl+Q = Quit (prompts to save if there are unsaved changes)
Ctrl+F = Search bar
Arrow keys = Navigate
Page up/ Down = Scroll up/down
Home / end = Move to beginning / end of line
Backspace / Delete = Delete stuff


If you want to add support for aditional programming languages: modify syntax.c

For the .sh file: This script navigates to the NovaEditor source directory, compiles the editor, and installs it globally on your system so you can use the editor anywhere by simply typing 'novaeditor' in your terminal.
