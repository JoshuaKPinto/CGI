#ifndef WAVEFRONT_PARSER_H
#define WAVEFRONT_PARSER_H

#include <fstream>
#include <string>
#include <vector>
#include "linalg.h"

using namespace std;

class Parser
{
private:
	std :: ifstream myFile;
	string delim = " ";

public:
	Parser(string, vector<Vec3f>&, std::vector<face>&);
	~Parser();

};

Parser :: Parser (string file_name, vector<Vec3f>& w, std::vector<face>& q){
	// cout << "Parser function not complete!\n";
	myFile.open(file_name);

	string line;

	if(myFile.is_open()){

		while(std :: getline(myFile, line)){

			if((line[0] == 'v') and (line[1] == ' ')){
				// Code to parse vertex lines
				Vec3f v(0,0,0);
				size_t pos = 0;
				string token;
				line.erase(0,2);
				int i = 0;

				while ((pos = line.find(delim)) != string::npos) {
				    token = line.substr(0, pos);
				    float val = stof(token);
				    v[i++] = val;
				    line.erase(0, pos + 1);
				}
				// cout << stof(line) << endl;
				v[i] = stof(line);
				w.push_back(v);

			}

			if(line[0] == 'f'){
				face mface;
				string token;
				string sub_token;
				size_t pos, sub_pos;
				line.erase(0, 2);


				while ((pos = line.find(delim)) != string::npos){
					token = line.substr(0, pos);
					sub_pos = token.find("/");
					sub_token = token.substr(0, sub_pos);
					int val = stof(sub_token) - 1;
					line.erase(0, pos + 1);
					mface.set_face(val);
				}
				pos = line.find("/");
				sub_token = line.substr(0, pos);
				int val = stof(sub_token) - 1;
				mface.set_face(val);
				q.push_back(mface);
			}


		}
	}
}

Parser :: ~Parser(){
	cout << "Parser Destroyed! \n";
	myFile.close();
}

#endif
