// neural-net-tutorial.cpp
// Source: https://www.youtube.com/watch?v=sK9AbJ4P8ao&t=25s&ab_channel=AbhishekPandey

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

struct Connection {
	double weight;
	double deltaWeight;
};


class Neuron;

typedef vector<Neuron> Layer;


// *************************** class Neuron ***************************
class Neuron{
	public:
		Neuron(unsigned numOutputs, unsigned myIndex);
		void setOutputVal(double val) { m_outputVal = val; }
		double getOutputVal(void) const { return m_outputVal; }
		void feedForward(const Layer &prevLayer);
		void calcOutputGradients(double targetVal);
		void calcHiddenGradients(const Layer &nextLayer);
		void updateInputWeights(Layer &prevLayer);

	private:
		static double eta; // overal net learning rate [0.0, 1.0] (slow learner, reckless learner).
		static double alpha; // multiplier of last weight change (momentum) [0.0, 1.0] (no momentum, high momentum).
		static double transferFunction(double x);
		static double transferFunctionDerivative(double x);
		static double randomWeight(void) { return rand() / double(RAND_MAX); }
		double sumDOW(const Layer &nextLayer) const;
		double m_outputVal;
		vector<Connection> m_outputWeights;
		unsigned n_myIndex;
		double m_gradient;
};

// Define class Neuron constructor.
Neuron::Neuron(unsigned numOutputs, unsigned myIndex) {
	for (unsigned c = 0; c < numOutputs; ++c) {
		m_outputWeights.push_back(Connection());
		m_outputWeights.back().weight = randomWeight();
	}

	n_myIndex = myIndex;
}

// Define class Neuron feedForward member function.
void Neuron::feedForward(const Layer &prevLayer) {
	double sum = 0.0;

	// Sum the previous layer's outputs (which are the inputs) include
	// the bias node from the previous layer.
	for (unsigned n = 0; n < prevLayer.size(); ++n) {
		sum += prevLayer[n].getOutputVal() * 
				prevLayer[n].m_outputWeights[n_myIndex].weight;
	}

	m_outputVal = Neuron::transferFunction(sum);
}

// Define class Neuron transferFunction (activation function) member
// function.
double Neuron::transferFunction(double x) {
	// tanh - output range [-1.0, 1.0].
	return tanh(x);
}

// Define class Neuron transferFunctionDerivative member function 
// (for backpropagation).
double Neuron::transferFunctionDerivative(double x) {
	// tanh derivative.
	return 1.0 - x * x;
}

// Define class Neuron calcOutputGradients member function.
void Neuron::calcOutputGradients(double targetVal) {
	double delta = targetVal - m_outputVal;
	m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
}

// Define class Neuron calcHiddenGradients member function.
void Neuron::calcHiddenGradients(const Layer &nextLayer) {
	double dow = sumDOW(nextLayer);
	m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal);
}

// Define class Neuron sumDOW member function.
double Neuron::sumDOW(const Layer &nextLayer) const {
	 double sum = 0.0;

	 // Sum contributions of the errors at the nodes we feed.
	 for (unsigned n = 0; n < nextLayer.size() - 1; ++n) {
	 	sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
	 }

	 return sum;
}

// Define class Neuron updateInputWeights member function.
void Neuron::updateInputWeights(Layer &prevLayer) {
	// The weights to be updated are in the Connection container in the
	// neurons in the preceding layer.
	for (unsigned n = 0; n < prevLayer.size(); ++n) {
		Neuron &neuron = prevLayer[n];
		double oldDeltaWeight = neuron.m_outputWeights[n_myIndex].deltaWeight;

		// New delta weight is going to be composed of individual
		// input, magnified by the gradient and train rate. Also add
		// momentum (= a fraction of the previous delta weight).
		double newDeltaWeight = 
				eta * neuron.getOutputVal() * m_gradient + alpha
				* oldDeltaWeight;

		neuron.m_outputWeights[n_myIndex].deltaWeight = newDeltaWeight;
		neuron.m_outputWeights[n_myIndex].weight += newDeltaWeight;
	}
}

// Define class Neuron eta member.
double Neuron::eta = 0.15;

// Define class Neuron alpha member.
double Neuron::alpha = 0.5;


// ***************************** class Net ****************************
class Net {
	public:
		Net(const vector<unsigned> &topology);
		void feedForward(const vector<double> &inputVals);
		void backProp(const vector<double> &targetVals);
		void getResults(vector<double> &resultVals) const;
		double getRecentAverageError(void) const { return m_recentAverageError; }

	private:
		vector<Layer> m_layers; // m_layers[layer_num][neuronNum]
		double m_error;
		double m_recentAverageError;
		static double m_recentAverageSmoothingFactor;
};

// Define class Net constructor.
Net::Net(const vector<unsigned> &topology) {
	unsigned numLayers = topology.size();
	for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {
		m_layers.push_back(Layer());
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

		// Another loop to add neurons to the layer.
		for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {
			m_layers.back().push_back(Neuron(numOutputs, neuronNum));
			cout << "Made a Neuron!" << endl;
		}

		// Force the bias node's output value to 1.0. it's the last
		// neuron create above.
		m_layers.back().back().setOutputVal(1.0);
	}
}

// Define class Net feedforward member function.
void Net::feedForward(const vector<double> &inputVals) {
	assert(inputVals.size() == m_layers[0].size() - 1);

	// Assign {latch} the input values into the input neurons.
	for (unsigned i = 0; i < inputVals.size(); ++i) {
		m_layers[0][i].setOutputVal(inputVals[i]);
	}

	// Forward propagation.
	for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum) {
		Layer &prevLayer = m_layers[layerNum - 1];
		for (unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n) {
			m_layers[layerNum][n].feedForward(prevLayer);
		}
	}
}

