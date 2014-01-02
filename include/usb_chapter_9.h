/*      ----------------------------------------------------------------------------
        FILE:                           usb_descriptors.h
        PROJECT:                        pinguino - http://www.pinguino.cc/
        PURPOSE:                        Pinguino PIC32 bootloader USB descriptors
        PROGRAMER:                      Andrej Golac <andrej.golac@runbox.com>
        FIRST RELEASE:                  January 2014
        LAST RELEASE:
        ----------------------------------------------------------------------------
        This is free software; you can redistribute it and/or modify it under the 
        terms of the GNU Lesser General Public License as published by the Free 
        Software Foundation; either version 2.1 of the License, or (at your option) 
        any later version.

        This software is distributed in the hope that it will be useful, but WITHOUT 
        ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
        FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more 
        details.

        You should have received a copy of the GNU Lesser General Public License along 
        with this library; if not, write to the Free Software Foundation, Inc., 59 
        Temple Place, Suite 330, Boston, MA  02111-1307  USA
        ----------------------------------------------------------------------------

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

#include <stdint.h>

typedef struct __attribute__((packed))__ {
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

typedef struct __attribute__ ((packed)) {
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

typedef struct __attribute__ ((packed)) {
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

typedef struct __attribute__ ((packed)) {
	int8_t	bLength;		// Descriptor size in bytes (07h)
	int8_t	bDescriptorType;	// The constant ENPOINT (05h)
	int8_t	bEndpointAddress;	// Endpoint number and direction
	int8_t	bmAttributes;		// Transfer type and supplementary information
	int16_t	wMaxPacketSize;		// Maximum packet size supported
	int8_t	bInterval;		// Service interval or NAK (Not Aknowledged) rate
} endpoint_descriptor;

typedef struct __attribute__ ((packed)) {
	int8_t	bLength;		// Descriptor size in bytes (variable)
	int8_t	bDescriptorType;	// The constand STRING (03h)
      uint16_t	bSTRING[];		// String
} string_descriptor;

typedef struct __attribute__ ((packed)) {
	int8_t	bLength;		// Descriptor size in bytes (09h)
	int8_t	bDescriptorType;	// The constant for HID (21h)
	int16_t	bcdHID;			// HID Spec. release number (BCD)
	int8_t	bCountryCode;		// Country Code
	int8_t	bNumDescriptors;	// Number of subordinate class descriptors
	int8_t	bDescriptortype;	// Descriptor Type
	int16_t	wDescriptorLength;	// Report descriptor size in bytes
} hid_descriptor;

/*
	Format of Setup Data, Chapter 9, Table 9.2
	bmRequestType = D7	Data direction
				0 = Host To Device
				1 = Device To Host
			D6-5	Type
				0 = Standard
				1 = Class
				2 = Vendor
				3 = Reserved
			D4-0	Recipient
				0 = Device
				1 = Interface
				2 = Endpoint
				3 = Other
				4-31 = Reserved
				
			
*/
typedef struct __attribute__ ((packed)) {
	uint8_t	bmRequestType;
	uint8_t	bRequest;
	uint16_t wValue;
	uint16_t wIndex;
	uint16_t wLength;
} setup_data;

// Chapter 9, Standard Device Requests Table 9-4
enum StandardDeviceRequests {
	GET_STATUS		= 0x00,
	CLEAR_FEATURE		= 0x01,
	//			= 0x02,	// Reserved for future use
	SET_FEATURE		= 0x03,
	//			= 0x04;	// Reserved for future use
	SET_ADDRESS		= 0x05,
	GET_DESCRIPTOR		= 0x06,
	SET_DESCRIPTOR		= 0x07,
	GET_CONFIGURATION	= 0x08,
	SET_CONFIGURATION	= 0x09,
	GET_INTERFACE		= 0x0A,
	SET_INTERFACE		= 0x0B,
	SYNCH_FRAME		= 0x0C,
};

// Chapter 9, Descriptor Types, Table 9-5
enum DescriptorTypes {
	DEVICE				= 0x01,
	CONFIGURATION			= 0x02,
	STRING				= 0x03,
	INTERFACE			= 0x04,
	ENDPOINT			= 0x05,
	DEVICE_QUALIFIER		= 0x06,
	OTHER_SPEED_CONFIGURATION	= 0x07,
	INTERFACE_POWER			= 0x08,
};

enum DeviceState {
	DEVICE_ATTACHED,
	DEVICE_POWERED,
	DEVICE_DEFAULT,
	DEVICE_ADDRESS,
	DEVICE_CONFIGURED,
	DEVICE_SUSPENDED
};
