#include <iostream>
#include <fstream>
#include <random>
#include "Genome.hpp"
#include <string>

using namespace SAHap;
using namespace std;

string siteTostring(Site s, string nextlinetowrite){
	if(s.value==Allele::REF){
		nextlinetowrite[s.pos] = '0';
	}
	if(s.value==Allele::ALT){
		nextlinetowrite[s.pos] = '1';
	}
	if(s.value==Allele::UNKNOWN){
		nextlinetowrite[s.pos] = '2';
	}
	return nextlinetowrite;
}

void writeTo(Chromosome ch, ofstream& outputFile){
	unordered_set<dnapos_t>  visited;
	unordered_set<Read *> overlapped_sets;
	std::string nextlinetowrite (ch.size(), '=');
	for(Read* r : ch.reads){
		unordered_set<dnapos_t>  changed;
		for(Site s : r->sites){
			if(visited.find(s.pos)==visited.end()){
				nextlinetowrite = siteTostring(s, nextlinetowrite);
				changed.insert(s.pos);
				visited.insert(s.pos);
			}else{
				overlapped_sets.insert(r);
				for(dnapos_t revert : changed){
					nextlinetowrite[revert]='=';
				}
				visited.insert(s.pos);
				break;
			}
		}
	}
	outputFile << nextlinetowrite << endl;

	visited.clear();
	bool readValid = true;
	unordered_set<Read*> toEraseFromOverlapped_sets;
	bool readOverlaps = false;
	while(overlapped_sets.size()!=0){
		//cout << "size now: " << overlapped_sets.size() << endl << "visited: ";
		for(auto v: visited){cout << v << " ";}
		//cout<<"\n";
		std::string nextlinetowrite (ch.size(), '=');
		//loop over all reads on overlapped_sets, get read r
		for(Read* r : overlapped_sets){
			//cout << "new read\n";
			readValid = true;
			//first, check if any of the sites in read r are already in the current string to print
			//if any pos is already in visited (eg, overlapping), then do not place it in toEraseFromOverlapped_sets. Set "readValid" to False
			for(Site s : r->sites){
				if(visited.find(s.pos)!=visited.end()){
					readValid = false;
					//cout << "offending position: " << s.pos << endl;;
					break;		
				}
			}
			//now, if the readValid is true, we can process it. Otherwise, just skip the processing and continue onto the next read
			if(readValid){
				//write each site onto the string, and records the visited position in visited.
				for(Site s : r->sites){
					nextlinetowrite = siteTostring(s, nextlinetowrite);
					visited.insert(s.pos);
					//cout << "\tinserted into visited: " << s.pos << "\n";
				}
				//then, add the read to toEraseFromOverlapped_sets
				toEraseFromOverlapped_sets.insert(r);
			}
		}
		//everytime we go through overlapped_sets once, we must clear out the reads that we can remove
		for(Read* r : toEraseFromOverlapped_sets){
			if(overlapped_sets.find(r)==overlapped_sets.end()){
				//cout<<"error: overlapped sets doen't have r\n";
				exit(0);
			}
			overlapped_sets.erase(r);
		}
		outputFile << nextlinetowrite << endl;
		//cout << "\nline has been written;\n";
		//once the string has been recorded, clear the visited list
		visited.clear();
		toEraseFromOverlapped_sets.clear();
	}
	outputFile << "\n\n\n\n\n\n\n";
}






















int main(int argc, char *argv[]) {
	ofstream outputFile("errordata",  std::ios_base::app);
	cout << "running";
	cout << "running";
	if (argc <= 4) {
		cerr << "Usage: " << argv[0] << endl;
		return 0;
	}
	
	ifstream file;
	ifstream truthfile;
	cout << "1\n";
	file.open(argv[1]);
	truthfile.open(argv[2]);
	cout << "2\n";
	auto parsed = WIFInputReader::read(file, 2);
	cout << "2-2\n";
	WIFInputReader::readGroundTruth(truthfile, parsed);	
	cout << "3\n";
	truthfile.close();
	//vector <string> truthlist;
	truthfile.open(argv[2]);
	//string line;
	//while(getline(truthfile, line)){
	//	truthlist.insert((std::string)line);
	//}
	string truth1;
	getline(truthfile, truth1);
	string truth2;
	getline(truthfile, truth2);
	truthfile.close();
	

	try {
		Genome ge(parsed);
		cout << "Loaded\n" << endl;
		// cout << ge.chromosomes[0].percentAgree() << endl;
		//for (float e = -5; e <= 2; e += 0.1) {
		float temp = 1.0;
		while(temp > 0.0000001){
			//float temp = pow(10, e);
			auto pbad = ge.findPbad(temp);
			dnaweight_t mecscore = ge.mec();
			dnacnt_t truthscore = ge.compareGroundTruth();
			cout << "MEC: " << mecscore << " base truth diff: " << truthscore << endl;

			//output visual
			//outputFile << "----------------------------------------------------------------------------\n";
			bool readOverlaps = false;
			unordered_set<Read*> toEraseFromOverlapped_sets;
			outputFile << "MEC: " << mecscore << " truth score: " << truthscore << "\n";
			int index = 0;
			for(auto ch : ge.chromosomes){
				if(index==0){outputFile << truth1 << endl;}
				if(index==1){outputFile << truth2 << endl;}
				writeTo(ch, outputFile);
				index+=1;
			}
			outputFile << "\n\n\n\n\n";
			temp = temp * 0.95;
		}

	} catch (const char* e) {
		cout << e << endl;
	}
	// ge.optimize();

	// /*
	// for (float e = -10; e <= 10; ++e) {
	// 	float temp = pow(10, e);
	// 	cout << temp << ": " << ge.findPbad(temp) << endl;
	// }
	// */
	// /*
	// for (float i = 1; i > 0; i -= 0.1f) {
	// 	cout << "pBad @ " << i << " = " << ge.findPbad(100) << endl;
	// }
	// */

	return 0;
}

