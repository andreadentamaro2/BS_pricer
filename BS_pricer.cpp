#include <iostream>
#include <cmath>
#include <fstream> 

using namespace std;

// COMP0041 ASSIGNMENT: Create an option pricer using the Black-Scholes pricing formula

// Cumulative Distribution Function (CDF)
double CDF(const double& x) {
    const double pi = 4.0 * atan(1.0), a1 = 0.319381530, a2 = -0.356563782, a3 = 1.781477937, a4 = -1.821255978, a5 = 1.330274429;    // Define all constants
    double k = 1/(1+0.2316419 * x);
    double n = (1/sqrt(2 * pi)) * exp(-0.5 * x * x); 
    double N = 1 - n * (a1 * k + a2 * k * k + a3 * pow(k,3) + a4 * pow(k,4) + a5 * pow(k,5));

    if (x >= 0.0) {
        return N;
    } else {
        return 1.0 - CDF(-x);
    }
}

// Calculate the price for the European vanilla call option
double european_call(const double& d1, const double& d2, const double& S, const double& E, const double& r, const double& sigma, const double& t, const double& T, const double& D) {
    return S * exp(-D * (T-t)) * CDF(d1) - E * exp(-r * (T-t)) * CDF(d2);
}

// Calculate the price for the European vanilla put option 
double european_put(const double& d1, const double& d2, const double& S, const double& E, const double& r, const double& sigma, const double& t, const double& T, const double& D) {
    return  -S * exp(-D * (T-t)) * CDF(-d1) + E * exp(-r * (T-t)) * CDF(-d2);
}

// Calculate the price for the binary call option 
double binary_call(const double& d1, const double& d2, const double& S, const double& E, const double& r, const double& sigma, const double& t, const double& T, const double& D){
    return exp(-r * (T-t)) * CDF(d2);
}

// Calculate the price for the binary put option 
double binary_put(const double& d1, const double& d2, const double& S, const double& E, const double& r, const double& sigma, const double& t, const double& T, const double& D){
    return exp(-r * (T-t)) * CDF(-d2);
}


int main()
{

ofstream out; 
// Output the results on an Excel file called "result.xls"
out.open("result.xls"); 

// Name the columns on the Excel file
out << "Stock Price" << '\t' << "Option Price" << endl; 

char type;
float S, E, r, sigma, t, T, D;
// Select what type of option is to be price 
cout << "\n 1. European Call Option \n 2. European Put Option \n 3. Binary Call Option \n 4. Binary Put Option \n Type the number of the option you want to price: " << endl;
cin >> type;
// Input the parameters to price the option 
cout << "Select the parameters: \n Spot Price:" << endl;
cin >> S; 
cout << "\n Strike Price: " << endl;
cin >> E;
cout << "\n Risk-free interest rate: " << endl;
cin >> r;
cout << "\n Volatility: " << endl;
cin >> sigma;
cout << "\n Time: " << endl;
cin >> t;
cout << "\n Maturity: " << endl;
cin >> T;
cout << "\n Continuous constant dividend yield: " << endl;
cin >> D;


double Vanilla_Call_Option, Vanilla_Put_Option, Binary_Call_Option, Binary_Put_Option, d1, d2;


switch (type)
{
    case '1':
    for(int S = 0; S <= 200; S +=5) {
        // Calculate d1 and d2
        d1 = (log(S / E) + (r - D + 0.5 * sigma * sigma) * (T-t)) / (sigma * pow((T-t),0.5));
        d2 = d1 - sigma * pow((T-t),0.5);

        Vanilla_Call_Option = european_call(d1, d2, S, E, r, sigma, t, T, D);   // Price the European Call Option 
        out << S << '\t' << Vanilla_Call_Option << endl;    // Store the results in the Excel file 
        
        // Set the value of the european call option equal to zero when the price is negative 
        if (Vanilla_Call_Option < 0){
            
            Vanilla_Call_Option = 0;
        }
    }
    break; 

    case '2':
    for(S = 0; S <= 200; S +=5) {
        // Calculate d1 and d2
        d1 = (log(S / E) + (r - D + 0.5 * sigma * sigma) * (T-t)) / (sigma * pow((T-t),0.5));
        d2 = d1 - sigma * pow((T-t),0.5);

        Vanilla_Put_Option = european_put(d1, d2, S, E, r, sigma, t, T, D);     // Price the European Put Option 
        out << S << '\t' << Vanilla_Put_Option << endl;     // Store the results in the Excel file 

        // Set the value of the european put option equal to zero when the price is negative
        if (Vanilla_Put_Option < 0){
            
            Vanilla_Put_Option = 0;
        }
    }
    break; 

    case '3':
    for(S = 0; S <= 200; S +=5) {
        // Calculate d1 and d2
        d1 = (log(S / E) + (r - D + 0.5 * sigma * sigma) * (T-t)) / (sigma * pow((T-t),0.5));
        d2 = d1 - sigma * pow((T-t),0.5);

        Binary_Call_Option = binary_call(d1, d2, S, E, r, sigma, t, T, D);      // Price the Binary Call Option 
        out << S << '\t' << Binary_Call_Option << endl;     // Store the results in the Excel file 

        // Set the value of the binary call option equal to zero when the price is negative
        if (Binary_Call_Option < 0){
            
            Binary_Call_Option = 0;
        }
    }
    break; 

    default:
    for(S = 0; S <= 200; S +=5) {
        // Calculate d1 and d2
        d1 = (log(S / E) + (r - D + 0.5 * sigma * sigma) * (T-t)) / (sigma * pow((T-t),0.5));
        d2 = d1 - sigma * pow((T-t),0.5);

        Binary_Put_Option = binary_put(d1, d2, S, E, r, sigma, t, T, D);        // Price the Binary Put Option 
        out << S << '\t' << Binary_Put_Option << endl;      // Store the results in the Excel file 

        //Set the value of the binary put option equal to zero when the price is negative
        if (Binary_Put_Option < 0){
            
            Binary_Put_Option = 0;
        }   
    }   
}

// Close the Excel file 
out.close();

return 0;

}

