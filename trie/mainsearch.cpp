//
//  main.cpp
//  tries
//
//  Created by sunny on 12/4/15.
//  Copyright © 2015 Runxi Ding. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <fstream>

using namespace std;
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim = ' ') {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}
string join(vector<string> words) {
    auto begin = words.begin();
    string str = "";
    for (auto it = words.begin(); it<words.end(); ++it) {
        if (it == begin) {
            str += (*it);
        }
        else {
            str += " " + (*it);
        }
    }
    return str;
}
string file_get_contents(string path) {
    ifstream fin(path);
    stringstream buffer;
    buffer << fin.rdbuf();
    string result = buffer.str();
    return result;
}
string charToString(char c) {
    stringstream ss;
    string s;
    ss << c;
    ss >> s;
    return s;
}
int main(int argc, const char * argv[]) {
    map<string, int> primaryName_freq;
    map<vector<string>, string> synonym_primaryName;
    
    auto content = file_get_contents("companies.dat");
    
    auto lines = split(content, '\n');
    int maxWordsCnt = 0;
    for (int i = 0; i < lines.size(); ++i) {
        auto  company_names = split(lines[i], '\t');
        auto primary_name = company_names[0];//primary name
        for (auto it = company_names.begin(); it != company_names.end(); ++it) {
            auto words = split(*it, ' ');
            if (maxWordsCnt < words.size()) {
                maxWordsCnt = static_cast<int>(words.size());
            }
            synonym_primaryName[words] = primary_name;
            
        }
        
    }
    
    
    vector<string> words;
    string word;
    int wordsCnt = 0;
    cout << "Please type an article(new line with a period(.) to finish):" << endl;
    while (std::cin >> word) {
        //filter the words
        if (word == ".") {
            break;
        }
        if (word == "a" || word == "an" || word == "the" || word == "and" || word == "or" || word == "but") {
            continue;
        }
        string resultWord = "";
        for (char x : word) {
            if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z')) {
                resultWord += charToString(x);
            }
        }
        wordsCnt++;
        words.push_back(resultWord);
    }
    
    vector<string> strVec;
    vector<map<vector<string>, string>::iterator> mapIterStack;
    vector<vector<string>::iterator> vecIterStack;
    auto main_iter = words.begin();
    auto probe_iter = main_iter;
    while (main_iter != words.end()) {
        
        strVec.erase(strVec.begin(), strVec.end());
        mapIterStack.erase(mapIterStack.begin(), mapIterStack.end());
        vecIterStack.erase(vecIterStack.begin(), vecIterStack.end());
        probe_iter = main_iter;
        
        for (int i = 0; i< maxWordsCnt; ++i) {
            if ((probe_iter+i)<words.end()) {
                //strVec is the key of the map
                strVec.push_back(*(probe_iter+i));
                auto foundIter = synonym_primaryName.find(strVec);
                if (foundIter != synonym_primaryName.end()) {
                    mapIterStack.push_back(foundIter);//primary name++
                    vecIterStack.push_back((probe_iter+i));//jump to the probe
                }
                
            }
            else {
                break;
            }
        }
        
        if (mapIterStack.size() != 0) {
            auto iter = mapIterStack.back();
            // iter->second is the primary name, add the corrsbonding freq
            //if (primaryName_freq.find(iter->second) != primaryName_freq.end()){}
            primaryName_freq[iter->second]++;
            
        }
        if (mapIterStack.size()>1) {
            main_iter = vecIterStack.back();
        }
        else {
            ++main_iter;
        }
        
    }
    
    for (auto it = primaryName_freq.begin(); it != primaryName_freq.end(); ++it) {
        cout << it->first << ": " << it->second << "/" << wordsCnt << endl;
    }
    
    cout << "Press enter to exit" << endl;
    cin.get(); cin.get();
    
    return 0;
}
