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

#include <usb_chapter_9.h>
#include <stdint.h>
#include <xc.h>
#include <usb_hal.h>
#include <config.h>
#include <usb.h>
#include <cp0defs.h>
#include <regdef.h>
void InitUSB (void) {

device_descriptor USB_Device_descriptor;

USB_Device_descriptor.bLength 			= 0x12;   // Descriptor size in bytes
USB_Device_descriptor.bDescriptorType 		= DEVICE;
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
USB_Configuration_descriptor.bDescriptorType	= CONFIGURATION;
USB_Configuration_descriptor.wTotalLength	= 0x29;// Total length of this and subordinate descript.
USB_Configuration_descriptor.bNumInterfaces	= 0x01; // 01h for only one interface
USB_Configuration_descriptor.bConfigurationValue= 0x01; // 01h for this configuration
USB_Configuration_descriptor.iConfiguration	= 0x00; // Zero if no string descriptor
USB_Configuration_descriptor.bmAttributes	= 0x80; // Bus powered,no remote wakeup,bit7 USB1.0 compa
USB_Configuration_descriptor.bMaxPower		= 0xFA; // (2mAx250)=2xFAh=max 500 mA

interface_descriptor USB_Interface_descriptor;

USB_Interface_descriptor.bLength		= 0x09; // Descriptor size in bytes
USB_Interface_descriptor.bDescriptorType	= INTERFACE;
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
USB_Endpoint_descriptor_OUT.bDescriptorType	= ENDPOINT;
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


static buffer_descriptor USB_BDT[12] __attribute__ ((aligned(512)))={0};
uint32_t USB_BDT_BASE_ADDRESS;
USB_BDT_BASE_ADDRESS = VIRTUAL_TO_PHYSICAL(USB_BDT); // Must be physical address

// According to PIC32 Family Reference manual BDT base address is split between three registers
// Following registers hold base address bits:
//
// BDTPTRL (7 bit with bit 0 unimplemented) - Address bits 15-9
// BDTPTRH (8 bit value) - Address bits 23-16
// BDTPTRU (8 bit value) - Address bits 31-24
// So, 9 bits of BDT_BASE address are discarded
U1BDTP1bits.BDTPTRL = (USB_BDT_BASE_ADDRESS >> 8);
U1BDTP2bits.BDTPTRH = (USB_BDT_BASE_ADDRESS >> 16);
U1BDTP3bits.BDTPTRU = (USB_BDT_BASE_ADDRESS >> 24);

USB_BDT[0].ControlFormat.DTS = 1;
USB_BDT[0].ControlFormat.UOWN = 1;
USB_BDT[1].ControlFormat.DTS = 1;
USB_BDT[1].ControlFormat.UOWN = 1;

U1EP0bits.EPRXEN = 1;
U1EP0bits.EPTXEN = 1;
U1EP0bits.EPHSHK = 1;
U1EP0bits.EPSTALL= 0;
U1EP1bits.EPRXEN = 1;
U1EP1bits.EPTXEN = 1;
U1EP1bits.EPHSHK = 1;
U1EP2bits.EPRXEN = 1;
U1EP2bits.EPTXEN = 1;

}

void InitializeUSB (void) {

	U1IE = 0;

	U1PWRCSET = _U1PWRC_USBPWR_MASK; 	// - Start USB clock
						// - Allow USB interrupt to be activated
						// - Select USB as owner of the necessary USB pins
						// - Enable USB transciever
						// - Enable USB comparators
	U1OTGCONCLR = _U1OTGCON_OTGEN_MASK;	// Disable OTG
	U1CONCLR = _U1CON_HOSTEN_MASK;		// Disabled as host
	INTCONSET = _INTCON_MVEC_MASK;
	IPC11SET = 7 << _IPC11_USBIP_POSITION;
	IFS1CLR = _IFS1_USBIF_MASK;
	IEC1SET = _IEC1_USBIE_MASK;
	U1CONSET = _U1CON_USBEN_MASK;	// Enable USB
	U1IE = 0xFF;
}

void __attribute__((interrupt)) USB_Interrupt_Handler (void) {
      
	IFS1CLR = _IFS1_USBIF_MASK;
	TRISGCLR = _PORTG_RG6_MASK;
        PORTGSET = _PORTG_RG6_MASK;
}

void __attribute__((section(".vector_45"))) ISR_USB_vector_45(void) {
	USB_Interrupt_Handler();
}
