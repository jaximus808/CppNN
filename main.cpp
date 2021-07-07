#include <iostream>   
#include <cmath>       
#include <time.h>
#include <random>

// float GetRandom(float min, float max)
// {
//     std::random_device r;
//     std::default_random_engine e1(r());
//     std::uniform_int_distribution<int> uniform_dist(min, max);
//     return uniform_dist(e1);
// }

// float GetRandom(float max)
// {
//     return uniform_dist(e1);
// }

float sinRandom(float _in)
{
    return sin(_in *1000000 + time(NULL));
}

struct nueron
{
    public:
        float value;
        float *bias;
        float *weights;
        void setNueron(float _setValue,int _biasSize, int _prevLayerCount)
        {
            bias = new float[_biasSize];
            weights = new float[_prevLayerCount];
            value = _setValue;
        }
        
};

class NueralNetwork
{
    public: 
        nueron *networkInput;
        nueron *networkHidden;
        nueron *networkOutput;

        int inputSize;
        int hiddenLayerSize;
        int outputSize; 
        NueralNetwork(int _inputCount,int _hiddenLayerCount)
        {
            networkInput = new nueron[_inputCount];
            inputSize = _inputCount;
            for(int i=0;i< _inputCount;i++)
            {
                srand (time(NULL)+i);
                networkInput[i].setNueron(sinRandom(float(i+1)), _hiddenLayerCount,0);
                std::cout<< networkInput[i].value<<std::endl;
            }
            //for(int i = 0 )
        }
    
};


int main()
{
    NueralNetwork NP(4,10);
    return 0;
}

