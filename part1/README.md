# README for PART 1 of ENCM515 Final Project

## Overview

This project implements an FIR filter system, designed for testing and processing audio samples. 
The system can be configured to test different modes of the filtering process, including circular buffer handling, MLA optimizations, and frame-based processing.


## Configuration Modes
The system provides several configuration modes, each designed for different testing or processing scenarios. Two key macros, CONFIG_MODE and TEST_MODE, control the functionality of the system. These macros define the filter's processing configuration, and their combinations are outlined below.

### TEST_MODE = 1 - Indicates testing.
- CONFIG_MODE = 0:
Testing the circular buffer processor function without MLA optimization.
- CONFIG_MODE = 1:
Testing the circular buffer processing function with MLA optimization.
- CONFIG_MODE = 2:
Testing the frame-based processing function.
- CONFIG_MODE = 3:
Testing the frame-based processing function with MLA.




