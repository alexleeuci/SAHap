/*
 * test1.cpp
 *
 *  Created on: Jul 29, 2019
 *      Author: me
 */

#include <iostream>
#include <tuple>
#include <vector>
#include <fstream>
#include <sstream>

struct read {
int pos;
std::string leftRead;
int pos2;
std::string rightRead;
};

read splitstring(std::string test){
    std::string chunk;
    read newRead;
    int index2=0;
    for(int i=0; i<4; i++){
        while(test[index2]!='\t' && index2!=test.length()){
            chunk = chunk + test[index2];
            index2 = index2 + 1;
        }
        if(i==0){
            std::istringstream iss (chunk);
            iss >> newRead.pos;

        }
        if(i==1){newRead.leftRead = chunk;}
        if(i==2){
            std::istringstream iss (chunk);
            iss >> newRead.pos2;

        }
        if(i==3){newRead.rightRead = chunk;}
        index2 = index2 + 1;
        chunk = "";
    }
    return newRead;
}

std::vector<std::string> readGenomeFile(std::string genomeFileName){
	std::ifstream genomeFile;
	genomeFile.open(genomeFileName);
	std::vector<std::string> out;
	std::string nextLine;
	while(genomeFile >> nextLine){
		out.push_back(nextLine);
	}
	return out;
}

std::vector<std::string> readReadFile(std::string readFileName){
	std::ifstream readFile;
	readFile.open(readFileName);
	std::vector<read> out;
	std::string nextLine;
	int index = 0;
	read newRead;
	while(! readFile.eof() ){
		getline(readFile, nextLine);
		newRead = splitstring(nextLine);
		out.push_back(newRead);
		newRead.pos=0;
		newRead.pos2=0;
		newRead.leftRead="";
		newRead.rightRead="";
	}
	return out;
}


float MEC(std::vector<int> sol,  std::vector<std::string> genomes ,std::vector<read> reads){
	float out;
	//Complete this!
	return out;
}

float score(std::vector<int> sol,  std::vector<std::string> genomes ,std::vector<read> reads){
	float out;
	//Complete this!
	return out;
}

float chanceToKeep(float scoreOfCurrent, float scoreOfNew, float temp){
	float out;
	//Complete this!
	return out;
}

std::vector<int> randomSolution(int k, std::vector<int> currentSolution){
	std::vector<int> out;
	return out;
}

std::vector<int> makeSolution(std::string genomeFileName, std::string readFileName, int in_numiters, float in_temp, float in_minTemp, float in_decreaseFactor){
    std::vector<std::string> myGenome;
    std::vector<read> myRead;
	myGenome = readGenomeFile(genomeFileName);
    myRead = readReadFile(readFileName);
	std::vector<int> minSolution;
	std::vector<int> currentSolution;
	int numiters = in_numiters;
	float temp = in_temp;
	float minTemp = in_minTemp;
	float decreaseFactor = in_decreaseFactor;
	while(temp>minTemp){
		for(int i = 0; i<numiters; i++){
			if(MEC(currentSolution, myGenome, myRead) < MEC(minSolution, myGenome, myRead)){
				minSolution = currentSolution; //make sure vector assignment works like this in C!
			}
			std::vector<int> newSolution = randomSolution(myGenome.size(), currentSolution);
			int scoreOfCurrent = score(currentSolution, myGenome, myRead);
			int scoreOfNew = score(newSolution, myGenome, myRead);
			float chanceToKeep = chanceToKeep(scoreOfCurrent, scoreOfNew, temp);
			float randomIndex = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			if(chanceToKeep>randomIndex){
				currentSolution = newSolution;
			}
		}
		temp = temp * decreaseFactor;
	}
	return minSolution;
}





int main()
{
    std::cout << "Hello, World!";
    std::vector<std::string> myGenome;
    std::vector<read> myRead;
    myGenome = readGenomeFile("test");
    myRead = readReadFile("testr");
    return 0;
}


