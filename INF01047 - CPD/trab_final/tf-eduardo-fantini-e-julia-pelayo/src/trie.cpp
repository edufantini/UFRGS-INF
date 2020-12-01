#include "trie.h"

// -------------------------------------------
//      mapeamento de todos char's usados
// -------------------------------------------
int trieIndex(char c){
  switch (c) {
    case '(':
      return 36;
    case ')':
      return 37;
    case '.':
      return 38;
    case ',':
      return 39;
    case '\'':
      return 40;
    case ':':
      return 41;
    case ' ':
      return 42;
    case '-':
      return 43;
    case '&':
      return 44;
    case '!':
      return 45;
    case '/':
      return 46;
    case '?':
      return 47;
    case '+':
      return 48;
    case '*':
      return 49;
    case '$':
      return 50;
    case '#':
      return 51;
    case '_':
      return 52;
    case '\\':
      return 53;
    case '"':
      return 54;
    case '|':
      return 55;
    case '%':
      return 56;
    case ';':
      return 57;
    case '[':
      return 58;
    case ']':
      return 59;
    case '@':
      return 60;
    case '=':
      return 61;
    case '~':
      return 62;
    case '`':
	  return 63;
    case '\t':
	  return 64;
    case '<':
	  return 65;
    case '^':
	  return 66;
    case '>':
	  return 67;
    default:
      if(c >= 'A' && c<='Z'){
        return c-'A';
      }
      if(c >= 'a' && c <='z'){
        int to_upper = 'A' - 'a';
        return c + to_upper - 'A';
      }
      if(c >= '0' && c<='9'){
        char n = c - '0';
        return n + 'Z' - 'A';
      }
      else return -1;
  }
}

// ----------- Movie -----------------
MovieTrie::MovieTrie() {
  final = false;
  // nulo em todos filhos
  for(int i=0; i < ALPH_SIZE; i++) {
    children[i] = NULL;
  }
  movieId = 0;
}


void MovieTrie::insert(string movie, int id) {
  MovieTrie *aux = this;
  char c;

  for(int i=0; i < movie.length(); i++) {

    // index dentro da arvore
    c = movie[i];
    int index = trieIndex(c);
    // cout << "insere => " << c << " | " << index << endl;

    if (!aux->children[index]) {
      // indice nao ocupado, cria outro nodo
      aux->children[index] = new MovieTrie();
      aux = aux->children[index];
    } else {
      // indice ocupado, anda para proximo
      aux = aux->children[index];

    }

  }

  // terminou de varrer a palavra, setar folha como final
  aux->final = true;
  aux->movieId = id;
}

bool isLastMovie(MovieTrie *m) {
	for(int i=0; i < ALPH_SIZE; i++) {
		if(m->children[i])
			return false;
	}
	return true;
}

int MovieTrie::search(string movie) {

MovieTrie *aux = this;
char c;

for(int i=0; i < movie.length(); i++) {

    c = movie[i];
    int index = trieIndex(c);
    // cout << "busca => " << c << " | " << index << endl;

    if (!aux->children[index]) {
      // n existe, retorna false
      return -1;
    } else {
      // existe, anda proximo
      aux = aux->children[index];
    }
  }

  // varreu toda palavra
  // pode ser nodo nulo (n encontrou)
  // se nodo n é nulo, ver se é final
  // se for final, encontrou retorna true
  if (aux == NULL || !aux->final || aux->movieId == 0)
    return -1;
  return aux->movieId;
}

void collectMovies(MovieTrie *root, vector<int> *ids) {

	MovieTrie *aux = root;
	
	// base da recursao
	if(aux->final)
		ids->push_back(aux->movieId);
	
	//passo
	for(int i=0; i<ALPH_SIZE; i++) {
		if(aux->children[i])
			collectMovies(aux->children[i], ids);
	}

}

vector<int> MovieTrie::prefixSearch(string arg) {
	
	MovieTrie *aux = this;
	vector<int> v;
	char c;
	
	for(int i=0; i < arg.length(); i++) {
		c = arg[i];
		int index = trieIndex(c);
		
		if (!aux->children[index]) {
			// n existe, retorna false
			return v;
		}
		
		if (aux->children[index]) {
			// existe, anda proximo
			aux = aux->children[index];
		}
	}
	
	// parou de percorrer
	// nesse ponto, aux é a 'raiz' da busca
	collectMovies(aux, &v);
	
	return v;
}

void populateMovieTrie(MovieTrie *m_trie, vector<string> movies, vector<int> ids) {
	for (int i = 0; i < movies.size(); ++i) {
		m_trie->insert(movies[i], ids[i]);
	}
}

// -------------- Genre ---------------
// constructor
GenreTrie::GenreTrie() {
	final = false;
	// nulo em todos filhos
	for(int i=0; i < ALPH_SIZE; i++) {
		children[i] = NULL;
	}
	movieId = {0};
}


