#include <iostream>
#include <string>
#include <vector>
#include <random>

class RandomFruitSelector
{
private:
	std::vector<std::string> fruitNames;
	std::vector<int> weightOptions;
	std::vector<int> selectedFruitCount;
	int numberOfRuns; 

	/*
	* Return the total weight based on the number of weights available
	*/
	int getTotalWeight()
	{
		int totalWeight = 0;

		for (const auto& weightOption : weightOptions)
		{
			totalWeight += weightOption;
		}

		return totalWeight;
	}

	/*
	* Generate a random number based on the total of weights 
	* @ https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
	*/
	int generateRandomNumber()
	{
		// produces different random numbers for each run (https://en.cppreference.com/w/cpp/numeric/random/random_device) 
		std::random_device randomDistribution; 

		// a random number engine based on Mersenne Twister algorithm (https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine) 
		std::mt19937 gen(randomDistribution());

		// produces a range of numbers between 0 and 99 (https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distri
		std::uniform_int_distribution<> distribution(0, getTotalWeight() - 1); 

		return distribution(gen);
	}

	/*
	* Get the fruit name based on the random number and how it compares to the cumulative weight 
	*/
	std::string getFruitName()
	{
		// https://python-course.eu/numerical-programming/weighted-probabilities.php
		int randomNumber = generateRandomNumber();
		int cumulativeWeight = 0;
		std::string selectedRandomFruit;

		for (int i = 0; i < fruitNames.size(); ++i)
		{
			cumulativeWeight += weightOptions[i]; // Add the weight to the cumulative weight  
			
			// Select a fruit and increment its occurence if the random number is smaller than the cumulative weight 
			if (randomNumber < cumulativeWeight)
			{
				selectedRandomFruit = fruitNames[i];
				selectedFruitCount[i]++; // increment the count of the fruit that has been selected
				return selectedRandomFruit;
			}
		}
	}

public:
	RandomFruitSelector(const std::vector<std::string>& fruitSymbols, const std::vector<int>& weights, int& runs)
		: fruitNames(fruitSymbols), weightOptions(weights), selectedFruitCount(fruitSymbols.size(), 0), numberOfRuns(runs)
	{
	}

	void printFruitSelected()
	{
		std::cout << "\n";
		std::cout << "********** \n";
		std::cout << "\n";

		for (int i = 0; i < numberOfRuns; ++i) {
			std::cout << "The chosen fruit corresponds to : " << getFruitName() << "\n"; 
		}
	}

	void printNumberOfOccurences() const {
		
		std::cout << "\n";
		std::cout << "********** \n";
		std::cout << "\n";

		for (int i = 0; i < fruitNames.size(); ++i) {
			std::cout << fruitNames[i] << " has been selected: " << selectedFruitCount[i] << " times \n";
		}
	}
};

int main()
{
	std::vector<std::string> fruit = { "Seven", "Bell", "Melon", "Plum", "Orange", "Lemon", "Cherry" };
	std::vector<int> probabilities = { 10, 15, 20, 25, 15, 10, 5 };
	int runs = 15;

	// Create a random fruit selector / generator object 
	RandomFruitSelector randomFruitSelector(fruit, probabilities, runs);

	// https://github.com/HedonisticOpportunist/Advisor-Bot/blob/main/AdvisorBotMessages.cpp
	std::cout << "       /////_/////// \n";
	std::cout << "      (^ .^) _) \n";
	std::cout << "      /  ( \n";
	std::cout << "      (| |) \n";
	std::cout << "    (__d b__) \n";
	std::cout << "RANDOM FRUIT GENERATOR \n"; 

	// print which fruit has been selected 
	randomFruitSelector.printFruitSelected(); 

	// print out how often a fruit symbol has been selected
	randomFruitSelector.printNumberOfOccurences();

	return 0;
}
