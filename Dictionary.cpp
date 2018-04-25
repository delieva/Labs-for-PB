#include "iostream"
#include "fstream"
#include "string"
int amount;
using namespace std;
struct Node {
	string word;
	string meaning;
	Node* next = NULL;
};

struct HashTable {
	int element;
	Node* next = NULL;

};

void insertingElement(HashTable hashTable[], const string word, int hash);
string searchExplaining(HashTable hashTable[], string word, int hash);
int findingKey(string word, int hash);
void deletion_ht(HashTable *ht);
HashTable *makingBigger(HashTable *ht, int hash);

int main() {
	amount = 53;
	string inputedWord;
	cout << "input word: " << endl;
	cin >> inputedWord;
	string word;
	for (int i = 0; i < inputedWord.length(); i++) {
		word += toupper(inputedWord[i]);
	}

	int hash = 0;
	auto *hashTable = new HashTable[amount];
	ifstream fin("E:\dict_processed.txt");
	int counter = 0;
	if (fin.is_open()) {
		while (fin.good()) {
			string current;
			getline(fin, current);
			insertingElement(hashTable, current, hash);
			counter++;
			if (counter > 0.8*amount) {
				hashTable = makingBigger(hashTable, hash);
				amount = amount * 2;
			}
		}
	};

	cout << searchExplaining(hashTable, word, hash) << endl;
	deletion_ht(hashTable);
	fin.close();
	system("pause");
	return 0;
}

void insertingElement(HashTable hashTable[], const string meaning, int hash) {
	string word;
	int i = 0;
	while (meaning[i] != ';') {
		word += meaning[i];
		i++;
	}
	int key = findingKey(word, hash);
	auto *node = new Node;
	node->meaning = meaning;
	node->word = word;
	if (hashTable[key].element == key) {
		node->next = hashTable[key].next;
		hashTable[key].next = node;
	}
	else {
		hashTable[key].element = key;
		hashTable[key].next = node;
	}
}

int findingKey(string word, int hash) {
	for (int i = 0; i < word.length(); i++) {
		hash += word[i];
	}
	int key = hash % amount;
	return key;
}

string searchExplaining(HashTable hashTable[], string word, int hash) {
	int key = findingKey(word, hash);
	if (hashTable[key].element == key) {
		Node *current = hashTable[key].next;
		while (current->next != nullptr && current->word != word) {
			current = current->next;
		}
		if (current->word == word) {
			return current->meaning;
		}
		return "No such a word!";
	}
	else
		return "No such a word!";
}

void deletion_ht(HashTable * ht) {
	for (int i = 0; i < amount; i++) {
		if (ht[i].next != nullptr) {
			while (ht[i].next != nullptr) {
				Node *current = ht[i].next;
				ht[i].next = ht[i].next->next;
				delete current;
			}
		}
	}
	delete[] ht;
}
HashTable *makingBigger(HashTable *hashTable, int hash) {
	auto * newHT = new HashTable[amount * 2];
	for (int i = 0; i < amount; i++) {
		if (hashTable[i].next != nullptr) {
			Node *current = hashTable[i].next;
			while (current != nullptr) {
				insertingElement(newHT, current->meaning, hash);
				current = current->next;
			}
		}
	}
	deletion_ht(hashTable);
	return newHT;
}



