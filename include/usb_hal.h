// USB Buffer descriptor according PIC32 Family Reference Manual section 27.3.5.3.4
typedef struct __attribute__ ((packed)) {
	struct __attribute__ ((packed)) {
		uint8_t			:2;	// Reserved
		uint8_t BSTALL		:1;	// Buffer Stall Enable bit
		uint8_t DTS		:1;	// Data Toggle Synchronization Enable bit
		uint8_t NINC		:1;	// DMA Address Increment Disable bit
		uint8_t KEEP		:1;	// BD Keep Enable bit
		uint8_t DATA0_1		:1;	// Data Toggle Packet Bit
		uint8_t UOWN		:1;	// USB OWN bit, 1-USB-OTG Own, 0-CPU Own
		uint8_t			:8;	// Reserved
		uint16_t ByteCount	:10;	// Number of bytes to be transmitted/max received
		uint8_t			:6;	// Reserved
		uint32_t BufferAddress;		// Starting point address of the endpoint packet data
						// buffer. Must be physical memory address
	} ControlFormat;
	struct __attribute__ ((packed)) {
		uint8_t 		:2;	// Reserved
		uint8_t PID		:4;	// Packet Identifier Bits
		uint8_t DATA0_1		:1;	// Data Toggle Packet bit
		uint8_t UOWN		:1;	// USB Own bit
		uint8_t			:8;	// Reserved
		uint16_t ByteCount	:10;	// Actual number of bytes transfered or received
		uint8_t 		:6;	// Reserved
		uint32_t BufferAddress;		// Starting pointing address of the endpoint packet data
						// buffer. Must be physical memory address
	} StatusFormat;

} buffer_descriptor;

// PIC32 Family Reference Manual, Chapter 27, Figure 27-2
typedef struct {
	int32_t	BDTBA		:23;
	int8_t	ENDPOINT	:4;
	int8_t	DIR		:1;
	int8_t	PPBI		:1;
	int8_t			:2;
} bdt_address_generation;
