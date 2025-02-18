#!/bin/bash

LIB_DIR=lib
LIB_LIST=$(cat $LIB_DIR/.liblist)

# Check each
for LIB in $LIB_LIST; do
    # Remove all content inside the folder except the install script
    find $LIB_DIR/$LIB -type f ! -name "install.sh" -delete && \
    find "$LIB_DIR/$LIB" -type d -empty -delete

    # Check if exist .installed file, if yes fail the uninstall
    if [ -f "$LIB_DIR/$LIB/.installed" ]; then
        echo "❌ Uninstall failed for lib [$LIB]."
        exit 1
    fi

    echo "✅ Uninstall complete for lib [$LIB]."
done