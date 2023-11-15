## Smart Home Project
The Project was done as Application on RTOS Module in 4 months Automotive embdded system in [NTI](https://www.nti.sci.eg/) under supervise ENG/Ahmed Atia.

This is a simple smart home system, done using **FreeRTOS** and **Atmega32** microcontroller and the **targed** is Apply how to divid the application into tasks and how make Synchronization between tasks and how to protect shared resources .
## System Overview
 The system starts by ask the user to enter password. The password is has a maximum of three attempts to enter the correct If the maximum number of attempts is exceeded, the buzzer is activated as a warning and the system is power off and if the user entered the correct password the system start to measure The LM35 temperature sensor and uses this information to control a speed of a fan and showing the fan state speed on LCD
 
## project simulation vedio

https://github.com/Mahmoud-Ismail98/coursera-introduction-embedded-systems-software-and-development-environments/assets/63348980/5d5cf581-860b-45ce-ac35-f3e6106d4e10

## System Behavior
## The System has 5 tasks These are:
1. INIT_Task: intialization task take the highst perority in the system that resposiable of intialize some resourse in the system then terminate
2. KeyPad_Task: The password is entered by the user using the keypad The    user has 3 attempts to enter the password. If the password is incorrect, the system will be in alarm mode and the system will not response
If the password is correct, the system will be in normal mode and the door will be opened.
3. Buzzer_Task:this task is run in case user exceeded the maximum number of attemps in entering the correct password the task work the buzzer 
4. TEMP_Task :task hat fire after keyPad_Task is finish and this task will start to run ADC in asynchrons mode and passed TempNotificatonRead function to ADC to update reading from temperture LM35 sensor
5. Fan_Task:task is responsible turn on FAN with speed various depend on updated reading temperture sensor and resposible show the state of FAN speed on LCD

## hardware components

- Atmega32 : The Atmega32 microcontroller acts as the main processing unit, responsible for coordinating the inputs from the sensors and controlling the actuators.

- LCD : The LCD   is used to show information such a temperature and Fan speed 

- Keypad: The keypad serves as the input interface for the user to enter the password.

- LM35 Temperature Sensor: The LM35 temperature sensor measures the temperature of the home environment.

- Buzzer: The buzzer is used to provide audio feedback, such as indicating incorrect login attempts.

- Fan DC Motor: The Fan DC motor work with speed varios and depend on the reading tempeture sensor .

