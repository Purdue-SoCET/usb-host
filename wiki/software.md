# Software

## TinyUSB Full Stack

![Software Stack](/wiki/img/TinyUSB_software_diagram.png)

This semester, the software team primarily focused on developing the **Host Controller Driver (HCD)**, which abstracts the RTL register interface for integration with the **TinyUSB core host stack**.

TinyUSB defines a hardware agnostic API for host controllers. Platform specific implementations are provided by implementing the required HCD functions declared in `hcd.h` and defined in a corresponding `hcd.c` file.

---

## Host Controller Driver (HCD)

### Overview

* `hcd.h`

  * Part of the TinyUSB stack
  * Declares all required HCD API functions
  * These functions must be implemented by the platform-specific driver

* `hcd.c`

  * Platform-specific implementation of the HCD API
  * Handles:

    * Register-level access to the USB host controller
    * Interrupt handling
    * Port and endpoint control
    * Transfer scheduling and completion signaling

The detailed behavior of each HCD function are documented in the **[USB Host SharePoint](https://purdue0.sharepoint.com/:w:/r/sites/ENGR-ECE-O-SOCET/Shared%20Documents/Digital%20Design/USB%20Host/TinyUSB%20HCD%20Overview.docx?d=w137dc7b049ed4a36886c0a4508d2c5c2&csf=1&web=1&e=AwrBZi)**.

---

## Platform Abstraction Layer (PAL)

![pal.h](/wiki/img/pal.png)

### `pal.h`

The HCD implementation interfaces with hardware registers

* Located in the USB host directory
* Currently very barebones
* Mimics the structure and definitions found in the `AFT-dev pal.h`
* Provides:

  * Base addresses
  * Register offsets
  * Low-level read/write accessors

At this stage, registers are accessed directly using macros and raw values.

### Future Improvements

* Introduce **bitfield definitions** for important registers
* Goals:

  * Improve readability
  * Reduce errors when manipulating control/status bits
  * Simplify register access in `hcd.c`

---

## Proof-of-Concept Functions

Several functions have already been implemented as proof-of-concept to validate:

* Correct register access
* Basic interaction with the TinyUSB core
* Feasibility of control transfer setup and enumeration flow

These implementations serve as early scaffolding and will be refined as the PAL matures.

---

## Key Functions to be Implemented in `hcd.c`

![hcd.h](/wiki/img/hcd.png)

### Driver Configuration

Functions responsible for:

* Initializing the host controller hardware
* Resetting internal state
* Enabling required clocks and interrupts
* Registering the HCD with the TinyUSB core

### Interrupt Handling

* Top-level interrupt handler invoked by the platform
* Responsibilities include:

  * Reading interrupt status registers
  * Clearing interrupt flags
  * Dispatching events to the TinyUSB core
  * Signaling transfer completion and error conditions

---

## Control Transfers and Enumeration (Core Calls)

![enum_req.png](/wiki/img/enum_req.png)

The HCD must support the TinyUSB core during device enumeration, including:

* Creating and submitting **control transfers**
* Managing **descriptor requests**, such as:

  * Device descriptor
  * Configuration descriptor
  * String descriptors
* Supporting the sequence of operations required for:

  * Device reset
  * Address assignment
  * Configuration selection

These flows are initiated by the TinyUSB core and rely on the HCD for correct low-level execution.

---

## `hcd.c` Functions for Port Access

![hcd_port.png](/wiki/img/hcd_port.png)

Port-related APIs provide control over the physical USB port, including:

* Port reset and power control
* Connection and disconnection detection
* Speed detection (low/full/high speed, as supported)
* Reporting port status changes back to the TinyUSB core

These functions translate TinyUSB port commands into appropriate register operations.

---

## `hcd.c` Functions for Endpoint Control

![hcd_edpt.png](/wiki/img/hcd_edpt.png)


Endpoint-related APIs handle communication channels between the host and device:

* Endpoint allocation and deallocation
* Endpoint configuration:

  * Endpoint type (control, bulk, interrupt, isochronous)
  * Direction (IN/OUT)
  * Maximum packet size
* Transfer submission and cancellation
* Handling endpoint-level errors and stalls

These functions form the core interface between TinyUSB’s transfer scheduler and the underlying hardware.

---