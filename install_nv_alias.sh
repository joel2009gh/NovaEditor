#!/bin/bash
if [ ! -f "/usr/local/bin/novaeditor" ]; then
    echo "Error: NovaEditor is not installed in /usr/local/bin/"
    echo "Please install NovaEditor first."
    exit 1
fi
if [ -f "/usr/local/bin/nv" ]; then
    echo "Found existing 'nv' alias. Removing..."
    sudo rm /usr/local/bin/nv
    if [ $? -ne 0 ]; then
        echo "Error: Failed to remove existing 'nv' alias. Do you have sudo privileges?"
        exit 1
    fi
fi
echo "Creating 'nv' alias for NovaEditor..."
echo '#!/bin/bash
novaeditor "$@"' | sudo tee /usr/local/bin/nv > /dev/null
sudo chmod +x /usr/local/bin/nv
if [ $? -eq 0 ]; then
    echo "Success! You can now use 'nv' as a shortcut for 'novaeditor'."
    echo "Example: nv filename.txt"
else
    echo "Error: Failed to create 'nv' alias. Do you have sudo privileges?"
    exit 1
fi
