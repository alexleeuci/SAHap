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

typedef std::vector<std::vector<std::vector<int> > > array3d;

read splitstring(std::string test){
    std::string chunk;
    read newRead;
    unsigned int index2=0;
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

float MEC(std::vector<int> sol,  int k ,std::vector<read> reads, array3d votes){
	float out;
	//Complete this!
	return out;
}

void fillVotes(std::vector<read> reads, std::vector<int> currentSolution, array3d& votes, int k, int m){
	int max = 0;
	std::cout << "p2\n\n";
	for(int chromIndex=0; chromIndex<4; chromIndex++){
		for(int ki = 0; ki<k; ki++){
			for(int mi = 0; mi<m; mi++){
				votes[chromIndex][ki][mi]=0;
			}
		}
	}
	std::cout << "p3\n\n";
	for(unsigned int readIndex1 = 0; readIndex1<reads.size(); readIndex1++){
		read readBeingAdded = reads[readIndex1];
		for(unsigned int leftReadIndex = 0; leftReadIndex<readBeingAdded.leftRead.length(); leftReadIndex++){
			std::cout << "p4\n\n";
			char letterBeingAdded = readBeingAdded.leftRead[leftReadIndex];
			std::cout << "p5\n\n";
			int chromosomeIndex = currentSolution[readIndex1];
			std::cout << "p6\n\n";
			if(letterBeingAdded=='a'){votes[0][chromosomeIndex][readBeingAdded.pos+leftReadIndex-1]++;}
			if(letterBeingAdded=='t'){votes[1][chromosomeIndex][readBeingAdded.pos+leftReadIndex-1]++;}
			if(letterBeingAdded=='g'){votes[2][chromosomeIndex][readBeingAdded.pos+leftReadIndex-1]++;}
			if(letterBeingAdded=='c'){votes[3][chromosomeIndex][readBeingAdded.pos+leftReadIndex-1]++;}
			std::cout << "p7\n\n";
		}
		for(unsigned int rightReadIndex = 0; rightReadIndex<readBeingAdded.rightRead.length(); rightReadIndex++){
			char letterBeingAdded = readBeingAdded.rightRead[rightReadIndex];
			int rightmostIndex = readBeingAdded.pos2+rightReadIndex-1;
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
}

float score(float temp, float MECval){
	float out;
	//Complete this!
	return out;
}

float chanceToKeepFunc(float scoreOfCurrent, float scoreOfNew, float temp){
	float out;
	//Complete this!
	return out;
}

std::vector<int> randomSolution(int k, std::vector<int> currentSolution){
	std::vector<int> out;
	return out;
}

std::vector<int> randomSolution(int k, int m){
	std::vector<int> out;
	for(int i = 0; i<m; i++){
		int nextInt = rand()%k;
		out.push_back(nextInt);
	}
	return out;
}


std::vector<int> makeSolution(const int k, const int m, std::string readFileName, int in_numiters, float in_temp, float in_minTemp, float in_decreaseFactor){
	std::vector<read> myRead;
    myRead = readReadFile(readFileName);
	std::vector<int> minSolution;
	std::vector<int> currentSolution;
	int numiters = in_numiters;
	float temp = in_temp;
	float minTemp = in_minTemp;
	float decreaseFactor = in_decreaseFactor;
	array3d votes(4, std::vector<std::vector<int> >(k, std::vector<int>(m, 0)));
	currentSolution = randomSolution(k, m);
	fillVotes(myRead, currentSolution, votes, k, m);
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
			float chanceToKeep = chanceToKeepFunc(scoreOfCurrent, scoreOfNew, temp);
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
    std::vector<int> sol;
    myGenome = readGenomeFile("test");
    myRead = readReadFile("testr");
    const int testk1 = 3;
    const int testm1 = 11;
    array3d votes(4, std::vector<std::vector<int> >(testk1, std::vector<int>(testm1, 0)));
    std::vector<int> newSol;
    newSol = randomSolution(testk1, testm1);
    std::cout << "p1\n\n";
    fillVotes(myRead, newSol, votes, testk1, testm1);
    for(int i = 0; i<4; i++){
    	for(int j = 0; j<testk1; j++){
    		for(int k = 0; k<testm1; k++){
    			std::cout << votes[i][j][k];
    		}
    		std::cout << "\n";
    	}
    	std::cout << "\n---------------------------------------------\n";
    }
    std::cout << "\ndone\n";
    return 0;
}


