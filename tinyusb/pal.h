#ifndef USB_PAL_H_
#define USB_PAL_H_

#include <stdint.h>

#define __IO volatile
#define __I  volatile const

/* Bitfield definition for USB_CTRL register */
typedef struct {
    uint32_t enable_sof     : 1;  /* Bit 0: Enable SOF generation */
    uint32_t phy_opmode     : 2;  /* Bits 1-2: UTMI PHY Output Mode */
    uint32_t phy_xcvrselect : 2;  /* Bits 3-4: UTMI PHY Transceiver Select */
    uint32_t phy_termselect : 1;  /* Bit 5: UTMI PHY Termination Select */
    uint32_t phy_dppulldown : 1;  /* Bit 6: UTMI PHY D+ Pulldown Enable */
    uint32_t phy_dmpulldown : 1;  /* Bit 7: UTMI PHY D- Pulldown Enable */
    uint32_t tx_flush       : 1;  /* Bit 8: Flush Tx FIFO */
    uint32_t reserved       : 23; /* Remaining bits */
} usb_ctrl_bits_t;

/* Bitfield definition for USB_XFER_TOKEN register */
typedef struct {
    uint32_t reserved1      : 5;  /* Bits 0-4 */
    uint32_t ep_addr        : 4;  /* Bits 5-8: Endpoint address */
    uint32_t dev_addr       : 7;  /* Bits 9-15: Device address */
    uint32_t pid_bits       : 8;  /* Bits 16-23: Token PID (SETUP, OUT, IN) */
    uint32_t reserved2      : 4;  /* Bits 24-27 */
    uint32_t pid_datax      : 1;  /* Bit 28: DATA1 or DATA0 */
    uint32_t ack            : 1;  /* Bit 29: Send ACK in response to IN data */
    uint32_t in_xfer        : 1;  /* Bit 30: IN (1) or OUT (0) */
    uint32_t start          : 1;  /* Bit 31: Transfer start request */
} usb_token_bits_t;

/* Main Register Map using Unions  */
typedef struct {
    union {
        __IO uint32_t val;
        __IO usb_ctrl_bits_t bits;
    } CTRL;                       /* 0x00 */

    __I  uint32_t STATUS;         /* 0x04 */
    __IO uint32_t IRQ_ACK;        /* 0x08 */
    __I  uint32_t IRQ_STS;        /* 0x0C */
    __IO uint32_t IRQ_MASK;       /* 0x10 */
    __IO uint32_t XFER_DATA;      /* 0x14 */

    union {
        __IO uint32_t val;
        __IO usb_token_bits_t bits;
    } XFER_TOKEN;                 /* 0x18 */

    __I  uint32_t RX_STAT;        /* 0x1C */
    __IO uint32_t DATA;           /* 0x20 */
} USB_Host_Type;

#define USB_HOST_BASE   ((uint32_t)0x40001000) 
#define USB_HOST        ((USB_Host_Type *) USB_HOST_BASE)

#endif