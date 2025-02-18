#!/bin/bash

LIB_DIR=lib
LIB_LIST=$(cat $LIB_DIR/.liblist)

# Check each
for LIB in $LIB_LIST; do
    # If file .installed not exists, install it
    if [ ! -f "$LIB_DIR/$LIB/.installed" ]; then
        bash $LIB_DIR/$LIB/install.sh

        # Check if the installation was successful
        if [ $? -eq 0 ]; then
            touch "$LIB_DIR/$LIB/.installed"
        else
            echo "❌ Installation failed."
            exit 1
        fi

    fi
done
