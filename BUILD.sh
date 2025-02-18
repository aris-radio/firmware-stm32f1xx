# Replace values with your own
CPU=cortex-m3
MCU=stm32f103xb

VERSION=$(cat .version)

# if exist parameter, use it
if [ -n "$1" ]; then
    CPU=$1
fi

if [ -n "$2" ]; then
    MCU=$2
fi

# help
if [ "$1" == "help" ]; then
    echo "Usage: ./BUILD.sh [CPU] [MCU]"
    echo "Example: ./BUILD.sh cortex-m4 stm32f407xx"
    exit 0
fi

LIB_DIR=lib
# Check list of libraries
LIB_DIRNAME_LIST=$(cat $LIB_DIR/.liblist)

# Check if the library exists
for LIB_DIRNAME in $LIB_DIRNAME_LIST; do
    if [ ! -f "$LIB_DIR/$LIB/.installed" ] || [ ! -d "$LIB_DIR/$LIB_DIRNAME" ]; then
        echo "Library $LIB_DIRNAME not found, configuring..."
        
        bash $LIB_DIR/configure.sh

        # Check if the configuration was successful
        if [ $? -eq 0 ]; then
            echo "✅ Configuration complete."
        else
            echo "❌ Configuration failed."
            exit 1
        fi
    fi
done

# if not exist, use default
make cleanall
make CPU=$CPU MCU=$MCU VERSION=$VERSION