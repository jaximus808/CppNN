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
        int is64;
        nueron *networkInput;
        hiddenCollum *networkHiddenCollumns;
        nueron *networkOutput;

        int *NetworkStructure;

        ActivationFunction *activationFunctions;

        int inputSize;
        int hiddenLayerSize;
        int outputSize; 

        //also make a method of storing the value of the weights in the NN object in a text file.

        //expirmental function, if the data needs to be converted maybe use this idk lul. 
        void GiveInput()
        {

        }

        /// _inputs: gives the nueral network the inputs to the network so it can begin. If the inputs don't match the network size it will crash
        /// for now expect the user to give the appropiate length 
        void RunNetwork(float _inputs[])
        {
            //set the inputs of the input neurons
            for(int i = 0; i < sizeof(networkInput)/sizeof(*networkInput); i++)
            {
                //might not need this but leave for now
                networkInput[i].value = _inputs[i];
                
                //maybe have the calculations for the next layer here
                for(int y = 0; y < networkHiddenCollumns[0].hiddenNodesSize; y++)
                {
                    networkHiddenCollumns[0].hiddenNodes[y].value += networkInput[i].value;
                }
            }
            
            // apply sigmoid and bias calc, maybe optimize this better
            //for

            //where the calculations actually begins
            for(int i=0; i < hiddenLayerSize;i++)
            {
                for(int y=0; y < networkHiddenCollumns[0].hiddenNodesSize;y++)
                {
                }
            }
        }

        /// will update more later
        /// _inputCount: The quantity of input nuerons
        /// _hiddenLayerNodes: An integer array of the quantity of nodes in each hidden layer
        /// _outputNodeSize: The quanityt of output nuerons
        /// _activations: An Array of strings that consist of the name of each activation functions in each
        void SetNueralNetwork(int _inputCount,int _hiddenLayerNodes[], int _outputNodesSize, std::string _activations[])
        {   
            hiddenLayerSize = sizeof(_hiddenLayerNodes)/sizeof(*_hiddenLayerNodes);
            inputSize = _inputCount;
            outputSize = _outputNodesSize;
            //instantiate arrays of data
            NetworkStructure = new int(hiddenLayerSize+2);            
            networkInput = new nueron[_inputCount];
            networkHiddenCollumns = new hiddenCollum[hiddenLayerSize];
            networkOutput = new nueron[_outputNodesSize];
            activationFunctions = new ActivationFunction[hiddenLayerSize+1];


            //set input nueron values 
            for(int i=0;i< _inputCount;i++)
            {
                networkInput[i].setNueron(0.0, 0.0, 0);   
            }

            //define network structure and hiddenlayercollumns 
            NetworkStructure[0] = _inputCount;
            NetworkStructure[1] = _hiddenLayerNodes[0];

            networkHiddenCollumns[0].setHiddenCollum( _hiddenLayerNodes[0], _inputCount ); 
            
            for(int i = 1; i < hiddenLayerSize; i++)
            {
                NetworkStructure[i+1] = _hiddenLayerNodes[i];
                srand (time(NULL)+i);
                networkHiddenCollumns[i].setHiddenCollum(_hiddenLayerNodes[i], _hiddenLayerNodes[i-1]); 
            }
            NetworkStructure[hiddenLayerSize+1] = _outputNodesSize;
            
            for(int i = 0; i < hiddenLayerSize+1; i++)
            {
                int ret = activationFunctions[i].SetActivationFunction(_activations[i]);
                
                if(ret == -1)
                {
                    std::cout<<"error";
                    return;
                } 
            }
            for(int i = 0; i < outputSize; i++)
            {
                networkOutput[i].setNueron(0.0, 0.0, 0);
            }
            std::cout<<"Layer " <<0;
            std::cout<<": { ";
            std::cout<<networkInput[0].value;
            for(int i = 1; i < inputSize; i++)
            {
                std::cout<<", ";
                std::cout<<networkInput[i].value;
            }
            std::cout<<" }\n";
            for(int i = 0; i < hiddenLayerSize; i++)
            {
                std::cout<<"Layer "<<i+1;
                std::cout<<": { ";
                std::cout<<networkHiddenCollumns[i].hiddenNodes[0].value;
                for(int y = 1;y < networkHiddenCollumns[i].hiddenNodesSize; y++)
                {
                    std::cout<<", ";
                    std::cout<<networkHiddenCollumns[i].hiddenNodes[y].value;
                    
                }
                std::cout<<" }";    
                std::cout<<" Activation Function: "<< activationFunctions[i].activationSelection;
                std::cout << "\n";
            }
            std::cout<<"Layer "<<hiddenLayerSize+1;
            std::cout<<": { ";
            std::cout<<networkOutput[0].value;
            for(int i = 1; i < outputSize; i++)
            {
                std::cout<<", ";
                std::cout<<networkOutput[i].value;
                
            }
            std::cout<<" }";    
            std::cout<<" Activation Function: "<< activationFunctions[hiddenLayerSize].activationSelection;
            std::cout << "\n";
        }
};


int main()
{

    // std::cout<<"Define the input layers"<<std::endl;
    // int buffInput = 0;
    // std::cin >> buffInput;
    NueralNetwork NP;
    NP.SetNueralNetwork(4, new int[2]{128,7},10,new std::string[3]{"relu","relu","softmax"});
    return 0;
}