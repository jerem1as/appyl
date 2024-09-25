# APPYL (Aparato para pisar y leer)

This project was created to make it easier to read sheet music on a tablet, allowing you to turn pages simply by stepping on a pedal. It is a useful tool for musicians who need to turn pages without using their hands, optimizing their performance in live shows or rehearsals.

## Inspiration

I strongly believe in collaboration and open source. My intention in sharing this project is to allow anyone interested to build their own page-turning pedal for sheet music, freely and accessibly. By releasing this code, I hope more people can customize, improve, and adapt it to their needs, thus contributing to the spirit of community and free access to knowledge.

> "Open source unites us and allows us to build a better future together."

## Main Classes

### 1. `Footswitch`
This class manages the behavior of the foot pedal. It is responsible for reading the state of the buttons connected to the ESP32 and translating those actions into commands to turn the page on the tablet. It also supports the "inverse mode" functionality, where the pedal's behavior changes after a prolonged action.

- **Key functions**:
  - `getStatus()`: Returns the current state of the buttons.
  - `executeAction()`: Executes the action assigned to the button based on its current state.

### 2. `KeyMap`
Defines the key mapping configuration for Bluetooth, allowing the ESP32 to act as a keyboard that sends the correct commands to the tablet.

- **Key functions**:
  - `getAction(key)`: Returns the action assigned to a specific key.

### 3. `LedManager`
Manages the LEDs connected to the ESP32. These LEDs can be used to show the status of the device, indicating whether it is active or in configuration mode.

- **Key functions**:
  - `hit(pin, duration)`: Turns on an LED at the specified pin for a certain amount of time.
  - `titilar(pin, interval)`: Makes the LED at the specified pin blink at regular intervals.

### 4. `Preference_Manager`
This class is responsible for saving and retrieving the device's preferences, such as the actions assigned to the buttons and the state of the inverse mode. It uses the ESP32's internal storage system.

- **Key functions**:
  - `getPreference(key)`: Retrieves the value of a stored preference.
  - `setPreference(key, value)`: Saves a preference.

### 5. `WebPortal`
This class provides a web interface to configure the pedal. Users can connect to the ESP32 via Wi-Fi and easily change the device's preferences.

- **Key functions**:
  - `begin()`: Starts the web portal.
  - `handleClient()`: Handles requests from connected clients.

## How to Use This Project

1. Clone the repository to your local machine.
2. Set up the ESP32 with the appropriate connections for the buttons, LEDs, and Bluetooth interface.
3. Upload the code to the ESP32 using the Arduino tool or PlatformIO.
4. Connect your ESP32 to the tablet via Bluetooth and start using the pedal to turn pages.

## Requirements

- ESP32
- Buttons and LEDs
- Tablet with Bluetooth capability
- Basic electrical connections

## To Do

- **Convert Footswitch to a template**: Adapt the `Footswitch` class to function as a template, allowing for different types of behavior or hardware, for example, a version with footswitch buttons instead of regular buttons.
- **Treat buttons and LEDs as arrays**: Refactor the code to handle buttons and LEDs as arrays, making it easier to create devices with more or fewer buttons and LEDs without significant changes to the base code.
- **Allow brightness adjustment or turn off lights from the configuration**: This could possibly be done with a combination of key presses and handled from Footswitch. We’ll see.

## Known Issues

- **LED 2 blinks only once when changing modes**: When switching between modes, LED 2 should blink repeatedly, but currently, it only blinks once. This unexpected behavior has not yet been resolved.

## Contributions

Contributions are welcome. Feel free to fork this project, submit a pull request, or open issues for any improvements or problems you find.
