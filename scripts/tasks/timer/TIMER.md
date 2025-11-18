# Timer
The ARM A9 core incudes a private timer module that you can interact with in the simulator.

- At base address `0xFFFEC600` in memory.
- You Can read and write to it.
- To use a timer:
  - Write initial count value into Load register
  - Start and stop timer by enable bit E in Control register.
  - When enabled timer will decrement until it reaches zero.
  - At zero it sets the F bit in the Interrupt status register.
  - Code can chech F bit by polling when timer period has expired.
  - Timer has a clock frequency of 200 MHz.
  - prescaler field in control register can slow down counting rate.