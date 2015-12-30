
//
//  main.cpp
//  trie_by_trie
//
//  Created by sunny on 12/6/15.
//  Copyright © 2015 Runxi Ding. All rights reserved.
//

#include <iostream>
#include <memory>
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

struct node {
    string word = "";
    int count = 0;
    shared_ptr<struct node> left = nullptr;
    shared_ptr<struct node> right = nullptr;
    shared_ptr<struct node> next = nullptr;
};

class WordTrie {
private:
    shared_ptr<struct node>  root = nullptr;
    int size = 0;
public:
    void addWords(vector<string> words) {
        shared_ptr<struct node> tmpPtr = nullptr;
        for (int i = 0; i< words.size(); ++i) {
            auto node = make_shared<struct node>();
            bool isLastWord = (i == (words.size() - 1));
            node->word = words[i];
            if (i == 0) {
                tmpPtr = addFirstNode(node, isLastWord);
            }
            else {
                tmpPtr = addNodeByFirstWordPtr(tmpPtr, node, isLastWord);
            }
        }
    }
    
    shared_ptr<struct node> addNodeByFirstWordPtr(shared_ptr<struct node> firstNodePtr, shared_ptr<struct node>  node, bool isLastword) {
        if (isLastword) {
            node->count++;
        }
        
        if (firstNodePtr->next == nullptr) {
            firstNodePtr->next = node;
            firstNodePtr = firstNodePtr->next;
            
        }
        else if (firstNodePtr->next != nullptr) {
            firstNodePtr = firstNodePtr->next;
            while (1) {
                if (firstNodePtr->word.compare(node->word) > 0) {//look left
                    if (firstNodePtr->left == nullptr) {
                        firstNodePtr->left = node;
                        firstNodePtr = firstNodePtr->left;
                        break;
                    }
                    firstNodePtr = firstNodePtr->left;
                    break;
                }
                else if (firstNodePtr->word.compare(node->word) < 0) {//look right
                    if (firstNodePtr->right == nullptr) {
                        firstNodePtr->right = node;
                        firstNodePtr = firstNodePtr->right;
                        break;
                    }
                    firstNodePtr = firstNodePtr->right;
                    break;
                }
                else if (firstNodePtr->word.compare(node->word) == 0) {
                    firstNodePtr->count = node->count;
                    //firstNodePtr = firstNodePtr->next; the most important comment
                    break;
                }
            }
        }
        
        
        return firstNodePtr;
    }
    shared_ptr<struct node> addFirstNode(shared_ptr<struct node> node, bool isLastWord) {
        auto probe = root;
        if (isLastWord) {
            node->count++;
        }
        while (1) {
            if (root == nullptr) {
                probe = root = node;
                break;
            }
            else if (probe->word.compare(node->word) > 0) {//to left
                if (probe->left == nullptr) {
                    probe->left = node;
                    probe = probe->left;
                    break;
                }
                probe = probe->left;
            }
            else if (probe->word.compare(node->word)< 0) {
                if (probe->right == nullptr) {
                    probe->right = node;
                    probe = probe->right;
                    break;
                }
                probe = probe->right;
            }
            else if (probe->word.compare(node->word) == 0) {
                probe->count = probe->count + node->count;
                break;
            }
        }
        return probe;
    }
    
    shared_ptr<struct node> getRoot() {
        return root;
    }
    
    bool findWords(vector<string> words) {
        auto firstPtr = findFirstWordNodePtr(getRoot(), words[0]);
        if (firstPtr != nullptr && words.size() == 1) {
            return true;
        }
        if (firstPtr == nullptr) {
            return false;
        }
        firstPtr = firstPtr->next;
        for (int i = 1; i<words.size(); i++) {
            
            while (1) {
                if (firstPtr == nullptr) {
                    return false;
                }
                if (firstPtr->word.compare(words[i]) > 0) {//look left
                    if (firstPtr->left == nullptr) {
                        return false;
                    }
                    firstPtr = firstPtr->left;
                }
                else if (firstPtr->word.compare(words[i]) < 0) {//look right
                    if (firstPtr->right == nullptr) {
                        return false;
                    }
                    firstPtr = firstPtr->right;
                    
                }
                else if (firstPtr->word.compare(words[i]) == 0) {//if not last word next
                    if (i == (words.size() - 1) && firstPtr->count>0) {
                        return true;
                    }
                    firstPtr = firstPtr->next;
                    break;
                }
                
            }
            
        }
        return false;
    }
    
    shared_ptr<struct node> findFirstWordNodePtr(shared_ptr<struct node> _root, string firstWord) {
        shared_ptr<struct node>  resultPtr = nullptr;
        if (_root == nullptr) {
            
        }
        else {
            if (_root->word.compare(firstWord) > 0) { // to left
                auto p1 = findFirstWordNodePtr(_root->left, firstWord);
                if (p1 != nullptr) {
                    resultPtr = p1;
                }
            }
            else if (_root->word.compare(firstWord) <0) { // to right
                auto p2 = findFirstWordNodePtr(_root->right, firstWord);
                if (p2 != nullptr) {
                    resultPtr = p2;
                }
            }
            else {// find first words
                return _root;
            }
        }
        return        resultPtr;
    }
    
};
string charToString(char c) {
    stringstream ss;
    string s;
    ss << c;
    ss >> s;
    return s;
}

string file_get_contents(string path) {
    ifstream fin(path);
    stringstream buffer;
    buffer << fin.rdbuf();
    string result = buffer.str();
    return result;
}

int main(int argc, const char * argv[]) {
    
    map<string, int> primaryName_freq;
    map<vector<string>, string> synonym_primaryName;
    WordTrie wt;
    
    auto content = file_get_contents("companies.dat");
    
    auto lines = split(content, '\n');
    int maxWordsCnt = 0;
    for (int i = 0; i < lines.size(); ++i) {
        auto  company_names = split(lines[i], '\t');
        auto primary_name = company_names[0];//primary name
        for (auto it = company_names.begin(); it != company_names.end(); ++it) {
            auto words = split(*it, ' ');
            wt.addWords(words);
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
                
                bool isFound = wt.findWords(strVec);
                if (isFound) {
                    auto foundIter = synonym_primaryName.find(strVec);
                    mapIterStack.push_back(foundIter);//primary name++
                    vecIterStack.push_back((probe_iter+i));//jump to the probe
                }
                
            }else {
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
