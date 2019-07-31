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

std::vector<read> readReadFile(std::string readFileName){
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

float MEC(std::vector<int> sol,  int k ,std::vector<read> reads, int*** votes){
	float out;
	//Complete this!
	return out;
}

void fillVotes(std::vector<read> reads, std::vector<int> currentSolution, int*** votes, int& totalGenomeLen){
	int max = 0;
	for(int readIndex1 = 0; readIndex1<reads.size(); readIndex1++){
		read readBeingAdded = reads[readIndex1];
		for(int leftReadIndex = 0; leftReadIndex<readBeingAdded.leftRead.length(); leftReadIndex++){
			char letterBeingAdded = readBeingAdded.leftRead;
			int chromosomeIndex = currentSolution[readIndex1];
			if(letterBeingAdded=='a'){votes[0][chromosomeIndex][readBeingAdded.pos+leftReadIndex]++;}
			if(letterBeingAdded=='t'){votes[1][chromosomeIndex][readBeingAdded.pos+leftReadIndex]++;}
			if(letterBeingAdded=='g'){votes[2][chromosomeIndex][readBeingAdded.pos+leftReadIndex]++;}
			if(letterBeingAdded=='c'){votes[3][chromosomeIndex][readBeingAdded.pos+leftReadIndex]++;}
		}
		for(int rightReadIndex = 0; rightReadIndex<readBeingAdded.rightRead.length(); rightReadIndex++){
			char letterBeingAdded = readBeingAdded.rightRead;
			int rightmostIndex = readBeingAdded.pos2+rightReadIndex;
			if(rightmostIndex<max){
				max = rightmostIndex;
			}
			int chromosomeIndex = currentSolution[readIndex1];
			if(letterBeingAdded=='a'){votes[0][chromosomeIndex][rightmostIndex]++;}
			if(letterBeingAdded=='t'){votes[1][chromosomeIndex][rightmostIndex]++;}
			if(letterBeingAdded=='g'){votes[2][chromosomeIndex][rightmostIndex]++;}
			if(letterBeingAdded=='c'){votes[3][chromosomeIndex][rightmostIndex]++;}
		}
	}
	totalGenomeLen = max;
}

void destroyVotes(int*** votes, int x, int y, int z){
	for(int xi = 0; xi<x; xi++){
		for(int yi = 0; yi<y; yi++){
			delete[] votes[xi][yi];
		}
	}
}

float score(float temp, float MECval){
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

std::vector<int> randomSolution(int k){
	//To use when currentSolution is empty
	std::vector<int> out;
	return out;
}


std::vector<int> makeSolution(int k, int m, std::string readFileName, int in_numiters, float in_temp, float in_minTemp, float in_decreaseFactor){
    std::vector<read> myRead;
    myRead = readReadFile(readFileName);
	std::vector<int> minSolution;
	std::vector<int> currentSolution;
	int numiters = in_numiters;
	float temp = in_temp;
	float minTemp = in_minTemp;
	float decreaseFactor = in_decreaseFactor;
	int*** votes = new int[4][k][m];
	currentSolution = randomSolution(k);
	fillVotes(myRead, currentSolution, votes, m);
	while(temp>minTemp){
		for(int i = 0; i<numiters; i++){
			int currentMEC = MEC(currentSolution, k, myRead, votes);
			if( currentMEC < MEC(minSolution, k, myRead, votes)){
				minSolution = currentSolution; //make sure vector assignment works like this in C!
			}
			std::vector<int> newSolution = randomSolution(k, currentSolution);
			int newMEC = MEC(newSolution, k, myRead, votes);
			int scoreOfCurrent = score(temp, newMEC);
			int scoreOfNew = score(temp, newMEC);
			float chanceToKeep = chanceToKeep(scoreOfCurrent, scoreOfNew, temp);
			float randomIndex = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			if(chanceToKeep>randomIndex){
				currentSolution = newSolution;
			}
		}
		temp = temp * decreaseFactor;
	}
	destroyVotes(votes, 4, k, m);
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



