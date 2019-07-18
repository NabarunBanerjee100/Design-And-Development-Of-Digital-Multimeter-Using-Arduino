# Design-And-Development-Of-Digital-Multimeter-Using-Arduino

The entire project can be divided into three basic blocks;

1)      Resistance/Diode/Continuity Sensor Unit

2)      AC/DC Voltage Sensor Unit

3)      DC Current Sensor Unit

4)      Power Sensor Unit

5)      hfeSensor Unit

6)      Capacitance Sensor Unit

7)      Processor Unit

8)      Display Unit

                                          

The Resistance/Diode/Continuity Sensor, Voltage Sensor, Current Sensor, Power Sensor, Capacitance Sensor and hfeSensor  produces output voltages proportional to Resistance/Diode/Continuity, Voltage, Current, Power, Capacitance and hferespectively.

The Processor Unit takes these voltages one by one and calculates the Resistance/Diode/Continuity Sensor, Voltage, Current, Power, Capacitance and hfe. The Processor Unit then sends data to the Display Unit to display the values.

The Display unit takes 4bit data from the Processor Unit and generates a 16*2 display for different measurement values.

 

1)      Resistance/Diode/Continuity Sensor Unit

A basic voltage divider [H7] circuit is used as the Resistance/Diode/Continuity Sensing Unit to provide an output, which is the voltage equivalent of the unknown resistor, diode or continuous path connected as the input. From this output voltage we cancalculate[H8] the value of unknown resistance, detect the diode type or detect a continuous path.

 

2)      AC/DC Voltage Sensor Unit

A basic voltage divider circuit[H9]  is used as the AC/DC Sensing Unit to scale down the input DC and AC voltages into a DC voltage in the range of 0 to 5 V. The Processor Unit can read this scaled down voltage and calculate[H10]  the actual AC/DC voltages.

 

3)      DC Current Sensor Unit

The Current Sensor in this project is a single low valued resistor through which the current flows to the load device. The basic principle of current measurement is based on the Ohm’s law.

In our project we implement such a resistor in the current flowing path whose resistance value is known. Then we measure the voltage at both the ends of the resistor to calculate[H11]  the current flow.

 

4)      Power Sensor Unit

The Power Sensor in this project is a single low valued resistor through which the current flows to the load device. The Voltage across the resistor and the current flow [H12] through the resistor are measured to calculate[H13]  the Power consumption of the device.

 

5)      hfe Sensor Unit

The hfe sensor in this project is actually two current sensors[H14] , one of them sense the input current (base current) of the transistor and other one sense the output current (collector current) of the transistor. The current sensors in this project are single low valued resistors through which the current flows to the transistor.

As the current flows through them, voltages get drops across them; we can measure these voltages to calculate[H15]  the input current, output current and the hfe.

 

6)      Capacitance Sensor Unit

The Capacitance sensor in this project is an RC discharging circuit in which the unknown capacitor is discharged through a known resistor. While the capacitor discharges the time taken for the capacitor to drop the voltage across it to half the voltage before it starts discharging is measured and from that time value the capacitance is calculated[H16] .

 

7)      Processor Unit

The processor unit in this project is the Arduino board and it uses the ADC module[H17]  to read the output voltages from the Sensor Unit. The processor unit then applies an algorithm for calculating the measure resistance, diode, continuity[H18] , voltage[H19] , current[H20] , power[H21] , hfe[H22]  and capacitance[H23] .The Processor Unit then sends the data to the Display Unit.

 

8)      Display Unit

The Display Unit is a standard 16*2 LCD on which the Arduino displays the resistance, diode, continuity, voltage, current, power, hfe and capacitance values. The LCD has been wired in four bit mode to reduce the number of output pins of the Arduino board to be used
