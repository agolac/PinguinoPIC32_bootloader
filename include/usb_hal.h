// USB Buffer descriptor according PIC32 Family Reference Manual section 27.3.5.3.4
typedef struct __attribute__ ((packed)) {
	struct __attribute__ ((packed)) {
		unsigned		:2;	// Reserved
		unsigned BSTALL		:1;	// Buffer Stall Enable bit
		unsigned DTS		:1;	// Data Toggle Synchronization Enable bit
		unsigned NINC		:1;	// DMA Address Increment Disable bit
		unsigned KEEP		:1;	// BD Keep Enable bit
		unsigned DATA0_1	:1;	// Data Toggle Packet Bit
		unsigned UOWN		:1;	// USB OWN bit, 1-USB-OTG Own, 0-CPU Own
		unsigned		:8;	// Reserved
		unsigned ByteCount	:10;	// Number of bytes to be transmitted/max received
		unsigned		:6;	// Reserved
		uint32_t BufferAddress;		// Starting point address of the endpoint packet data
						// buffer. Must be physical memory address
	} ControlFormat;
	struct __attribute__ ((packed)) {
		unsigned 		:2;	// Reserved
		unsigned PID		:4;	// Packet Identifier Bits
		unsigned DATA0_1	:1;	// Data Toggle Packet bit
		unsigned UOWN		:1;	// USB Own bit
		unsigned		:8;	// Reserved
		unsigned ByteCount	:10;	// Actual number of bytes transfered or received
		unsigned 		:6;	// Reserved
		uint32_t BufferAddress;		// Starting pointing address of the endpoint packet data
						// buffer. Must be physical memory address
	} StatusFormat;

} buffer_descriptor;

