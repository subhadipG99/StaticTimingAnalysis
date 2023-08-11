# StaticTimingAnalysis
In this project we will calculate the delay of a circuit by performing static timing analysis (STA) on it. Each node of the graph corresponds to each gate of the circuit, while each edge denotes a wire connection.

# Circuit STA Tool

This repository contains a tool for performing Static Timing Analysis (STA) on circuits using NLDM (Normalized Delay Model) LUTs.

**FOR DETAILS: Check Project Description in Detail.pdf**

## Files

- `ReadLib.h`: Header file containing the class of objects for different gates parsed from NLDM LUTs.
- `ReadLibFunc.h`: Header file containing functions to read and write class objects from `ReadLib.h`.
- `RdCkt.cpp`: Main file that parses the circuit files and performs STA.
- `Project Description in Detail.pdf`: Full details of STA implementation, assumptions and everything in this file.

## Directories

- `Circuit Files`: This directory contains the circuit description files that you want to perform STA on.
- `NLDM LUT`: This directory contains sample NLDM (Normalized Delay Model) Look-Up Table files.

## Compilation and Execution


Follow these steps to compile and run the tool:

1. Compile the code using the provided Makefile:

2. Run the compiled executable with the NLDM filename and circuit filename as arguments:



## Example Usage

Replace nldm_file.txt with the filename of your NLDM file and circuit_file.txt with the filename of your circuit description file.

```bash
make
./sta nldm_file.txt circuit_file.txt

