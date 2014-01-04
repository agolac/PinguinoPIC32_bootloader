__attribute__ ((interrupt)) void USB_Handle_Interrupt (void);
__attribute__ ((section(".vector_45"))) void USB_ISR_Wrapper_vector_45 (void);
void InitUSB (void);
