# Core Wars

# Introduction
Core Wars consists of programs that run in a virtual machine. Each program's objective is to execute a special instruction ("live"), within a specified number of cycles. These programs simultaneously execute in the virtual machine and in the
same memory zone, which enables them to write on one another.
The project is coded in C. 😎

The project is divided into three separate parts:

*Virtual Machine*
– This is the controlled environment where the programs will run. It must provide all essential features for program execution and support the simultaneous execution of multiple programs.

*Assembler*
– At the heart of the system, the assembler defines syntax and rules for creating valid programs. Its role is to produce binary code that the Virtual Machine can execute.

*Programs*
– These are the entities that run within the Virtual Machine and interact with it. Written in the specific assembly language tailored for the Virtual Machine, programs must execute within the VM's confines.
