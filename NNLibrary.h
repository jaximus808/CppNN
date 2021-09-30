#include <cmath>
#include <random>
#include <time.h>
#include <chrono>

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

uint64_t getmili()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
 
}

class ActivationFunction
{
    public:

        //hiddenCollum* instanceCollum; 

        std::string choosableActivationFunctions[10] = {"binarystep","linear","sigmoid","tanh","relu","leakyrelu","paramrelu","exponlinunit","swish","softmax"};
         
        std::string activationSelection = ""; 
        int activationId = -1;
        // hiddenCollum actCol
        int SetActivationFunction(std::string _activationChoice,)
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
                        activationId = i;
                        activationSelection = _modifiedString;
                        break;
                    }
                }
                if(missing) throw(1);
                //instanceCollum = &actCol;
                return 1;
            }
            catch (int i)
            {
                std::cout<<"NN Error: Activation function doesn't exist";
                return -1;
            }
        }

        double ActivationFunctionAct(float* _nueronValue)
        {
            int nueronSize = sizeof(_nueronValue)/sizeof(*_nueronValue);
            float* activatedData = new float();
            
            switch (activationId)
            {
                //"binarystep","linear","sigmoid","tanh","relu","leakyrelu","paramrelu","exponlinunit","swish","softmax"
                //do everything else later
                //binarystep
                case 0:
                    return -1.0;
                    break;
                //linear
                case 1:
                    return -1.0;
                    break;
                //sigmnoid    
                case 2:
                    return -1.0;
                    break;
                //tanh
                case 3:
                    return -1.0;
                    break;
                //relu
                case 4:
                    for(int i = 0; i < nueronSize; i++)
                    {
                        activatedData[i] = std::max(0.0f, _nueronValue[i]);
                    }
                    return *activatedData;
                    break;
                //leakyrelu
                case 5:
                    return -1.0;
                    break;
                //paramrelu
                case 6:
                    return -1.0;
                    break;
                //exponlinunit
                case 7:
                    return -1.0;
                    break;
                //swish
                case 8:
                    return -1.0;
                    break;
                //softmax
                case 9:
                    return -1.0;
                    break;
                default:
                    std::cout << "error";
                    return -1.0;
                    break;
            }
        }
};