#include <vector>
#include <algorithm>
#include <string>

#define ALPH_SIZE 68 // 'a'-'z', '0'-'9', '.', '()', ',', ':', '-', '&', ...
#define ASCII_OFFSET 97 // 'a'

using namespace std;

int trieIndex(char c);

// Movie
class MovieTrie {
public:
    MovieTrie *children[ALPH_SIZE];
    bool final; // se alguma palavra termina nesse nodo
    int movieId;

    MovieTrie();
    void insert(string movie, int id);
    int search(string movie);
    vector<int> prefixSearch(string arg);
};

bool isLastMovie(MovieTrie *m);

void collectMovies(MovieTrie* root, vector<int> *ids);

void populateMovieTrie(MovieTrie *m_trie, vector<string> movies, vector<int> ids);

// Genre
class GenreTrie {
public:
	GenreTrie *children[ALPH_SIZE];
	bool final; // se alguma palavra termina nesse nodo
	vector<int> movieId;
	
	GenreTrie();
	void insert(vector<string> genres, int id);
	vector<int> search(string genre);
};

bool isLastGenre(GenreTrie *g_trie);

void populateGenreTrie(GenreTrie *g_trie, vector<vector<string>> genres, vector<int> ids);

// Tag
class TagTrie {

public:
    TagTrie *children[ALPH_SIZE];
    bool final; // se alguma palavra termina nesse nodo
    vector<int> movies; // filmes nessa tag

    TagTrie();
    void insert(string tag, int movie);
    vector<int> search(string tag);
    vector<int> prefixSearch(string tag);

};

bool isLastTag(TagTrie *t);

void collectTags(TagTrie *root, vector<int> *ids);

void populateTagTrie(TagTrie *t_trie, vector<string> tags, vector<int> ids);


