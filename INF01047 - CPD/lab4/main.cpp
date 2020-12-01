#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include "rang.h"


/*
 *
 *  Author: Eduardo Fantini / 2020
 *
 *
 *  Chosen policies:
 *      1. Separate Chaining
 *
 *
 *  Chosen hashing functions:
 *      1. Polynomial (Horner)
 *      2. Modular
 *
 *
 * */


// number of keys
const int N = 10000;

using namespace std;


// Linked list struct
struct Node {
	string name;
	int key;
	int count;
	struct Node *next{};
};
struct LinkedList {
	
	Node *head,*tail;
	
	LinkedList() {
		head = nullptr;
		tail = nullptr;
	}
	
	bool contain(const string& data) {
		Node *tmp = head;
		while(tmp != nullptr) {
			if(tmp->name == data) {
				// ja existe
				return true;
			} else {
				tmp = tmp->next;
			}
		}
		// n ta na lista
		return false;
	}
	
	int containCount(const string& data) {
		Node *tmp = head;
		while(tmp != nullptr) {
			if(tmp->name == data) {
				return tmp->count;
			} else {
				tmp = tmp->next;
			}
		}
		return -1;
	}
	
	int containCountAccess(const string& data) {
		Node *tmp = head;
		int c = 1;
		while(tmp != nullptr) {
			if(tmp->name == data) {
				return c;
			} else {
				tmp = tmp->next;
				c++;
			}
		}
		return c;
	}
	
	// return true if had collision
	bool addNode(string data, int key) {
		
		// ja na lista
		if(contain(data)) {
			return false;
		}
		
		Node *tmp = new Node();
		tmp->name = move(data);
		tmp->next = nullptr;
		tmp->key = key;
		tmp->count = 0;
		
		if(head == nullptr) {
			// lista vazia
			head = tmp;
			tail = tmp;
			// sem colisao
			return false;
		} else {
			tail->next = tmp;
			tail = tail->next;
		}
		// com colisao
		return true;
	}
	
	void printList()
	{
		Node* temp = head;
		int i = 0;
		while (temp != nullptr) {
			cout << i << " | " << temp->name << endl;
			temp = temp->next;
			i++;
		}
	}
};

// Polynomial w/ direct chaining struct
struct HashTableChainPol {

private:
	int M;

public:
	vector<LinkedList> *table;
	HashTableChainPol() {
		M = N/5;                // buckets
		table = new vector<LinkedList>(M);        // table
	}
	
	void printTable() {
		int a = 0;
		cout << "\n\n\nValores não nulos da tabela: " << endl;
		for (auto & it : *table) {
			if(it.head != nullptr) {
				Node *tmp = it.head;
				while (tmp != it.tail) {
					cout << tmp->name << " at pos " << a << endl;
					tmp = tmp->next;
				}
			}
			a++;
		}
	}
	
	int getHash(string name) {
		
		if(name.empty())
			return 0;
		
		// offset of alphabet in ASCII
		int offset = 96;
		
		int hash = name[0] - offset;
		int p = 31;
		
		// iterate over name
		for(int i=1; i<name.length(); i++) {
			hash = hash * p + (name[i] - offset);
		}
		return abs(hash % M);;
	};
	
	// returns true if had collision
	bool insert(const string& data) {
		int hash = getHash(data);
		if(table->at(hash).addNode(data, hash)) {
			return true;
		}else{
			auto aux = table->at(hash).head;
			while(aux != nullptr) {
				
				if(aux->name == data)
					aux->count++;
				
				aux = aux->next;
			}
			return false;
		}
	}
	
	// return collision number
	int construct(const string& file_name){
		fstream file;
		string name;
		int i = 0;
		int collisions = 0;
		file.open (file_name);
		
		while(getline(file, name)){
			if(insert(name)) {
				// had collision
				collisions ++;
			}
			i++;
		}
		file.close();
		
		return collisions;
	}
	
	int search(const string& name) {
		int hash = getHash(name);
		return table->at(hash).containCount(name);
	}
	
	int searchCountAccess(const string& name) {
		int hash = getHash(name);
		return table->at(hash).containCountAccess(name);
	}
	
	float occupRate() {
		int c = 0;
		for(int i=0; i<M; i++) {
			if(table->at(i).head != nullptr) {
				c++;
			}
		}
		return ((float)c/(float)M);
	}
	
	void rehash() {
		
		vector<LinkedList> temp = *table;
		free(table);
		table = new vector<LinkedList>(M);
		
		for(auto & i : temp) {
			Node* aux = i.head;
			
			while(aux != nullptr) {
				int hash = aux->key;
				string s = aux->name;
				table->at(hash).addNode(s, hash);
				aux = aux->next;
			}
		}
	}
	
	void doubleTable() {
		M *= 2;
		rehash();
	}
	
	void halfTable() {
		M /= 2;
		rehash();
	}
	
	void minMax() {
		int max = 0;
		int min = 10000;
		string maxS;
		string minS;
		for(auto& it : *table) {
			if(it.head != nullptr) {
				Node *tmp = it.head;
				while (tmp != it.tail) {
					if(tmp->count > max) {
						max = tmp->count;
						maxS = tmp->name;
					}
					if(tmp->count < min) {
						min = tmp->count;
						minS = tmp->name;
					}
					tmp = tmp->next;
				}
			}
		}
		cout << "\nNome com maior número de entradas: " << maxS;
		cout << "\nNome com menor número de entradas: " << minS;
	}
	
