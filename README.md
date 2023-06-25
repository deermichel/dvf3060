# dvf3060
I picked up an old Kenwood DVF-3060 DVD player and decided to reverse engineer the front panel for a future project.
The panel features a fancy vacuum fluorescent display (VFD) and some buttons, all controlled through a PT6311 (or UPD16311) IC.
This repo contains the driver I wrote for a Cortex-M based TI eval board (TM4C123G LaunchPad) to communicate with the controller via SPI.

## Features

## How to
The project runs out of the box with PlatformIO and comes with a [timer example](src/main.cpp).

The pinout is configured as follows (make sure your board supports **5V logic levels!**):

## Example

## Implementation
There are several abstraction layers that allow you to easily port the driver to a new platform or similar display configurations.
- HAL (hardware abstraction layer): Contains platform-specific code to make upper layers work regardless of the underlying platform (TM4C123 in my case). To port this driver to a new platform (e.g., Arduino or RP2040), implement the required methods (see [tm4c.h](src/tm4c.h) as a reference).
- Controller layer: This implements the SPI protocol as specified in the IC datasheet by using the HAL methods. For use with the DVF-3060 front panel, only PT6311 is relevant, but related controllers like the PT6312 can be supported in a similar fashion.
- Display layer: This is the frontend part of the driver which allows simplified control over characters and icons. It is based on the controller layer and comes with a predefined [ASCII font](src/dvf3060_font.h).

## Related

## License
This project is released under the [MIT License](LICENSE).
