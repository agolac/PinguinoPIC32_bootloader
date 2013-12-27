/*
Example of descriptor configuration tree

	DEVICE DECRIPTOR
		|
		|--- CONFIGURATION DESCRIPTOR ONE				*
		|		|						|
		|		|--- INTERFACE ZERO DESCIPTOR			|
		|		|		|				|
		|		|		|--- ENDPOINT DESCRIPTOR ONE	|
		|		|		|				|
		|		|		|--- ENDPOINT DESCRIPTOR TWO	| wTotalLength
		|		|						|
		|		|--- INTERFACE ONE DESCRIPTOR			|
		|				|				|
		|				|--- ENPOINT DESCRIPTOR ONE	|
		|				|				|
		|				|--- ENDPOINT DESCRIPTOR TWO	*
		|
		|--- CONFIGURATION DESCRIPTOR TWO				*
				|						|
				|--- INTERFACE ZERO DESCRIPTOR			|
						|				| wTotalLength
						|--- HID DESCRIPTOR		|
						|				|
						|--- ENPOINT DESCRIPTOR ONE	*
*/
typedef struct {
        int8_t  bLength;                // Descriptor size in bytes (12h)
        int8_t  bDescriptorType;        // The constant DEVICE (01h)
        int16_t bcdUSB;                 // USB specification release number (BCD)
        int8_t  bDeviceClass;           // Class code
        int8_t  bDeviceSubclass;        // Subclass code
        int8_t  bDeviceProtocol;        // Protocol code
        int8_t  bMaxPacketSize0;        // Maximum packet size for endpoint zero
        int16_t idVendor;               // Vendor ID
        int16_t idProduct;              // Product ID
        int16_t bcdDevice;              // Device release number (BCD)
        int8_t  iManufacturer;          // Index of string descriptor for manufacturer
        int8_t  iProduct;               // Index of string descriptor for product
        int8_t  iSerial;                // Index of string descriptor for serial number
        int8_t  bNumConfigurations;     // Number of possible configurations
} device_descriptor;

typedef struct {
	int8_t	bLength;		// Descriptor size in bytes (09h)
	int8_t	bDescriptorType;	// The constant CONFIGURATION (02h)
	int16_t wTotalLength;		// The Number of bytes in configuration descriptor
					// and all its subordinate descriptors
	int8_t	bNumInterfaces;		// Number of interfaces in configuration
	int8_t	bConfigurationValue;	// Identifier for Set Configuration and Get Configuration reqests
	int8_t	iConfiguration;		// Index of string descriptor for configuration
	int8_t 	bmAttributes;		// Self/bus power and remote wakeup settings
	int8_t	bMaxPower;		// Bus power req. in units of 2 mA (USB2.0) or 8 mA (Superspeed)
} configuration_descriptor;

typedef struct {
	int8_t	bLength;		// Descriptor size in bytes (08h)
	int8_t	bDescriptorType;	// The constant INTERFACE (04h)
	int8_t	bInterfaceNumber;	// Number identifying this interface
	int8_t	bAlternateSetting;	// A number that identifies a descriptor with alternate
					// settings for this bInterfaceNumber
	int8_t	bNumEndpoints;		// Number of endpoints supported not counting endpoint zero
	int8_t	bInterfaceClass;	// Class code
	int8_t	bInterfaceSubclass;	// Subclass code
	int8_t	bInterfaceProtocol;	// Protocol code
	int8_t	iInterface;		// Index of string descriptor for interface
} interface_descriptor;

typedef struct {
	int8_t	bLength;		// Descriptor size in bytes (07h)
	int8_t	bDescriptorType;	// The constant ENPOINT (05h)
	int8_t	bEndpointAddress;	// Endpoint number and direction
	int8_t	bmAttributes;		// Transfer type and supplementary information
	int16_t	wMaxPacketSize;		// Maximum packet size supported
	int8_t	bInterval;		// Service interval or NAK (Not Aknowledged) rate
} endpoint_descriptor;

typedef struct {
	int8_t	bLength;		// Descriptor size in bytes (variable)
	int8_t	bDescriptorType;	// The constand STRING (03h)
      uint16_t	bSTRING[8];		// String
} string_descriptor;
