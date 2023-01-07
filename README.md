# Sun-Earth-Moon System
This project shows the simplified version of a Sun-Earth-Moon model using the Leapfrog Integrator. This program runs dynamically so the user only has to send a file which has the planet's mass, x-value, y-value, vx value and vy value initialized. Also, I made it easier for the user to choose the default files which already have the values predefined.
# Run
To run the program you need C++ compiler and pgplot. 
To add your own dat file the format should be:

---
    Number of Planets
    Sun Mass Sun x-value Sun y-value Sun vx-value Sun vy-value
    Earth Mass Earth x-value Earth y-value Earth vx-value Earth vy-value
    Moon Mass Moon x-value Moon y-value Moon vx-value Moon vy-value
    Planet Mass Planet x-value Planet y-value Planet vx-value Planet vy-value
---

The Moon and another Planet is optional so it will still work without it. 

The energy and angular momentum of the system are also calculated with `energy()`, `angularM()` functions

If you were to input "2" in the program you will get the plot of `input3.dat` which will look like: 

![image](https://user-images.githubusercontent.com/64769412/211129039-69fc1d0d-cd6b-4ea1-a074-651fd6302399.png) 

Sun-Earth-Moon Model (Sun: Yellow, Earth: Blue, Moon: White)

![image](https://user-images.githubusercontent.com/64769412/211129122-032deaf0-0c16-484d-a813-ea85fa72c051.png)

Close-Up of Sun-Earth-Moon Model (Sun: Yellow, Earth: Blue, Moon: White)

To see why and how it works check `Project.pdf`

