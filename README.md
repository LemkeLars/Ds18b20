# DS18B20 Temperature Sensor Library for Mbed

This library is designed for the DS18B20 temperature sensor, optimized for use with Mbed controllers. It allows easy and quick reading of temperature values from the sensor in your Mbed project.

## Installation

To use this library, add the "DS18B20" directory to your Mbed project and import the library into your program.

## Structure

The library consists of a source file `Ds18b20.cpp` and a header file `Ds18b20.h` located in the `src` directory of the repository.

### `Ds18b20.cpp`

This file contains the implementation of the DS18B20 library. The important methods include:

- `Ds18b20(PinName pin)`: The constructor for the DS18B20 object which takes a pin name as input.
- `reset()`: This method sends a reset signal to the sensor and checks the response.
- `writeBit(int bit)`: This method sends a bit to the sensor.
- `readBit()`: This method receives a bit from the sensor.
- `writeByte(int byte)`: This method sends a byte to the sensor.
- `readByte()`: This method receives a byte from the sensor.
- `start()`: This method starts a temperature measurement on the sensor.
- `readTemperature()`: This method reads the temperature from the sensor.

### `Ds18b20.h`

This file contains the definition of the DS18B20 class and the methods implemented in `Ds18b20.cpp`.

## Examples

In the "examples" folder, you can find an example project that demonstrates how to use the library.

## License

This project is licensed under the MIT license. Please see the `LICENSE.md` file for more details.

**Note:** Some parts of the code and comments are in German. You may need to use a translation tool if you are not familiar with the language.
