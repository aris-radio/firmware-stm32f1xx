#!/bin/bash

# Directory and version settings
LIB_DIR="lib"
LIB_NAME="libprotoarisr"
VERSION="1.0.0"
URL="https://github.com/aris-radio/lib-protoarisr-c/releases/download/v$VERSION/libprotoarisr-$VERSION-source.tar.gz"

# Filename for the downloaded ZIP
FILE="libprotoarisr-source.tar.gz"

# Create the target extraction directory (if it doesn't already exist)
mkdir -p "$LIB_DIR/libprotoarisr"

# Download the file
echo "📥 Downloading $FILE from $URL..."
wget -O "$LIB_DIR/$LIB_NAME/$FILE" "$URL"

# Check if the download was successful
if [ $? -eq 0 ]; then
    echo "✅ Download completed."

    # Extract the file into $LIB_DIR/libprotoarisr
    echo "📦 Extracting $FILE into $LIB_DIR/$LIB_NAME..."
    tar -xvf "$LIB_DIR/$LIB_NAME/$FILE" -C "$LIB_DIR/$LIB_NAME"

    echo "✅ Extraction complete."

    # Remove the ZIP file after extraction
    rm "$LIB_DIR/$LIB_NAME/$FILE"
    echo "🗑️ ZIP file deleted."
else
    echo "❌ Download failed."
    exit 1
fi
