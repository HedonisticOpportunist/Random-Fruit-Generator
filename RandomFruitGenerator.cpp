#include <iostream>
#include <string>
#include <vector>
#include <random>

class RandomFruitSelector
{
private:
	std::vector<std::string> fruitNames;
	std::vector<int> weightOptions;
	std::vector<int> selectedFruit;

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
	* Return a random number based on the total of weights present
	* @ https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
	*/
	int generateRandomNumber()
	{
		std::random_device randomDistribution; 
		std::mt19937 gen(randomDistribution()); 

		std::uniform_int_distribution<> distribution(0, getTotalWeight() - 1);
		return distribution(gen);
	}

public:
	RandomFruitSelector(const std::vector<std::string>& fruitSymbols, const std::vector<int>& weights)
		: fruitNames(fruitSymbols), weightOptions(weights), selectedFruit(fruitSymbols.size(), 0)
	{
	}

	std::string getFruitName()
	{

		int randomNumber = generateRandomNumber();
		int cumulativeWeight = 0;
		std::string selectedRandomFruit;

		for (int i = 0; i < fruitNames.size(); ++i)
		{
			cumulativeWeight += weightOptions[i]; 

			
			if (randomNumber < cumulativeWeight) 
			{
				selectedRandomFruit = fruitNames[i];
				selectedFruit[i]++;
				return selectedRandomFruit;
				
			}
		}
	}

	void printSymbolCounts() const {
		std::cout << "Symbol Counts:\n";
		for (int i = 0; i < fruitNames.size(); ++i) {
			std::cout << fruitNames[i] << ": " << selectedFruit[i] << std::endl;
		}
	}
};

int main()
{
	std::vector<std::string> fruit = { "Seven", "Bell", "Melon", "Plum", "Orange", "Lemon", "Cherry" };
	std::vector<int> probabilities = { 10, 15, 20, 25, 15, 10, 5 };

	// Create a random fruit selector / generator object 
	RandomFruitSelector randomFruitSelector(fruit, probabilities);
	const int numberOfRuns = 15;

	for (int i = 0; i < numberOfRuns; ++i) {
		std::cout << "The chosen fruit corresponds to : " << randomFruitSelector.getFruitName() << std::endl;
	}

	randomFruitSelector.printSymbolCounts();

	return 0;
}