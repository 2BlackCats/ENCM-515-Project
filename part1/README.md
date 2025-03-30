# README for PART 1 of ENCM515 Final Project

## Overview

This project implements an FIR filter system, designed for testing and processing audio samples. 
The system can be configured to test different modes of the filtering process, including circular buffer handling, MLA optimizations (using SMLABB), and frame-based processing.


## Configuration Modes
The system provides several configuration modes, each designed for different testing or processing scenarios. Two key macros, CONFIG_MODE and TEST_MODE, control the functionality of the system. These macros define the filter's processing configuration, and their combinations are outlined below.

### TEST_MODE = 1 ("Testing mode")
- CONFIG_MODE = 0:
Testing the circular buffer processor function without MLA optimization.
- CONFIG_MODE = 1:
Testing the circular buffer processing function with MLA optimization.
- CONFIG_MODE = 2:
Testing the frame-based processing function.
- CONFIG_MODE = 3:
Testing the frame-based processing function with MLA.


### TEST_MODE = 0 ("Normal operation mode")
- CONFIG_MODE = 0:
Processing with normal circular buffer
- CONFIG_MODE = 1:
Processing with circular buffer and MLA optimization.
- CONFIG_MODE = 2:
Frame-based processing with frame size of 3.
- CONFIG_MODE = 3:
Frame-based processing with frame size of 16.
- CONFIG_MODE = 4:
Frame-based processing with frame size of 3 and MLA optimization.
- CONFIG_MODE = 5:
Frame-based processing with frame size of 16 and MLA optimization.

## How to Configure
To configure the system, modify the TEST_MODE and CONFIG_MODE macros at the top of the source file. For example:

#define TEST_MODE 1  // Set to 1 for testing mode

#define CONFIG_MODE 3  // Set to the desired configuration mode


## Execution Flow of main() and RunTestMode()
All configuration modes pass through main(). Depending on the value of TEST_MODE, either the rest of main() runs for normal operation, or RunTestMode() is executed for testing.

### main() 
- Calls filter functions on real audio data.
- Stores/outputs filtered audio.


### RunTestmode()
- Calls filter functions on predefined test data.
- Displays results in SWV ITM Data Console.

## Viewing Outputs in Debugging Mode
When TEST_MODE is set to 1 for testing, you can view the outputs of the test cases in Debugging Mode using SWV ITM Data Console.
1. Start Debugging Mode.
2. Enable SWV (Serial Wire Viewer).
3. Open ITM Data Console.
4. Enable ITM Stimulus Port 0 in the SWV settings.
5. Ensure "Start Trace" is enabled.
6. Resume the code execution.
7. The test results should now show up on the Data Console panel.

## Compilation and Execution
1. Transfer the audio file "a440_32f.bin" to the STM32 board using STM32CubeProgrammer.
2. Build the project using STM32CubeIDE.
3. Run the program with the desired configurations in Debugging Mode.
4. In Live Expressions or SWV ITM Data Console, check the values of the output buffer to see how the filter processes the audio data.