// Define class Net backProp member function.
void Net::backProp(const vector<double> &targetVals) {
	// Calculate the overal net error (RMS of output neuron errors).
	Layer &outputLayer = m_layers.back();
	m_error = 0.0;

	for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
		double delta = targetVals[n] - outputLayer[n].getOutputVal();
		m_error += delta * delta;
	}
	m_error /= outputLayer.size() - 1; // Get average error squared.
	m_error = sqrt(m_error); // RMS.

	// Implement a recent average measurement.
	m_recentAverageError = 
			(m_recentAverageError * m_recentAverageSmoothingFactor + m_error)
			/ (m_recentAverageSmoothingFactor + 1.0);

	// Calculate the output layer gradients.
	for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
		outputLayer[n].calcOutputGradients(targetVals[n]);
	}

	// Calculate the gradients on hidden layers.
	for (unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum) {
		Layer &hiddenLayer = m_layers[layerNum];
		Layer &nextLayer = m_layers[layerNum + 1];
	
		for (unsigned n = 0; n < hiddenLayer.size(); ++n) {
			hiddenLayer[n].calcHiddenGradients(nextLayer);
		}
	}

	// For all layers from outputs in first hidden layer, update
	// connection weights.
	for (unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum) {
		Layer &layer = m_layers[layerNum];
		Layer &prevLayer = m_layers[layerNum - 1];
	
		for (unsigned n = 0; n < layer.size() - 1; ++n) {
			layer[n].updateInputWeights(prevLayer);
		}
	}
}

// Define class Net getResults member function.
void Net::getResults(vector<double> &resultVals) const {
	resultVals.clear();
	for (unsigned n = 0; n < m_layers.back().size() - 1; ++n) {
		resultVals.push_back(m_layers.back()[n].getOutputVal());
	} 
}

// Define class Net m_recentAverageSmoothingFactor member.
double Net::m_recentAverageSmoothingFactor = 100.0;


// ************************ class TrainingData ************************
class TrainingData {
	public:
		TrainingData(const string filename);
		bool isEof(void) { return m_trainingDataFile.eof(); }
		void getTopology(vector<unsigned> &topology);

		// Returns the number of input values read from the file.
		unsigned getNextInputs(vector<double> &inputVals);
		unsigned getTargetOutputs(vector<double> &targetOutputVals);

	private:
		ifstream m_trainingDataFile;	
};

// Define class TrainingData constructor.
TrainingData::TrainingData(const string filename) {
	m_trainingDataFile.open(filename.c_str());
}

// Define class TrainingData getTopology member function.
void TrainingData::getTopology(vector<unsigned> &topology) {
	string line;
	string label;

	getline(m_trainingDataFile, line);
	stringstream ss(line);
	ss >> label;
	if (this->isEof() || label.compare("topology:") != 0) {
		abort();
	}

	while (!ss.eof()) {
		unsigned n;
		ss >> n;
		topology.push_back(n);
	}

	return;
}

// Define class TrainingData getNextInputs member function.
unsigned TrainingData::getNextInputs(vector<double> &inputVals) {
	inputVals.clear();

	string line;
	getline(m_trainingDataFile, line);
	stringstream ss(line);

	string label;
	ss >> label;
	if (label.compare("in:") == 0) {
		double oneValue;
		while (ss >> oneValue) {
			inputVals.push_back(oneValue);
		}
	}

	return inputVals.size();
}

// Define class TrainingData getNextInputs member function.
unsigned TrainingData::getTargetOutputs(vector<double> & targetOutputVals) {
	targetOutputVals.clear();

	string line;
	getline(m_trainingDataFile, line);
	stringstream ss(line);

	string label;
	ss >> label;
	if (label.compare("out:") == 0) {
		double oneValue;
		while (ss >> oneValue) {
			targetOutputVals.push_back(oneValue);
		}
	}

	return targetOutputVals.size();
}


void showVectorVals(string label, vector<double> &v) {
	cout << label << " ";
	for (unsigned i = 0; i < v.size(); ++i) {
		cout << v[i] << " ";
	}
	cout << endl;
}


int main() {
	TrainingData trainingData("./tmp/trainingData.txt");

	// e.g. {3, 2, 1}
	vector<unsigned> topology;
	trainingData.getTopology(topology);
	Net myNet(topology);

	vector<double> inputVals, targetVals, resultVals;
	int trainingPass = 0;

	while (!trainingData.isEof()) {
		++trainingPass;
		cout << endl << "Pass " << trainingPass;

		// Get new input data and feed it forward.
		if (trainingData.getNextInputs(inputVals) != topology[0]) {
			break;
		}
		showVectorVals(" :Inputs:", inputVals);
		myNet.feedForward(inputVals);

		// Collect the net's actual results.
		myNet.getResults(resultVals);
		showVectorVals("Outputs: ", resultVals);

		// Train the net what outputs should have been.
		trainingData.getTargetOutputs(targetVals);
		showVectorVals("Targets: ", targetVals);
		assert(targetVals.size() == topology.back());

		myNet.backProp(targetVals);

		// Reports how well the training is working, averaged over
		// recent samples.
		cout << "Net recent average error: "
				<< myNet.getRecentAverageError() << endl;
	}

	cout << endl << "Done";

	/*
	// e.g. {3, 2, 1}
	vector<unsigned> topology;
	topology.push_back(3);
	topology.push_back(2);
	topology.push_back(1);

	Net myNet(topology);

	vector<double> inputVals;
	myNet.feedforward(inputVals);

	myNet.backprop(targetVals);
	vector<double> targetVals;
	
	myNet.getResults(resultVals);
	vector<double> resultVals;
	*/

	return 0;
}