// Libraries 
#include <cmath>
#include <iostream>
#include <fstream>
#include <string.h>
#include "cpgplot.h"

using namespace std;

// Planets class to define the values for each planet
class Planets
{
    public:
        double mass;
        double x;
        double y;
        double vx;
        double vy;
};

// Solar System class to initialize the values for all the planets 
class SolarSystem
{
    public:
        // Number of Planets
        int n;
        // Pointer p to the Planets Class
        Planets *p;

        SolarSystem(const char* fileName)
        {
            ifstream inputfile;

            // Opens the file
            inputfile.open(fileName);

            // Checks if the file can be opened 
            if(!inputfile.is_open())
	    {
		cout << "Unable to open file" << endl;
	    }
            // First value in the file is number of planets
            inputfile >> n;
            p = new Planets[n];

            // Initializes all the values for the planets 
            for (int i = 0; i < n; i++)
            {
                inputfile >> p[i].mass;
                inputfile >> p[i].x;
                inputfile >> p[i].y;
                inputfile >> p[i].vx;
                inputfile >> p[i].vy;
                // Checks if any of the inputs fails
                if (inputfile.fail())
		{
		   cout << "Read incomplete at line: " << i << endl;
                }
            }
            // Closes the input file
            inputfile.close();
        }
};

// Computes the Energy
double energy(SolarSystem &solarS, double g)
{
    // Variables
    double r_ij[solarS.n];
    double r_ij2 = 0;
    double r_ij3;
    double KE = 0;
    double PE = 0;

    // Loops through all the planets
    for (int i = 0; i < solarS.n; i++)
    {
        // Computes the Kinetic Energy
        KE += 0.5 * solarS.p[i].mass * (solarS.p[i].vx * solarS.p[i].vx + solarS.p[i].vy * solarS.p[i].vy);

        // For all planets that is not itself
        for (int j = i; j < solarS.n; j++)
        {
            if (i != j)
            {
                // Loops through all the planets 
                for (int x = 0; x < solarS.n; x++)
                {
                    r_ij[x] = solarS.p[i].x - solarS.p[j].x;
                    r_ij2 += r_ij[x] * r_ij[x]; 
                }
                r_ij3 = pow(r_ij2, 0.5);

                // Computes the Potential Energy
                PE -= g * solarS.p[i].mass * solarS.p[j].mass / r_ij3;
            }
        }   
    }

    return KE + PE;
}

// Computes the Angular Momentum
double angularM(SolarSystem &solarS)
{
    // Variables
    double L = 0;
    double originX = 0;
    double originY = 0;

    // Loops through all the planets 
    for (int i = 0; i < solarS.n; i++)
    {
        // Computes the L value
        L += solarS.p[i].mass * (((solarS.p[i].x - originX) * solarS.p[i].vy) - ((solarS.p[i].y - originY) * solarS.p[i].vx));
    }

    return L;
}

// Updates the Coordinates using LeapFrog Integrator 
void updateCoord(double h, SolarSystem solarS)
{
    // For all planets update the coordinates
    for (int i = 0; i < solarS.n; i++) 
    {
        solarS.p[i].x += h * solarS.p[i].vx;
        solarS.p[i].y += h * solarS.p[i].vy;
    }  
}

// Updates the Velocity using LeapFrog Integrator 
void updateVelocity(double h, SolarSystem solarS, double g)
{
    // Variables
    double r_ij[2];
    double r_ij2;

    // For all planets that is not itself
    for (int i = 0; i < solarS.n; i++) 
    {   
        for (int j = 0; j < solarS.n; j++)
        {
            if (j != i)
            {
                r_ij2 = 0;

                r_ij[0] = solarS.p[i].x - solarS.p[j].x;
                r_ij[1] = solarS.p[i].y - solarS.p[j].y;
                r_ij2 = r_ij[0] * r_ij[0] + r_ij[1] * r_ij[1];

                double r_ij3 = pow(r_ij2, 1.5);
                solarS.p[i].vx -= h * g * solarS.p[j].mass * r_ij[0] / r_ij3;
                solarS.p[i].vy -= h * g * solarS.p[j].mass * r_ij[1] / r_ij3;
            }
        }
    }
}

