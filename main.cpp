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
                //aren't node set to zero in a NN???
                hiddenNodes[i].setNueron(0.0, 0.0, _prevLayerCount);
            }
        }
};

class NueralNetwork
{
    public: 
        int is64;
        nueron *networkInput;
        hiddenCollum *networkHiddenCollumns;
        hiddenCollum *networkLayers; 
        nueron *networkOutput;

        int *NetworkStructure;

        ActivationFunction *activationFunctions;

        int inputSize;
        int hiddenLayerSize;
        int outputSize; 

        //also make a method of storing the value of the weights in the NN object in a text file.

        //expirmental function, if the data needs to be converted maybe use this idk lul. 
        void Reset()
        {
            for(int hiddenNodesCollumNum = 0; hiddenNodesCollumNum < hiddenLayerSize; hiddenNodesCollumNum++)
            {
                for(int i = 0; i < networkHiddenCollumns[hiddenNodesCollumNum].hiddenNodesSize; i++)
                {
                    networkHiddenCollumns[hiddenNodesCollumNum].hiddenNodes[i].value = 0; 
                }
            }
            for(int i = 0; i < outputSize; i++) networkOutput[i].value = 0; 
        }

        /// _inputs: gives the nueral network the inputs to the network so it can begin. If the inputs don't match the network size it will crash
        /// for now expect the user to give the appropiate length 
        void RunNetwork(float _inputs[], size_t size)
        {
           
            uint64_t startMili = getmili();
            if(size != inputSize)
            {
                std::cout<< "You lack enough inputs! (given: " <<size<< ")";
                return;
            }
            std::cout<< "running nueral network with given data\n";
            
            for(int i = 0; i < size; i++)
            {
                networkLayers[0].hiddenNodes[i].value = _inputs[i];
            }

            for(int hiddenLayerCollumNum=1; hiddenLayerCollumNum < hiddenLayerSize+2; hiddenLayerCollumNum++)
            {
                for(int hiddenNodeNum=0; hiddenNodeNum < networkLayers[hiddenLayerCollumNum].hiddenNodesSize;hiddenNodeNum++)
                {
                    for(int prevNum = 0; prevNum < networkLayers[hiddenLayerCollumNum - 1].hiddenNodesSize; prevNum++)
                    {
                        networkLayers[hiddenLayerCollumNum].hiddenNodes[hiddenNodeNum].value += networkLayers[hiddenLayerCollumNum-1].hiddenNodes[prevNum].value * networkLayers[hiddenLayerCollumNum].hiddenNodes[hiddenNodeNum].weights[prevNum];
                        
                    } 
                    //make a logic check for softmax since it requires all the valuables. Say for example if softmax function then do a certain function that can handle these values. I take break now future jaxon lol 2:33 pm 9/28
                    networkLayers[hiddenLayerCollumNum].hiddenNodes[hiddenNodeNum].value += networkLayers[hiddenLayerCollumNum].hiddenNodes[hiddenNodeNum].bias;
                    networkLayers[hiddenLayerCollumNum].hiddenNodes[hiddenNodeNum].value = activationFunctions[hiddenLayerCollumNum-1].ActivationFunctionAct(&networkLayers[hiddenLayerCollumNum-1].hiddenNodes[hiddenNodeNum].value);
                }
            }
            printNetwork(false);

            // for(int hiddenNodeNum = 0; hiddenNodeNum < networkHiddenCollumns[0].hiddenNodesSize; hiddenNodeNum++)//y
            // {
            //     for(int inputNum = 0; inputNum < inputSize; inputNum++)
            //     {
            //         //adds all the inputs nodes multipled by its correlated weights and adds them
            //         networkHiddenCollumns[0].hiddenNodes[hiddenNodeNum].value += _inputs[inputNum]*networkHiddenCollumns[0].hiddenNodes[hiddenNodeNum].weights[inputNum];
            //     }
            //     networkHiddenCollumns[0].hiddenNodes[hiddenNodeNum].value += networkHiddenCollumns[0].hiddenNodes[hiddenNodeNum].bias;
            //     networkHiddenCollumns[0].hiddenNodes[hiddenNodeNum].value = activationFunctions[0].ActivationFunctionAct(&networkHiddenCollumns[0].hiddenNodes[hiddenNodeNum].value);
            // }

            // //apply sigmoid aftert

            // //layers after first hidden layers. 
            // std::cout<< "checkpoint 1\n";
            // for(int hiddenLayerCollumNum=1; hiddenLayerCollumNum < hiddenLayerSize; hiddenLayerCollumNum++)
            // {
            //     for(int hiddenNodeNum=0; hiddenNodeNum < networkHiddenCollumns[hiddenLayerCollumNum].hiddenNodesSize;hiddenNodeNum++)
            //     {
            //         for(int prevNum = 0; prevNum < networkHiddenCollumns[hiddenLayerCollumNum - 1].hiddenNodesSize; prevNum++)
            //         {
            //             networkHiddenCollumns[hiddenLayerCollumNum].hiddenNodes[hiddenNodeNum].value += networkHiddenCollumns[hiddenLayerCollumNum-1].hiddenNodes[prevNum].value * networkHiddenCollumns[hiddenLayerCollumNum].hiddenNodes[hiddenNodeNum].weights[prevNum];
                        
            //         } 
            //         networkHiddenCollumns[hiddenLayerCollumNum].hiddenNodes[hiddenNodeNum].value += networkHiddenCollumns[hiddenLayerCollumNum].hiddenNodes[hiddenNodeNum].bias;
            //         networkHiddenCollumns[hiddenLayerCollumNum].hiddenNodes[hiddenNodeNum].value = activationFunctions[hiddenLayerCollumNum].ActivationFunctionAct(&networkHiddenCollumns[hiddenLayerCollumNum].hiddenNodes[hiddenNodeNum].value);
            //     }
            // }
            
            std::cout<< "checkpoint 2\n";
            std::cout << "Network finished in " << getmili()-startMili << " ms"<<std::endl;
            printNetwork(false);
        }
        /// will update more later
        /// _inputCount: The quantity of input nuerons
        /// _hiddenLayerNodes: An integer array of the quantity of nodes in each hidden layer
        /// _outputNodeSize: The quanityt of output nuerons
        /// _activations: An Array of strings that consist of the name of each activation functions in each
        void SetNueralNetwork(int _inputCount,int _hiddenLayerSize,int _hiddenLayerNodes[], int _outputNodesSize, std::string _activations[])
        {   
            hiddenLayerSize = _hiddenLayerSize;
            inputSize = _inputCount;
            outputSize = _outputNodesSize;
            //instantiate arrays of data
            NetworkStructure = new int(hiddenLayerSize+2);  
            networkLayers = new hiddenCollum[hiddenLayerSize+2];          
            networkInput = new nueron[_inputCount];
            networkHiddenCollumns = new hiddenCollum[hiddenLayerSize];
            networkOutput = new nueron[_outputNodesSize];
            activationFunctions = new ActivationFunction[hiddenLayerSize+1];
            //consider refactoring to where have entireNetwork array with all hiddenCollumns for inputs and outputs to make looping easier, 

            //set input nueron values 
            for(int i=0;i< _inputCount;i++)
            {
                networkInput[i].setNueron(0.0, 0.0, 0);   
            }

            //define network structure and hiddenlayercollumns 
            NetworkStructure[0] = _inputCount;
            NetworkStructure[1] = _hiddenLayerNodes[0];

            networkLayers[0].setHiddenCollum(_inputCount, 0);
            
            networkHiddenCollumns[0].setHiddenCollum( _hiddenLayerNodes[0], _inputCount ); 
            
            for(int i = 1; i < hiddenLayerSize+2; i++)
            {
                networkLayers[i].setHiddenCollum(_hiddenLayerNodes[i-1], networkLayers[i-1].hiddenNodesSize);
                std::cout << networkLayers[i].hiddenNodesSize<< "\n";
                //networkHiddenCollumns[i].setHiddenCollum(_hiddenLayerNodes[i], _hiddenLayerNodes[i-1]); 
            }
            
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
                networkOutput[i].setNueron(0.0, 0.0, networkHiddenCollumns[hiddenLayerSize-1].hiddenNodesSize);
            }
            printNetwork(true);
        }

        void printNetwork(bool printweights)
        {
            for(int i = 0; i < hiddenLayerSize+2; i++)
            {
                std::cout<<"Layer "<< i<<": { ";
                for(int y = 0; y < networkLayers[i].hiddenNodesSize; y++)
                {
                    std::cout<<"value: "<< networkLayers[i].hiddenNodes[y].value;
                    if(printweights)
                    {
                        std::cout<<" weights: { ";
                        for(int z = 0; z < networkLayers[i].hiddenNodes[y].weightSize; z++)
                        {
                            std::cout<< " " << networkLayers[i].hiddenNodes[y].weights[z] << ",";
                        }
                        
                        std::cout<<"}, ";
                    }
                    else std::cout<< ", ";
                    
                }
                std::cout << "}";
                if(i > 0) std::cout << "Activation Function: " << activationFunctions[i-1].activationSelection;
                std::cout << "\n";
            }
        }
};


int main()
{

    // std::cout<<"Define the input layers"<<std::endl;
    // int buffInput = 0;
    // std::cin >> buffInput;
    NueralNetwork NP;
    NP.SetNueralNetwork(4,2, new int[3]{128,7,10},10,new std::string[3]{"relu","relu","softmax"});
    NP.RunNetwork(new float[4]{0.32f,0.12f,0.21f,0.23f}, 4);
    return 0;
}