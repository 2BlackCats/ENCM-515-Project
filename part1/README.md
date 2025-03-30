# README for PART 1 of ENCM515 Final Project

## Overview

This project implements an FIR filter system, designed for testing and processing audio samples. 
The system can be configured to test different modes of the filtering process, including circular buffer handling, MLA optimizations, and frame-based processing.


## Configuration Modes
The system provides several configuration modes, each designed for different testing or processing scenarios.
There are two macros that influence the code: "CONFIG_MODE" and TEST_MODE. The combinations of these 2 variables
and their outcomes are explained below.

### TEST_MODE 1
Indicates testing.
#### CONFIG_MODE 0
Testing the circular buffer without MLA optimization.

