#include"main.h"

int main() {
	// set up

	output_node output = { .bias = 1, .classification = -1, .list_inputs = NULL};
	output.list_inputs[0] = (input_node){ .weight = 2.0, .input_value = -1};
	output.list_inputs[1] = (input_node){ .weight = 0, .input_value = 2};
	output.list_inputs[2] = (input_node){ .weight = 3.0, .input_value = 0};
	output.list_inputs[3] = (input_node){ .weight = -1.0, .input_value = -4};

	// performs calculation and classification
	
	int i = -1;
	int iterations = 30;
	while (++i < iterations) {
		printf("\nITERATION: %d\n", i);

		print_nodes(&output);

		if (linear_classifier(&output) == output.classification) {
			printf("classified!\n");
			return 1;
		}

		error_correction(&output);
	}

	printf("not classified yet!\n");
	return 0;
}
