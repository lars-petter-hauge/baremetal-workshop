# Resources

## DE1-SoC

Resources that will help you when writing code for the DE1-SOC simulator

[DE1-SoC Computer Systemwith ARM* Cortex* A9](https://fpgacademy.org/Downloads/DE1-SoC_Computer_ARM.pdf "SoC documentation that contains sample programs and explains how to use I/O, like timers, video output, character buffer and more.")

[CPUIator I/O documentation](https://cpulator.01xz.net/doc/#io_devices "Documents the simulator. Lists supported I/O devices, features and more")

[ARM Architecture Reference Manual ARMv7-A and ARMv7-R edition](https://developer.arm.com/documentation/ddi0406/cd/?lang=en "See for example section A8.8 Alphabetical list of instructions")

[ARM developer - list of instructions](https://developer.arm.com/documentation/ddi0406/cb/Application-Level-Architecture/Instruction-Details/Alphabetical-list-of-instructions/ADD--register--ARM-?lang=en, "List of instructions on webpage, not in a PDF.")

[ARM developer - constant and immediate values](https://developer.arm.com/documentation/den0013/0400/ARM-Thumb-Unified-Assembly-Language-Instructions/Instruction-set-basics/Constant-and-immediate-values)

[ARM developer - status flags and condition codes](https://developer.arm.com/documentation/den0013/0400/ARM-Thumb-Unified-Assembly-Language-Instructions/Instruction-set-basics/Status-flags-and-condition-codes)

## Conversion tools

Conversion tool and lookup tables that might come in handy when working with the hexadecimal values found in content of registers and memory of simulator.

[Hexdecimal to binary](https://www.rapidtables.com/convert/number/hex-to-binary.html, "Registers and memory shows content as hexadecimal, and it is useful to see the binary pattern of zeros and ones stored, like the timer where certain bits configure timer, or leds where bits turn on and off leds")

[Hexdecimal to decimal](https://www.rapidtables.com/convert/number/hex-to-decimal.html, "And again content is stored as hexadecimals, here is a tool to convert to decimals. You can display content of memory in simulator as decimals as well.")

[Conversion table binary/hexadecimal/decimal](https://www.bbc.co.uk/bitesize/guides/zd88jty/revision/4, "When writing assembly code a quick lookup table can be useful. I need to store the binary pattern 1011 in register R0, what is the hexadecimal for that?")

## Chat.equinor.com

Prompting [chat.equinor.com](https://chat.equinor.com) can be a good way to learn the basics of assembly programming, and how use the DE1-SoC.

Try to explain your experience level, what SoC you are targetting and ask it to create a guide for you. Something like:

`I am new to ARM programmming and computer architecture. I am learning to use DE1-SoC and want to learn assembly programming. Help me by creating a guided tutorial, that explains the basics. I use https://cpulator.01xz.net`
