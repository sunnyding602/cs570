//
//  RunxiDing.cpp
//  Hello
//
//  Created by Ding,Runxi on 8/27/15.
//  Copyright (c) 2015 bunengzhai. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


unsigned long count_word(string word, int &one_letter_word_cnt, int &two_letter_word_cnt, int&three_letter_word_cnt, string &one_letter_words, string &two_letter_words, string &three_letter_words);
void output_table(int one_letter_word_cnt, int two_letter_word_cnt, int three_letter_word_cnt, string one_letter_words, string two_letter_words, string three_letter_words);
int main(int argc, const char * argv[]) {

	string word;
	int one_letter_word_cnt = 0;
	int two_letter_word_cnt = 0;
	int three_letter_word_cnt = 0;
	string one_letter_words = "";
	string two_letter_words = "";
	string three_letter_words = "";

	ifstream filein("input.txt");

	if (filein.fail()) {
		cout << "open file failed!" << filein.fail() << endl;
	}

	while (filein >> word) {
		count_word(word, one_letter_word_cnt, two_letter_word_cnt, three_letter_word_cnt, one_letter_words, two_letter_words, three_letter_words);
	}
	filein.close();

	output_table(one_letter_word_cnt, two_letter_word_cnt, three_letter_word_cnt, one_letter_words, two_letter_words, three_letter_words);

	return 0;
}

void output_table(int one_letter_word_cnt, int two_letter_word_cnt, int three_letter_word_cnt, string one_letter_words, string two_letter_words, string three_letter_words) {


	cout << "1-letter word count: " << one_letter_word_cnt << "\t they are: " << one_letter_words << endl;
	cout << "2-letter word count: " << two_letter_word_cnt << "\t they are: " << two_letter_words << endl;
	cout << "3-letter word count: " << three_letter_word_cnt << "\t they are: " << three_letter_words << endl;

}


unsigned long count_word(string word, int &one_letter_word_cnt, int &two_letter_word_cnt, int&three_letter_word_cnt, string &one_letter_words, string &two_letter_words, string &three_letter_words) {

	if (word.length() == 1) {
		one_letter_word_cnt++;
		one_letter_words = one_letter_words + word + " ";
	}
	else if (word.length() == 2) {
		two_letter_word_cnt++;
		two_letter_words = two_letter_words + word + " ";
	}
	else if (word.length() >= 3) {
		three_letter_word_cnt++;
		three_letter_words = three_letter_words + word + " ";
	}
	return word.length();
}