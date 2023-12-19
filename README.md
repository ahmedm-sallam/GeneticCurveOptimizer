# GeneticCurveOptimizer

## Problem Statement

Curve fitting involves constructing a mathematical function (polynomial equation) that best fits a series of data points. In this problem, the goal is to use a genetic algorithm to find the best coefficients for a polynomial equation, minimizing the distance between the polynomial function and given data points.

## Input

The input is provided in a file with the following format:

- First line: Number of datasets (at least 1)
- For each dataset:
  - Number of data points and polynomial degree separated by space
  - For each point: x-coordinate and y-coordinate separated by space

Example:
```plaintext
1
4 2
1 5
2 8
3 13
4 20
```

## Implementation

The C++ code provided uses a floating-point representation for the genetic algorithm. Key components of the algorithm include:

- Population initialization
- Fitness calculation based on mean squared error
- Tournament selection
- Crossover and mutation
- Elitist replacement

## Usage

1. Compile the C++ code.
2. Ensure the input file (`input.txt`) is properly formatted.
3. Run the compiled executable.
4. View the output in the console.

## Parameters

- `POPULATION_SIZE`: Size of the population
- `MUTATION_THRESHOLD`: Probability threshold for mutation
- `CROSSOVER_THRESHOLD`: Probability threshold for crossover
- `BESTN`: Percentage of the best individuals to be retained
- `MAX_GENERATION`: Maximum number of generations
- `MAX_CHILDREN`: Percentage of the population to be generated as children
