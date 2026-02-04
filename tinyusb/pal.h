#ifndef USB_PAL_H_
#define USB_PAL_H_

#include <stdint.h>

/* Use volatile to ensure the compiler does not optimize out hardware accesses. */
#define __IO volatile
#define __I  volatile const
#define __O  volatile

/*
 * USB Host Controller Register Map
 * The structure members must match the hardware offsets exactly.
 */
typedef struct {
    __IO uint32_t CTRL;          /* 0x00: Control of USB reset, SOF, and FIFO flush */
    __I  uint32_t STATUS;        /* 0x04: Line state, Rx error status, and frame time */
    __O  uint32_t IRQ_ACK;       /* 0x08: Acknowledge IRQ by setting relevant bit */
    __I  uint32_t IRQ_STS;       /* 0x0c: Interrupt status */
    __IO uint32_t IRQ_MASK;      /* 0x10: Interrupt mask */
    __IO uint32_t XFER_DATA;     /* 0x14: Tx payload transfer length */
    __IO uint32_t XFER_TOKEN;    /* 0x18: Transfer control info (direction, type) */
    __I  uint32_t RX_STAT;       /* 0x1c: Transfer status (Rx length, error, idle) */
    __IO uint32_t DATA;          /* 0x20: FIFO Data (WR_DATA for write, RD_DATA for read) */
} USB_Host_Type;

/* Placeholder for the IP base address on your AHB bus. */
#define USB_HOST_BASE            ((uint32_t)0x00000000) 
#define USB_HOST                 ((USB_Host_Type *) USB_HOST_BASE)

/* --- Register Bit Definitions --- */

/* USB_CTRL Bits */
#define USB_CTRL_TX_FLUSH        (1u << 8)
#define USB_CTRL_PHY_DMPULLDOWN  (1u << 7)
#define USB_CTRL_PHY_DPPULLDOWN  (1u << 6)
#define USB_CTRL_PHY_TERMSELECT  (1u << 5)
#define USB_CTRL_PHY_XCVR_SEL_M  (0x3u << 3)
#define USB_CTRL_PHY_OPMODE_M    (0x3u << 1)
#define USB_CTRL_ENABLE_SOF      (1u << 0)

/* USB_IRQ Bits (ACK, STS, and MASK) */
#define USB_IRQ_DEVICE_DETECT    (1u << 3)
#define USB_IRQ_ERR              (1u << 2)
#define USB_IRQ_DONE             (1u << 1)
#define USB_IRQ_SOF              (1u << 0)

/* USB_XFER_TOKEN Bits */
#define USB_XFER_START           (1u << 31)
#define USB_XFER_IN              (1u << 30)
#define USB_XFER_ACK             (1u << 29)
#define USB_XFER_PID_DATAX       (1u << 28)
#define USB_XFER_PID_BITS_M      (0xFFu << 16)
#define USB_XFER_DEV_ADDR_M      (0x7Fu << 9)
#define USB_XFER_EP_ADDR_M       (0xFu << 5)

/* USB_RX_STAT Bits */
#define USB_RX_STAT_START_PEND   (1u << 31)
#define USB_RX_STAT_CRC_ERR      (1u << 30)
#define USB_RX_STAT_RESP_TIMEOUT (1u << 29)
#define USB_RX_STAT_IDLE         (1u << 28)
#define USB_RX_STAT_RESP_PID_M   (0xFFu << 16)
#define USB_RX_STAT_COUNT_M      (0xFFFFu << 0)

#endif /* USB_PAL_H_ */