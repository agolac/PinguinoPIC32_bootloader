PROCESSOR=32MX440F256H
ARCH=mips32r2
#LIBS= -lm -lgcc -lc
#CC=/home/agolac/mips/bin/mipsel-unknown-elf-gcc
#CC=/opt/microchip/xc32/v1.30/bin/xc32-gcc
CC=/home/agolac/Downloads/ide/x.4/linux/p32/bin/mips-elf-gcc
INCDIR=	-I include \
	-I include/non-free \
	-I include/non-free/$(PROCESSOR) \
	-I usb/include \
	-I src
CFLAGS=	-EL -Os -march=$(ARCH) -fdollars-in-identifiers -msoft-float \
	-D __$(PROCESSOR)__ -D __PIC32MX__ \
	-Wl,-Map=output.map,--cref -nostartfiles \
	-L include/non-free/$(PROCESSOR) \
	-T include/non-free/$(PROCESSOR)/procdefs.ld \
	-T include/non-free/$(PROCESSOR)/elf32pic32mx.x
bootloader:
	$(CC) $(INCDIR) $(CFLAGS) -o bootloader src/main.c \
			include/non-free/32MX440F256H/processor.o \
			src/crt0.S \
			src/usb.c \
			src/ISRwrapper.S
