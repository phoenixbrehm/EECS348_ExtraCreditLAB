#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

double extract(const string &str);
double power10(int power);
double strtoInt(char num);

int main(){
    string userNumber;

    while(true){
        cout << "Enter a number or \"END\" to quit: ";
        cin >> userNumber;
        if(userNumber == "END"){
            cout << "Quitting...";
            break;
        }

        double returnedNumber = extract(userNumber);

        if(returnedNumber != -999999.99){
            cout << fixed << setprecision(4) << returnedNumber <<"\n";
        }else{
            cout << "Invalid input, try again.\n";
        }
    }
    return 1; //if we make it here we will get a valid program end
}

double extract(const string &str){
    //checking for signs
    bool hasFront = false;
    bool isNegative = false;
    if(str[0] == '+' || str[0] == '-'){
        hasFront = true;
        if(str[0] == '-'){
            isNegative = true;
        }
    }
    //can extract digit, cast it to a double, then multiply said number by 10^n. Where n is the digit  +100.47, decimal at 4, len=7, len-decimalIndex=nubers after decimal ifhasFront decimalindex-1 = numbers before the decimal, if not hasFront decimalIndex = numbers before the decimal. number**(denumberindex)
    
    //this will find the index of the decimal if present
    int decimalindex = str.length();
    for(int i=0;i<str.length();i++){
        if(str[i] == '.'){
            decimalindex = i;
        }
    }

    double result = 0;
    //this will create the front end of the number (those to the left of the decimal)
    if(hasFront){
        for(int i =decimalindex-1; i>0; i--){ //iteration goes from 1 left of the decimal and decrements until we have seen every non-sign number

            double valid = strtoInt(str[i]); //if we come across the default case, send out an invalid input
            if(valid ==-999999.99){
                return -999999.99;
            }

            //result is a cumulative sum of 
            result = result + strtoInt(str[i])*power10((decimalindex-i-1)); //this adds the number times the respective power
        }
    }else{
        for(int i=decimalindex-1;i>-1;i--){ //this will include the first digit, unlike the last loop which ignores the very first.
            double valid = strtoInt(str[i]);
            if(valid ==-999999.99){
                return -999999.99;
            }


            result = result + strtoInt(str[i])*power10((decimalindex-i-1));
        }
    }

    for(int i=decimalindex+1;i<str.length();i++){ //do not care about a sign case as we are always right of the decimal and signage has no affect on us
        double valid = strtoInt(str[i]);
        if(valid ==-999999.99){
            return -999999.99;
        }
        result = result + strtoInt(str[i])*power10(-1*(i-decimalindex)); //negative power
    }



    if(isNegative){
        result = result *-1;
    }
    return result;
}

double strtoInt(char num){
    switch (num)
    {
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    case '0':
        return 0;
    default:
        return -999999.99;
    }
}

double power10(int power){
    double manip = 1;
    if(power == 0){
        return manip;
    }else if(power > 0){
        for(int i=0; i<power;i++){
            manip = manip * 10;
        }
        return manip;
    }else if(power < 0){
        for(int i=0; i<(-1*power);i++){ //-1*power because power is always less than i otherwise
            manip = manip/10;
        }
        return manip;
    }
}