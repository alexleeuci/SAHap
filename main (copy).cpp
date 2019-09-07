#include <iostream>
#include <fstream>
#include <random>
#include "Genome.hpp"

using namespace SAHap;
using namespace std;

void writeTo(Chromosome ch){
outputFile << "truth placeholder\n";
toEraseFromOverlapped_sets.clear();
unordered_set<Read *> overlapped_sets;
unordered_set<dnapos_t> visited;
std::string nextlinetowrite (ch.size(), '=');
for(Read* r : ch.reads){
	unordered_set<dnapos_t>  changed;
	for(Site s : r->sites){
		if(visited.find(s.pos)==visited.end()){
			if(s.value==Allele::REF){
				nextlinetowrite[s.pos] = '0';
			}
			if(s.value==Allele::ALT){
				nextlinetowrite[s.pos] = '1';
			}
			if(s.value==Allele::UNKNOWN){
				nextlinetowrite[s.pos] = '2';
			}
			visited.insert(s.pos);
			changed.insert(s.pos);
		}else{
			overlapped_sets.insert(r);
			for(dnapos_t revert : changed){
				nextlinetowrite[revert]='=';
				visited.erase(revert);
			}
			//readOverlaps = true;
			break;
		}
	}
}
outputFile << "FIRST ITER\n" << nextlinetowrite << endl;
unordered_set<dnapos_t>  changed;
unordered_set<Read*> toEraseFromOverlapped_sets;
bool readOverlaps = false;
while(overlapped_sets.size()!=0){
	cout << "---------------------------------------------------" << endl;
	//cout << "1-.\n" << endl;
	std::string nextlinetowrite (ch.size(), '=');
	visited.clear();
	for(Read* r : overlapped_sets){
		//cout << "2-.\n" << endl;
		//DEBUG
		cout << "\n\nDEBUG" << "\nstringtowrite\n\n\n" << nextlinetowrite << "\n\n\nnsize now: " << overlapped_sets.size() << endl;
		cout << "changed: ";
		for(dnapos_t c : changed){cout << c << " ";}
		cout << "\nvisited: ";
		for(dnapos_t v : visited){cout << v << " ";}
		cout << "\nreading being tested: ";
		for(Site s: r->sites){
			if(s.value==Allele::REF){
				cout << "0";
			}
			if(s.value==Allele::ALT){
				cout << "1";
			}
			if(s.value==Allele::UNKNOWN){
				cout << "2";
			} 						
		}
		cout << "\nread positions: ";
		for(Site s: r->sites){cout << s.pos << " ";}
		cout << endl;
		//
		changed.clear();
		toEraseFromOverlapped_sets.clear();
		for(Site s : r->sites){
			//cout << "3-.\n" << endl;
			if(visited.find(s.pos)==visited.end()){
				//cout << "\t3-1\n" << endl;
				if(s.value==Allele::REF){
					nextlinetowrite[s.pos] = '0';
				}
				if(s.value==Allele::ALT){
					nextlinetowrite[s.pos] = '1';
				}
				if(s.value==Allele::UNKNOWN){
					nextlinetowrite[s.pos] = '2';
				}
				visited.insert(s.pos);
				cout << "new visited insert: " << s.pos << endl;
				changed.insert(s.pos);
			}else{
				//cout << "\t3-2\n" << endl;
				cout << "\noffending position: " << s.pos << "\n";
				for(dnapos_t revert : changed){
					nextlinetowrite[revert]='=';
					visited.erase(revert);
				}
				readOverlaps = true;
				break;
			}
		}
		if(!readOverlaps){
			toEraseFromOverlapped_sets.insert(r);
		}
	}
	for(Read* r : toEraseFromOverlapped_sets){
		cout << "ERASED*************************************************************\n";
		if(overlapped_sets.find(r)==overlapped_sets.end()){
			cout << "ERROR: r was not in unordered set\n";
			exit(0);
		}
		overlapped_sets.erase(r);
	}
	outputFile << "INNER ITER\n" << nextlinetowrite << endl;
	cout << "\nline has been written;\n";
}
}
outputFile << "\n\n\n\n\n";
//
}






















int main(int argc, char *argv[]) {
	cout << "running";
	ofstream outputFile("errordata");
	cout << "running";
	if (argc <= 1) {
		cerr << "Usage: " << argv[0] << " [reads]" << endl;
		return 0;
	}
	
	if (argc == 3) {
		cout << "3args\n\n";
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
			//cout << "MEC: " << mecscore << " base truth diff: " << truthscore << endl;

			//output visual
			//outputFile << "----------------------------------------------------------------------------\n";
			outputFile << mecscore << endl;
			outputFile << truthscore << endl;
			bool readOverlaps = false;
			unordered_set<Read*> toEraseFromOverlapped_sets;
			for(auto ch : ge.chromosomes){
				toWrite(ch);
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

