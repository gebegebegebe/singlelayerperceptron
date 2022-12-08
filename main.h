#include<stdio.h>
#include<math.h>
#define list_len 4

struct input_node { 
	float weight;
	float input_value;
};

struct output_node {
	float bias;
	int classification;
	input_node list_inputs[list_len];
};

int linear_classifier (struct output_node *output);
void error_correction(struct output_node *output);
void print_nodes(struct output_node *output);
float sigmoid_function (float summation);
float summation_accumulator (struct output_node *output);

float sigmoid_function (float summation) {
	return (1/(1 + pow(2.718,-summation)));
}

float summation_accumulator (struct output_node *output) {
	float summation_sum = 0;

	for(int i = 0 ; i < list_len ; i++) {
		summation_sum += output->list_inputs[i].weight * output->list_inputs[i].input_value;
	}
	summation_sum += output->bias;

	return summation_sum;
}

void error_correction (struct output_node *output) {
	
	// uses mean squared error

	float sigmoid_result = sigmoid_function(summation_accumulator(output));
	float alpha_constant = 0.2;

	for (int i = 0 ; i < list_len ; i++) {
		output->list_inputs[i].weight = output->list_inputs[i].weight - (alpha_constant * (2*(sigmoid_result - output->classification) * (1 - sigmoid_result) * sigmoid_result * output->list_inputs[i].weight));
	}
	output->bias = output->bias - (alpha_constant * (2*(sigmoid_result - output->classification) * (1 - sigmoid_result) * sigmoid_result));
}

int linear_classifier (struct output_node *output) {
	float summation_sum = 0;
	float sigmoid_result = 0;
	int classification_result = -1;

	summation_sum = summation_accumulator(output);
	printf("summation %f\n", summation_sum);
	sigmoid_result = sigmoid_function(summation_sum);
	printf("sigmoid %f\n", sigmoid_result);

	if (sigmoid_result >= 0.5) {
		classification_result = 1;	
	}

	return classification_result;
}

void print_nodes(struct output_node *output) {
	printf("\n");
	for (int i = 0 ; i < list_len ; i++) {
		printf("input node %d: %f\n", i, output->list_inputs[i].weight);
	}
	printf("\n");
}

