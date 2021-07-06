#include <iostream>   
#include <stdlib.h>     
#include <time.h>       


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
                networkInput[i].setNueron(rand()%10-5, _hiddenLayerCount,2);
                std::cout<< networkInput[i].value<<std::endl;
            }
        }
    
};


int main()
{
    NueralNetwork NP(4,10);
    return 0;
}