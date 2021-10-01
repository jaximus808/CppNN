#include <cmath>
#include <random>
#include <time.h>
#include <chrono>
#include <math.h>  

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


        std::string choosableActivationFunctions[10] = {"binarystep","linear","sigmoid","tanh","relu","leakyrelu","paramrelu","exponlinunit","swish","softmax"};
         
        std::string activationSelection = ""; 
        int activationId = -1;
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
                        activationId = i;
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

        void ActivationFunctionAct(auto actCol)
        {
            // int nueronSize = sizeof(_nueronValue)/sizeof(*_nueronValue);
            // float* activatedData = new float();
            float maxV = 0.0f;
            float sum = 0.0f; 
            switch (activationId)
            {
                //"binarystep","linear","sigmoid","tanh","relu","leakyrelu","paramrelu","exponlinunit","swish","softmax"
                //do everything else later
                //binarystep
                case 0:
                    break;
                //linear
                case 1:
                    break;
                //sigmnoid    
                case 2:
                    break;
                //tanh
                case 3:
                    break;
                //relu
                case 4:
                    // for(int i = 0; i < nueronSize; i++)
                    // {
                    //     activatedData[i] = std::max(0.0f, _nueronValue[i]);
                    // }
                    // return *activatedData;
                    for(int i = 0; i < actCol.hiddenNodesSize; i++)
                    {
                        actCol.hiddenNodes[i].value = std::max(0.0f,actCol.hiddenNodes[i].value);
                    }
                    break;
                //leakyrelu
                case 5:
                    break;
                //paramrelu
                case 6:
                    break;
                //exponlinunit
                case 7:
                    break;
                //swish
                case 8:
                    break;
                //softmax
                case 9:
                    
                    for(int i = 0; i < actCol.hiddenNodesSize; i++) maxV = std::max(actCol.hiddenNodes[i].value, maxV);
                    std::cout<<maxV<<std::endl;
                    for(int i = 0; i < actCol.hiddenNodesSize; i++) sum += exp(actCol.hiddenNodes[i].value - maxV);
                    for(int i = 0; i < actCol.hiddenNodesSize; i++) actCol.hiddenNodes[i].value = exp(actCol.hiddenNodes[i].value- maxV) / sum;
                    break;
                default:
                    std::cout << "error";
                    break;
            }
        }
};