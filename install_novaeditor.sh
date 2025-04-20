#!/bin/bash
cd novaeditor/
echo "Building NovaEditor..."
make
if [ $? -eq 0 ]; then
    echo "Build successful!"
    echo "Installing NovaEditor globally..."
    
    # Check if novaeditor already exists in /usr/local/bin/
    if [ -f "/usr/local/bin/novaeditor" ]; then
        echo "Found existing installation. Removing..."
        sudo rm /usr/local/bin/novaeditor
        if [ $? -ne 0 ]; then
            echo "Error: Failed to remove existing installation. Do you have sudo privileges?"
            exit 1
        fi
    fi
    # Copy the new executable
    sudo cp novaeditor /usr/local/bin/novaeditor
    if [ $? -eq 0 ]; then
        sudo chmod +x /usr/local/bin/novaeditor
        echo "NovaEditor installed successfully!"
        echo "You can now use it by typing 'novaeditor' anywhere in your terminal."
    else
        echo "Error: Failed to copy to /usr/local/bin/. Do you have sudo privileges?"
    fi
else
    echo "Error: Build failed. Please check the error messages above."
fi
