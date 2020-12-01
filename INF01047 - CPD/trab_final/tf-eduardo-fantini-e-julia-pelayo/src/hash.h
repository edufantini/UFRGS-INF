#include <vector>
#include <algorithm>
#include <string>

#define USER_HASH_SIZE   5471  // primo mais proximo de 22 278/5
#define MOVIE_HASH_SIZE  33238 // primo mais proximo de 166 191/5

#define HASH_DEFINED

using namespace std;

// Movie
class MovieHash{
    public:
        MovieHash();
        bool free;
        MovieHash *next;
        void insert(int id, string title, vector<string> genres);
        void update_ratings(int id, float avg);

        int id;

        string title;
        vector<string> genres;
        int n_ratings;
        float avg_ratings;
};


int movieHashing(int id);

MovieHash* search(int i, MovieHash t[]);

vector<MovieHash*> search(vector<int> is, MovieHash t[]);

void populateMovieHash(MovieHash m_hash[], vector<string> movies, vector<int> ids, vector<vector<string>> genres);

// User
class UserHash{
    public:
        UserHash();
        bool free;
        UserHash *next;
        void insert(int i, int m, float r);
        UserHash* search(int i);

        int id;

        vector<int> movies;
        vector<float>  ratings;
};

int userHashing(int id);

UserHash* search(int i, UserHash t[]);

void populateUserHash(UserHash u_hash[], MovieHash m_hash[], vector<float> ratings, vector<int> m_ids, vector<int> u_ids);