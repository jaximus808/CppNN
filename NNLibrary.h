#include <cmath>
#include <random>
#include <time.h>

float random(float _min, float _max)
{
    float _rand = sin(2000000.0 + time(NULL) * rand());
    return (std::abs(_rand - floor(_rand))*(_max-_min))+(_min);
//     return ((abs(sin(1000000.0 + time(NULL) * rand())))+_min)*(_max);
}

/// Offers better random than rand() lul. First Parameter is min and second is max. If only one parameter inputted then parameter is max
float random(float _max)
{
    float _rand = sin(2000000.0 + time(NULL) * rand());
    return (std::abs(_rand - floor(_rand)))*_max;
}

class ActivationFunction
{
    public:

        std::string choosableActivationFunctions[10] = {"binarystep","linear","sigmoid","tanh","relu","leakyrelu","paramrelu","exponlinunit","swish","softmax"};
         
        std::string activationSelection;
        int SetActivationFunction(std::string _activationChoice)
        {
            std::string _modifiedString = "";
            
            
            for(auto c:_activationChoice) if(c!=' ') _modifiedString += tolower(c);
            try
            {
                bool missing = true; 
                for(int i = 0;i < sizeof(choosableActivationFunctions)/sizeof(choosableActivationFunctions[0]); i++)
                {
                    if(choosableActivationFunctions[i] == _modifiedString)
                    {
                        missing = false; 
                        activationSelection = _modifiedString;
                        break;
                    }
                }
                if(missing) throw(1);
                return 1;
            }
            catch (int i)
            {
                std::cout<<"NN Error: Activation function doesn't exist";
                return -1;
            }
            
        }
};