/*	----------------------------------------------------------------------------
	FILE:				usb.c
	PROJECT:			pinguino - http://www.pinguino.cc/
	PURPOSE:			Pinguino PIC32 USB
	PROGRAMER:			Andrej Golac <andrej.golac@runbox.com>
	FIRST RELEASE:			January 2014
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
	--------------------------------------------------------------------------*/

#include <usb_descriptors.h>
#include <stdint.h>
#include <xc.h>
#include <usb_hal.h>

void InitUSB (void) {

device_descriptor USB_Device_descriptor;

USB_Device_descriptor.bLength 			= 0x12;   // Descriptor size in bytes
USB_Device_descriptor.bDescriptorType 		= 0x01;	  // 01h constant for Device descriptor
USB_Device_descriptor.bcdUSB			= 0x0200; // 0200h for USB 2.0
USB_Device_descriptor.bDeviceClass		= 0x00;	  // Zero for no device class
USB_Device_descriptor.bDeviceSubclass		= 0x00;	  // Zero for no device subclass
USB_Device_descriptor.bDeviceProtocol		= 0x00;	  // Zero for no device protocol
USB_Device_descriptor.bMaxPacketSize0		= 0x08;	  // Endpoint zero max packet size
USB_Device_descriptor.idVendor			= 0x04D8; // Microchip idVendor
USB_Device_descriptor.idProduct			= 0x003C; // Microchip idProduct
USB_Device_descriptor.bcdDevice			= 0x0002; // Microchip device release number
USB_Device_descriptor.iManufacturer		= 0x01;	  // Index to manufacturer string
USB_Device_descriptor.iProduct			= 0x02;   // Index to product string
USB_Device_descriptor.iSerial			= 0x03;   // Index to serial number string
USB_Device_descriptor.bNumConfigurations	= 0x01;	  // Number of configurations


configuration_descriptor USB_Configuration_descriptor;

USB_Configuration_descriptor.bLength		= 0x09; // Descriptor size in bytes
USB_Configuration_descriptor.bDescriptorType	= 0x02; // 02h constant for Configuration descriptor
USB_Configuration_descriptor.wTotalLength	= 0x029;// Total length of this and subordinate descript.
USB_Configuration_descriptor.bNumInterfaces	= 0x01; // 01h for only one interface
USB_Configuration_descriptor.bConfigurationValue= 0x01; // 01h for this configuration
USB_Configuration_descriptor.iConfiguration	= 0x00; // Zero if no string descriptor
USB_Configuration_descriptor.bmAttributes	= 0x80; // Bus powered,no remote wakeup,bit7 USB1.0 compa
USB_Configuration_descriptor.bMaxPower		= 0xFA; // (2mAx250)=2xFAh=max 500 mA

interface_descriptor USB_Interface_descriptor;

USB_Interface_descriptor.bLength		= 0x09; // Descriptor size in bytes
USB_Interface_descriptor.bDescriptorType	= 0x04; // 04h constant for Interface descriptor
USB_Interface_descriptor.bInterfaceNumber	= 0x00; // Zero for default interface number
USB_Interface_descriptor.bAlternateSetting	= 0x00; // No alternate setting
USB_Interface_descriptor.bNumEndpoints		= 0x02;	// Endpoints in addition to zero endpoint
USB_Interface_descriptor.bInterfaceClass	= 0x03;	// 03h is for HID interface
USB_Interface_descriptor.bInterfaceSubclass	= 0x00; // Zero if defined bInterfaceClass
USB_Interface_descriptor.bInterfaceProtocol	= 0x00; // Zero if defined bInterfaceClass
USB_Interface_descriptor.iInterface		= 0x00; // Zero if no string descriptor

hid_descriptor USB_HID_descriptor;

USB_HID_descriptor.bLength			= 0x09;	// Descriptor size in bytes
USB_HID_descriptor.bDescriptorType		= 0x21; // 21h constant for HID descriptor
USB_HID_descriptor.bcdHID			= 0x0110;// HID Spec. release number (BCD) (1.1)
USB_HID_descriptor.bCountryCode			= 0x00;	// Country Code
USB_HID_descriptor.bNumDescriptors		= 0x01; // Number of subordinate class descriptors
USB_HID_descriptor.bDescriptortype		= 0x22;	// 22h report descriptor type 

endpoint_descriptor USB_Endpoint_descriptor_OUT;

USB_Endpoint_descriptor_OUT.bLength		= 0x07; // Descriptor size in bytes
USB_Endpoint_descriptor_OUT.bDescriptorType	= 0x05; // 05h constant for Endpoint descriptor
USB_Endpoint_descriptor_OUT.bEndpointAddress	= 0x01; // 00000001b, Endpoint number=1, Bit 7=0=OUT 
USB_Endpoint_descriptor_OUT.bmAttributes	= 0x03; // Innterrupt transfer
USB_Endpoint_descriptor_OUT.wMaxPacketSize	= 0x0040;// 64 bytes max packet size
USB_Endpoint_descriptor_OUT.bInterval		= 0x0A;	// Interval 10 ms

endpoint_descriptor USB_Endpoint_descriptor_IN;

USB_Endpoint_descriptor_IN.bLength		= 0x07;	// Descriptor size in bytes
USB_Endpoint_descriptor_IN.bDescriptorType	= 0x05;	// 05h constant for ENDPOINT descriptor
USB_Endpoint_descriptor_IN.bEndpointAddress	= 0x81;	// 10000001b, Endpoint number=1, Bit 7=1=IN
USB_Endpoint_descriptor_IN.bmAttributes		= 0x03; // Interrupt transfer
USB_Endpoint_descriptor_IN.wMaxPacketSize	= 0x0040;// 64 bytes max packet size
USB_Endpoint_descriptor_IN.bInterval		= 0x0A;	// Interval 10 ms

string_descriptor USB_String_Manufacturer;

USB_String_Manufacturer.bLength 		= sizeof (USB_String_Manufacturer);
USB_String_Manufacturer.bDescriptorType 	= 0x03;	// 03h constant for STRING descriptor
USB_String_Manufacturer.bSTRING[8]		= 'P','i','n','g','u','i','n','o';

string_descriptor USB_String_Product;

USB_String_Product.bLength			= sizeof (USB_String_Product);
USB_String_Product.bDescriptorType		= 0x03;
USB_String_Product.bSTRING[14]			= 'H','I','D',' ','B','o','o','t','l','o','a','d','e','r';

string_descriptor USB_String_Serial;

USB_String_Serial.bLength			= sizeof (USB_String_Serial);
USB_String_Serial.bDescriptorType		= 0x03;
USB_String_Serial.bSTRING[4]			= 'v','1','.','0';

U1PWRCbits.USBPWR = 1; 	// - Start USB clock
			// - Allow USB interrupt to be activated
			// - Select USB as owner of the necessary USB pins
			// - Enable USB transciever
			// - Enable USB comparators
IEC1bits.USBIE = 0;	// Just in case, disable USB interrupts before initialization

U1OTGCONbits.OTGEN = 0;	// Disable OTG
U1CONbits.HOSTEN = 0;	// Disabled as host

buffer_descriptor USB_BDT[12] __attribute__ ((aligned(512)))={0};

U1CONbits.USBEN = 1;	// Enable USB

}