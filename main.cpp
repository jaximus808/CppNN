#include <iostream>   
#include <cmath>       
#include <time.h>
#include <random>
#include "./NNLibrary.h"




struct nueron
{
    public:
        float value;
        float bias;
        float *weights;

        int weightSize = 0;
        /// _setValue: the starting random value of the nueron
        /// _biasSet: the bias of the collumn, could be removed possibly
        ///  _prevLayerCount: the amount of nodes behind it, used for weights
        void setNueron(float _setValue,float _biasSet, int _prevLayerCount)
        {
            bias = _biasSet;
            weights = new float[_prevLayerCount];
            value = _setValue;
            weightSize = _prevLayerCount;
            for(int i = 0; i < weightSize; i++)
            {
                weights[i] = random(-6.0,6.0);
            }
            //create an algorithm to randomly add weights
        }
        
};

struct hiddenCollum
{
    public:

        nueron *hiddenNodes; 

        int hiddenNodesSize = 0;
        /// _hiddenNodeSize: The amount of hidden nodes in this collum, 
        /// _prevLayerCount: the amount of previous nodes to create weights
        void setHiddenCollum(int _hiddenNodeSize, int _prevLayerCount )
        {
            hiddenNodes = new nueron[_hiddenNodeSize];
            hiddenNodesSize = _hiddenNodeSize;
            for(int i = 0; i < hiddenNodesSize; i++)
            {
                hiddenNodes[i].setNueron(random(-6.0,6.0), 0.0, _prevLayerCount);
            }
        }
};

class NueralNetwork
{
    public: 
        nueron *networkInput;
        hiddenCollum *networkHiddenCollumns;
        nueron *networkOutput;

        int *NetworkStructure;

        int inputSize;
        int hiddenLayerSize;
        int outputSize; 

        /// _inputCount is the quantity of Input Nodes
        /// _hiddenLayerNodes[] is a structure of the hidden layers
        /// _hiddenLayerCollum is the quanitity of hidden layers 
        NueralNetwork(int _inputCount,int _hiddenLayerNodes[], int _hiddenLayerCollumn, int _outputNodesSize)
        {
            //instantiate arrays of structs and ints
            NetworkStructure = new int(_hiddenLayerCollumn+2);            
            networkInput = new nueron[_inputCount];
            networkHiddenCollumns = new hiddenCollum[_hiddenLayerCollumn];
            networkOutput = new nueron[_outputNodesSize];

            //define sizes
            hiddenLayerSize = _hiddenLayerCollumn;
            inputSize = _inputCount;
            outputSize = _outputNodesSize;

            //set input nueron values 
            for(int i=0;i< _inputCount;i++)
            {
                networkInput[i].setNueron(0.0, 0.0, 0);   
            }

            //define network structure and hiddenlayercollumns 
            NetworkStructure[0] = _inputCount;
            NetworkStructure[1] = _hiddenLayerNodes[0];

            networkHiddenCollumns[0].setHiddenCollum( _hiddenLayerNodes[0], _inputCount ); 
            
            for(int i = 1; i < _hiddenLayerCollumn; i++)
            {
                NetworkStructure[i+1] = _hiddenLayerNodes[i];
                srand (time(NULL)+i);
                networkHiddenCollumns[i].setHiddenCollum(_hiddenLayerNodes[i], _hiddenLayerNodes[i-1]); 
            }
            NetworkStructure[_hiddenLayerCollumn+1] = _outputNodesSize;



            
            for(int i = 0; i < outputSize; i++)
            {
                networkOutput[i].setNueron(0.0, 0.0, 0);
            }
            std::cout<<0;
            std::cout<<": ";
            std::cout<<networkInput[0].value;
            for(int i = 1; i < inputSize; i++)
            {
                std::cout<<", ";
                std::cout<<networkInput[i].value;
            }
            std::cout<<std::endl;
            for(int i = 0; i < hiddenLayerSize; i++)
            {
                std::cout<<i+1;
                std::cout<<": ";
                std::cout<<networkHiddenCollumns[i].hiddenNodes[0].value;
                for(int y = 1;y < networkHiddenCollumns[i].hiddenNodesSize; y++)
                {
                    std::cout<<", ";
                    std::cout<<networkHiddenCollumns[i].hiddenNodes[y].value;
                    
                }
                std::cout<<std::endl;    
            }
            std::cout<<hiddenLayerSize+1;
            std::cout<<": ";
            std::cout<<networkOutput[0].value;
            for(int i = 1; i < outputSize; i++)
            {
                std::cout<<", ";
                std::cout<<networkOutput[i].value;
            } 
        }
};


int main()
{
    // std::cout<<"Define the input layers"<<std::endl;
    // int buffInput = 0;
    // std::cin >> buffInput;
    NueralNetwork NP(4, new int[5]{4,1,2,3},4,2);
    return 0;
}

