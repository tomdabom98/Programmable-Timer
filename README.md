# Programmable-Timer
# Multi-User Board Game Timer (Arduino + TM1638)

A simple multi-user countdown timer prototype for turn-based board games.

## Demo
[Watch the timer demo](https://youtube.com/shorts/ls5030_OJig?feature=share)

# Multi-User Board Game Timer (Arduino + TM1638)

A simple multi-user countdown timer prototype for turn-based board games.  
The system displays the active player’s remaining time and plays a buzzer alert when their time reaches zero.

## Hardware
- Arduino Uno
- TM1638 LED & button module (TM1638plus library)
- Piezo buzzer
- Breadboard and jumper wires

## Wiring
TM1638 module:
- STB → D4
- CLK → D3
- DIO → D2

Buzzer:
- Signal → D10
- GND → GND

## Features
- Supports up to 4 users
- Adjustable countdown time
- Button-based user switching
- Interrupt-driven 1 Hz countdown
- Audible buzzer alert when time expires

## Controls
### Setup
- S8: enter user/time setup mode
- S1: increase time
- S2: decrease time
- S8: confirm and start

### During Operation
- S1: switch to user 1
- S2: switch to user 2
- S3: switch to user 3
- S4: switch to user 4

The LED above each display position indicates the active user.  
For example, when time is running for user 1, LED1 is on; for user 2, LED2 is on, and so on.

## How It Works
- Timer1 is configured to generate a 1 Hz interrupt.
- The interrupt decrements the active user’s remaining time.
- The main loop handles button input, display updates, and buzzer alerts.

## Known Limitations
- Prototype-level code structure; not yet organized into a full state machine.
- Pause/resume functionality not implemented.
- Button handling could be improved with debouncing and clearer state logic.
- Timer configuration was adapted from a previous Arduino Mega version and could be further optimized for the Uno.

## Future Improvements
- Add pause/resume feature.
- Refactor into a cleaner state-machine architecture.
- Non-blocking buzzer logic.
- Improve timer configuration and portability across boards.
- Enhanced user interface feedback.

## Library
- TM1638plus (Arduino library)

## Author
Thomas Williams  
Electrical Engineering Student
