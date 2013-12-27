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
      uint16_t	bSTRING[];		// String
} string_descriptor;

enum ControlTransferRequest {
	GET_STATUS		= 0x00,
	CLEAR_FEATURE		= 0x01,
	SET_FEATURE		= 0x03,
	SET_ADDRESS		= 0x05,
	GET_DESCRIPTOR		= 0x06,
	SET_DESCRIPTOR		= 0x07,
	GET_CONFIGURATION	= 0x08,
	SET_CONFIGURATION	= 0x09,
	GET_INTERFACE		= 0x0A,
	SET_INTERFACE		= 0x0B,
	SYNCH_FRAME		= 0x0C,
	SET_SEL			= 0x30,
	SET_ISOCHRONOUS_DELAY	= 0x31,
};
