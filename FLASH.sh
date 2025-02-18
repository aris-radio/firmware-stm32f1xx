# Replace values with your own
# uart usb swd or default (STM32CUBEPROGRAMMER)
FLASH=swd
USB=/dev/ttyUSB0
RATE=9600

# if exist parameter, use it
if [ -n "$1" ]; then
    FLASH=$1
fi

if [ -n "$2" ]; then
    USB=$2
fi

if [ -n "$3" ]; then
    RATE=$3
fi

# help
if [ "$1" == "help" ]; then
    echo "Usage: ./FLASH.sh [FLASH] [USB] [RATE]"
    echo "Example: ./FLASH.sh st-flash /dev/ttyUSB0 9600"
    echo "Please start flashing the STM32 with a lower baud rate and then switch to a higher baud rate. Otherwise, the call will fail"
    exit 0
fi

make flash FLASH=$FLASH USB=$USB RATE=$RATE