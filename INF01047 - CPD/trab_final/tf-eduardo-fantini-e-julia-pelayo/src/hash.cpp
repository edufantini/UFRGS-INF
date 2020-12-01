#include "hash.h"

// ----------- Movie --------------
int movieHashing(int id){
  int M = MOVIE_HASH_SIZE;
  return id%M;
}

MovieHash::MovieHash(){
    free =  true;
    next = NULL;
    n_ratings = 0;
    avg_ratings = 0;
}

void MovieHash::insert(int i, string t, vector<string> g){
  if(free){
    id = i;
    title = t;
    genres = g;

    free = false;
  }
  else{
    MovieHash *c = this;
    while(c->next != NULL)
      c = c->next;
    c->next = new MovieHash();
    c = c->next;
    c->id = i;
    c->title = t;
    c->genres = g;
    c->free = false;
  }
}

void MovieHash::update_ratings(int i, float r){
  MovieHash *m = this;
  if (m->free)
    return;
  while (m->id != i) {
    if(m->next == NULL) return;
    m = m->next;
  }
  m->n_ratings++;
  if(m->avg_ratings == -1)
    m->avg_ratings = r;
  else
    m->avg_ratings = (m->avg_ratings + r)/2;
}

// ponteiro para a instancia do usuario, se nao existe, NULL
MovieHash* search(int i, MovieHash t[]){
  int idx = movieHashing(i);
  if (t[idx].free)
    return NULL;
  MovieHash *c = &t[idx];
  while(c->id != i){
    c = c->next;
    if (c == NULL)  return NULL;
  }
  return c;
}

vector<MovieHash*> search(vector<int> is, MovieHash t[]){
  vector<MovieHash*> ms;
  for(vector<int>::iterator it=is.begin(); it!=is.end(); it++){
    MovieHash* m = search(*it, t);
    if(m != NULL)
      ms.push_back(m);
  }
  return ms;
}


void populateMovieHash(MovieHash m_hash[], vector<string> movies, vector<int> ids, vector<vector<string>> genres) {
	for (int i = 0; i < movies.size(); ++i) {
		m_hash[movieHashing(ids[i])].insert(ids[i],movies[i],genres[i]);
	}
}

// --------------- User ---------------

UserHash::UserHash(){
    free = true;
    next = NULL;
	movies.clear();
	ratings.clear();
}

int userHashing(int id){
  return id%USER_HASH_SIZE;
}

void UserHash::insert(int i, int m, float r){
  if(ratings.empty() && movies.empty()){
    id = i;
    movies.push_back(m);
    ratings.push_back(r);
    free = false;
  }
  else{
    UserHash *c = this;
	while (c->id != i){
		if(c->next == NULL){
			c->next = new UserHash();
			c->next->id = i; 
			c->next->free = false;
		}
		c = c->next;
	}
    c->movies.push_back(m);
    c->ratings.push_back(r);
  }
}

// ponteiro para a instancia do usuario, se nao existe, NULL
UserHash* search(int i, UserHash t[]){
  int idx = userHashing(i);
  if (t[idx].free)
    return NULL;
  UserHash *c = &t[idx];
  while(c->id != i){
    c = c->next;
    if (c == NULL)  return NULL;
  }
  return c;
}

void populateUserHash(UserHash u_hash[], MovieHash m_hash[], vector<float> ratings, vector<int> m_ids, vector<int> u_ids) {
	for (int i = 0; i < ratings.size(); ++i) {
		u_hash[userHashing(u_ids[i])].insert(u_ids[i],m_ids[i],ratings[i]);
		m_hash[movieHashing(m_ids[i])].update_ratings(m_ids[i],ratings[i]);
	}
}
