// Based on Purdue-SoCET AFT-dev/blob/master/sw-tests/support/pal.h

#ifndef USB_PALH_H_
#define USB_PALH_H_

#include <stdint.h>

// IO definitions
#define __I  volatile const // Defines 'read-only' permissions
#define __O  volatile       // Defines 'write-only' permissions
#define __IO volatile       // Defines 'read/write' permissions

// TEMPORARY 0x00000000 MEMORY LOCATION
#define USB_BASE ((uint32_t)0x00000000)

// USBRegBlk *USB = (USBRegBlk *) USB_BASE;

// USB register block
typedef struct {
    __IO uint32_t USB_CTRL;
    /*
    OTHER REGISTERS HERE...
    */
} USBRegBlk;

#endif /* USB_PALH_H_ */