	void printResults(const vector<string>& found, const vector<string>& notFound) {
		cout << "\n\nNomes não encontrados:\n";
		for(auto& it : found) {
			cout << it << " (-1)\n";
		}
		cout << "\n\nNomes encontrados:\n";
		for(auto& it : found) {
			cout << it << " encontrado com " << searchCountAccess(it) << " acesso(s).\n";
		}
	}
	
};

// Modular w/ direct chaining struct
struct HashTableChainMod {

private:
	int M;

public:
	vector<LinkedList> *table;
	HashTableChainMod() {
		M = N*1.2;                // buckets
		table = new vector<LinkedList>(M);        // table
	}
	
	void printTable() {
		int a = 0;
		cout << "\n\n\nValores não nulos da tabela: " << endl;
		for (auto & it : *table) {
			if(it.head != nullptr) {
				Node *tmp = it.head;
				while (tmp != it.tail) {
					cout << tmp->name << " at pos " << a << endl;
					tmp = tmp->next;
				}
			}
			a++;
		}
	}
	
	int getHash(string name) {
		
		if(name.empty())
			return 0;
		
		// offset of alphabet in ASCII
		int offset = 96;
		
		int hash = name[0] - offset;
		
		// iterate over name
		for(int i=1; i<name.length(); i++) {
			hash *= (name[i] - offset);
		}
		return abs(hash % M);;
	};
	
	bool insert(const string& data) {
		int hash = getHash(data);
		if(table->at(hash).addNode(data, hash))
			return true;
		else
			return false;
	}
	
	int construct(const string& file_name){
		fstream file;
		string name;
		int i = 0;
		int col = 0;
		file.open(file_name);
		
		while(getline(file, name)){
			if(insert(name)) {
				// had collision
				col ++;
			}
			i++;
		}
		file.close();
		
		return col;
	}
	
	int search(const string& name) {
		int hash = getHash(name);
		return table->at(hash).containCount(name);
	}
	
	int searchCountAccess(const string& name) {
		int hash = getHash(name);
		return table->at(hash).containCountAccess(name);
	}
	
	float occupRate() {
		int c = 0;
		for(int i=0; i<M; i++) {
			if(table->at(i).head != nullptr) {
				c++;
			}
		}
		return ((float)c/(float)M);
	}
	
	void rehash() {
		
		vector<LinkedList> temp = *table;
		table = new vector<LinkedList>(M);
		
		for(auto & i : temp) {
			Node* aux = i.head;
			
			while(aux != nullptr) {
				int hash = aux->key;
				string s = aux->name;
				table->at(hash).addNode(s, hash);
				aux = aux->next;
			}
		}
	}
	
	void doubleTable() {
		M *= 2;
		rehash();
	}
	
	void halfTable() {
		M /= 2;
		rehash();
	}
	
	void minMax() {
		int max = 0;
		int min = 10000;
		string maxS;
		string minS;
		for(auto& it : *table) {
			if(it.head != nullptr) {
				Node *tmp = it.head;
				while (tmp != it.tail) {
					if(tmp->count >= max) {
						max = tmp->count;
						maxS = tmp->name;
					}
					if(tmp->count < min) {
						min = tmp->count;
						minS = tmp->name;
					}
					tmp = tmp->next;
				}
			}
		}
		cout << "\nNome com maior número de entradas: " << maxS;
		cout << "\nNome com menor número de entradas: " << minS;
	}
	
	void printResults(const vector<string>& found, const vector<string>& notFound) {
		cout << "\n\nNomes não encontrados:\n";
		for(auto& it : found) {
			cout << it << " (-1)\n";
		}
		cout << "\n\nNomes encontrados:\n";
		for(auto& it : found) {
			cout << it << " encontrado com " << searchCountAccess(it) << " acesso(s).\n";
		}
	}
	
};

vector<string> populateSearchVector(const string& file_name) {
	
	fstream file;
	string name;
	vector<string> vec;
	file.open(file_name);
	
	while (getline(file, name)) {
		vec.push_back(name);
	}
	file.close();
	
	return vec;
}

int main(int argc, char** argv) {
	
	if(argc != 3) {
		cout << "Invalid arguments Usage " << argv[0]
		     << " (names file TXT) (search file TXT)" << endl;
		exit(1);
	}
	
	string namesFile = argv[1];
	string searchFile = argv[2];
	vector<string> searchVector = populateSearchVector(searchFile);
	vector<string> found;
	vector<string> notFound;
	
	HashTableChainMod tcm;
	cout << "\n=================================\n";
	cout << "\tMODULAR ENCADEADA\n";
	cout << "=================================";
	int constResTcm = (tcm.construct(namesFile));
	cout << "\nTamanho da tabela: " << tcm.table->size();
	cout << "\nTaxa de Ocupação: " << tcm.occupRate();
	cout << "\nTabela construída com um total de  " << constResTcm << " colisões.\n";
	for (const auto& it : searchVector) {
		if(tcm.search(it) != -1) {
			found.push_back(it);
		}
		notFound.push_back(it);
	}
	tcm.printResults(found, notFound);
	tcm.minMax();
	
	
	found.clear();
	notFound.clear();
	
	
	HashTableChainPol tcp;
	cout << "\n\n=================================\n";
	cout << "\tPOLINOMIAL ENCADEADA\n";
	cout << "=================================";
	int constResTcp = (tcp.construct(namesFile));
	cout << "\nTamanho da tabela: " << tcp.table->size();
	cout << "\nTabela construída com um total de " << constResTcp << " colisões.\n";
	cout << "\nTaxa de ocupação: " << tcp.occupRate();
	for (const auto& it : searchVector) {
		if(tcp.search(it) != -1) {
			found.push_back(it);
		}
		notFound.push_back(it);
	}
	tcp.printResults(found, notFound);
	tcp.minMax();

}