void GenreTrie::insert(vector<string> genres, int id) {
	GenreTrie *aux = this;
	char c;
	
	for(int j=0; j<genres.size(); j++) {
		
		for (int i = 0; i < genres[j].length(); i++) {
			
			// index dentro da arvore
			c = genres[j][i];
			int index = trieIndex(c);
			
			if (!aux->children[index]) {
				// indice nao ocupado, cria outro nodo
				aux->children[index] = new GenreTrie();
				aux = aux->children[index];
			} else {
				// indice ocupado, anda para proximo
				aux = aux->children[index];
			}
			
		}
		// terminou de varrer a palavra, setar folha como final
		if(aux->final) {
			aux->movieId.push_back(id);
		}else{
			aux->final = true;
			aux->movieId.clear();
			aux->movieId.push_back(id);
		}
	}
}

bool isLastGenre(GenreTrie *g_trie) {
	for(int i=0; i < ALPH_SIZE; i++) {
		if(g_trie->children[i])
			return false;
	}
	return true;
}

// se achou retorna o id
// senão retorna -1
vector<int> GenreTrie::search(string genre) {
	
	GenreTrie *aux = this;
	vector<int> v;
	char c;
	
	for(int i=0; i < genre.length(); i++) {
		
		c = genre[i];
		int index = trieIndex(c);
		// cout << "busca => " << c << " | " << index << endl;
		
		if (!aux->children[index]) {
			// n existe, retorna false
			return v;
		} else {
			// existe, anda proximo
			aux = aux->children[index];
		}
	}
	
	// varreu toda palavra
	// pode ser nodo nulo (n encontrou)
	// se nodo n é nulo, ver se é final
	// se for final, encontrou retorna true
	if (aux == NULL || !aux->final || aux->movieId.empty())
		return v;
	return aux->movieId;
}

void populateGenreTrie(GenreTrie *g_trie, vector<vector<string>> genres, vector<int> ids) {
	for (int i = 0; i < genres.size(); ++i) {
		g_trie->insert(genres[i], ids[i]);
	}
}

// ----------- Tag --------------
TagTrie::TagTrie() {
  final = false;
  // nulo em todos filhos
  for(int i=0; i < ALPH_SIZE; i++) {
    children[i] = NULL;
  }
}

void TagTrie::insert(string tag, int movie) {
  TagTrie *aux = this;
  char c;

  for(int i=0; i < tag.length(); i++) {

    // index dentro da arvore
    c = tag[i];
    int index = trieIndex(c);

    if (!aux->children[index]) {
      // indice nao ocupado, cria outro nodo
      aux->children[index] = new TagTrie();
      aux = aux->children[index];
    } else {
      // indice ocupado, anda para proximo
      aux = aux->children[index];
    }
  }
  
  aux->final = true;
  aux->movies.push_back(movie);
}

bool isLastTag(TagTrie *t) {
	for(int i=0; i < ALPH_SIZE; i++) {
		if(t->children[i])
			return false;
	}
	return true;
}

vector<int> TagTrie::search(string tag) {

  TagTrie *aux = this;
  vector<int> v;
  char c;

  for(int i=0; i < tag.length(); i++) {

    c = tag[i];
    int index = trieIndex(c);

    if (!aux->children[index]) {
      // n existe a tag, retorna NULL
      return v;
    } else {
      // existe, anda proximo
      aux = aux->children[index];
    }
  }

  // varreu toda palavra
  // pode ser nodo nulo (n encontrou)
  // se nodo n é nulo, ver se é final
  // se for final, encontrou retorna true
  if (aux == NULL || !aux->final || aux->movies.empty())
    return v;
  return aux->movies;

}

void collectTags(TagTrie *root, vector<int> *ids) {
	
	TagTrie *aux = root;
	
	// base da recursao
	if(aux->final)
		ids->insert(ids->end(), aux->movies.begin(), aux->movies.end());
	
	//passo
	for(int i=0; i<ALPH_SIZE; i++) {
		if(aux->children[i])
			collectTags(aux->children[i], ids);
	}
	
}

vector<int> TagTrie::prefixSearch(string arg) {
	
	TagTrie *aux = this;
	vector<int> v;
	char c;
	
	for(int i=0; i < arg.length(); i++) {
		c = arg[i];
		int index = trieIndex(c);
		
		if (!aux->children[index]) {
			// n existe, retorna false
			return v;
		}
		
		if (aux->children[index]) {
			// existe, anda proximo
			aux = aux->children[index];
		}
	}
	
	// parou de percorrer
	// nesse ponto, aux é a 'raiz' da busca
	collectTags(aux, &v);
	
	return v;
}


void populateTagTrie(TagTrie *t_trie, vector<string> tags, vector<int> ids) {
	for (int i = 0; i < tags.size(); ++i) {
		t_trie->insert(tags[i], ids[i]);
	}
}

