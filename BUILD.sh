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

# if not exist, use default
make cleanall
make CPU=$CPU MCU=$MCU VERSION=$VERSION