int main()
{
    // Gravity
    const double g = 1.0;

    // Time Step
    double h = 0.01;

    // Number of Iterations
    int n = 4000;

    // Earth's Orbits
    int orbits = 0;

    // Variables
    string s;
    int cases;

    // User Input
    cout << "Enter (0) to input file with 2,3 or 4 planets " << endl;
    cout << "Enter (1) for Sun-Earth Orbits " << endl;
    cout << "Enter (2) for Sun-Earth-Moon Orbits " << endl;
    cout << "Input a number: " << endl;
    cin >> cases;

    if (cases == 0)
    {
        cout << "Input a file: " << endl;
        cin >> s;
    }
    else if (cases == 1)
    {
        s = "input.dat";
    }
    else if (cases == 2)
    {
        s = "input3.dat";
    }
    else
    {
        cout << "Error: Not a valid number" << endl;
	return 1;
    }
    
    char x[s.length()];

    // Converts the string into char
    strcpy(x, s.c_str());
    
    SolarSystem solarS(x);

    // **** Default ********************
    // solarS.p[0] is always Sun
    // solarS.p[1] is always Earth
    // *********************************

    // **** Options for the User *******
    // solarS.p[2] is always Moon
    // solarS.p[3] is always Planet/Asteroid
    // *********************************
    
    // Variables
    float S_x = solarS.p[0].x;
    float S_y = solarS.p[0].y;
    float E_x[n], E_y[n];
    float M_x[n], M_y[n];
    float P_x[n], P_y[n];
    float Energy[n];
    float AngularM[n];
    float Time[n];
    
    // Prints the Energy and Angular Momentum
    cout << "Energy: " << energy(solarS, g) << endl;
    cout << "Angular Momentum: " << angularM(solarS) << endl;
    
    // Loops through the loop for n iterations
    for (int i = 0; i < n; i++)
    {
	
        // Stores the Energy and Angular Momentum in the array      
        Energy[i] = energy(solarS, g);
        AngularM[i] = angularM(solarS);
        Time[i] = i * h;

        // Earth Coordinates
        E_x[i] = solarS.p[1].x;
        E_y[i] = solarS.p[1].y;

        // Checks if there are 3 planets
        if (solarS.n >= 3)
        {
            // Moon Coordinates
            M_x[i] = solarS.p[2].x;
            M_y[i] = solarS.p[2].y;
        }

        // Checks if there are 4 planets    
        if (solarS.n >= 4)
        {
            // Planet Coordinates
            P_y[i] = solarS.p[3].y;
            P_x[i] = solarS.p[3].x;
        }

        // Updating velocity with half step and coordinates with full step
        updateVelocity(0.5 * h, solarS, g);
        updateCoord(h, solarS);
        updateVelocity(0.5 * h, solarS, g);
    }

    // Loops through the loop for n iterations
    for (int i = 0; i < n; i++)
    {
        // Checks when the y value of Earth went from negative to positive
        if (E_y[i] < 0 && E_y[i+1] > 0 )
        {
            orbits++;
        }
    }

    // Prints the orbits of Earth
    cout << "Earth orbits: " << orbits << endl;

    // ************* Plotting The Coordinates *************
    
    // Open a plot window
    if (!cpgopen("/XWINDOW")) return 1;

    // Set-up plot axes
    cpgenv(-2.,2.,-2.,2.,0,1);

    // Close up of Moon Plot Axes
    // cpgenv(0.5,1.,0.,1.,0,1);

    // ************* Energy Graph(n = 40) *************
    // cpgenv(0.,0.1,-0.0005,0.,0,1);
    // cpglab("Time", "Energy", " ");
    // cpgsci(2);
    // cpgline(n,Time, Energy);

    // ************* AngularM Graph(n = 40) *************
    // cpgenv(-0.02,0.02,-0.02,0.02,0,1);
    // cpglab("Time", "Angular Momentum", " ");
    // cpgsci(5);
    // cpgline(n,Time, AngularM);


    // Label axes
    cpglab("x", "y", "Solar System");

    // Plots the Earth (blue)
    cpgsci(4);
    cpgline(n,E_x,E_y);

    // Plots the Sun (yellow)
    cpgsci(7);
    // Plots a dot 
    cpgpt1(S_x,S_y,-22);

    if(solarS.n >= 3)
    {
	// Plots the Moon (white on black screen)
     	cpgsci(1);
    	cpgline(n,M_x,M_y);
    }

    if(solarS.n >= 4)
    {
	// Plots the Planet (green)
     	cpgsci(9);
    	cpgline(n,P_x,P_y);
    }

    // Pause and close plot window
    cpgclos();

}