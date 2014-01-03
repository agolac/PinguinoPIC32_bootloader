__attribute__ ((interrupt)) void USB_Handle_Interrupt (void);
__attribute__ ((section(".vector_57"))) void USB_ISR_Wrapper_vector_57 (void);
void InitUSB (void);
