#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

#include "quick-sort.h"
#ifndef HASH_DEFINED
  #include "hash.h"
#endif
#include "trie.h"


// -------------------------------------------
//      bibliotecas externas utilizadas
// -------------------------------------------
// ler arquivos
#include "csv-parser-master/parser.hpp"
// animação de carregamento
#include "indicators.hpp"
// cores no terminal
#include "termcolor.hpp"
// construção de tabelas
#include "tabulate.hpp"

using namespace std;

void intro() {
	system("clear");
	cout << termcolor::cyan << termcolor::bold
	     << R"(
 $$\      $$\                  $$\                $$\
 $$$\    $$$ |                 \__|               $$ |
 $$$$\  $$$$ |$$$$$$\$$\    $$\$$\ $$$$$$\        $$ |     $$$$$$\ $$$$$$$\  $$$$$$$\
 $$\$$\$$ $$ $$  __$$\$$\  $$  $$ $$  __$$\       $$ |    $$  __$$\$$  __$$\$$  _____|
 $$ \$$$  $$ $$ /  $$ \$$\$$  /$$ $$$$$$$$ |      $$ |    $$$$$$$$ $$ |  $$ \$$$$$$\
 $$ |\$  /$$ $$ |  $$ |\$$$  / $$ $$   ____|      $$ |    $$   ____$$ |  $$ |\____$$\
 $$ | \_/ $$ \$$$$$$  | \$  /  $$ \$$$$$$$\       $$$$$$$$\$$$$$$$\$$ |  $$ $$$$$$$  |
 \__|     \__|\______/   \_/   \__|\_______|      \________\_______\__|  \__\_______/
)" << endl;
	
	cout << "\t\tTrabalho por " << termcolor::white << termcolor::bold
	     << "Eduardo Fantini" << termcolor::cyan << " & "
	     << termcolor::white << termcolor::bold << "Júlia Pelayo Rodrigues\n\n";
	
}

// -------------------------------------------
//          auxiliares
// -------------------------------------------

bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

string floatToStr(float f, int prec) {
	stringstream ss;
	ss.precision(prec);
	ss << f;
	return ss.str();
}

// -------------------------------------------
//          buscas
// -------------------------------------------

void movieSearch(MovieTrie *m_trie, MovieHash m_hash[], string arg) {

// -------------------------------------------
//      inicia timer, busca e ordena
// -------------------------------------------
	const clock_t begin_time = clock();
	vector<int> ids = m_trie->prefixSearch(arg);
	quicksort_hoare(ids,0,ids.size()-1);
	if(ids.size() == 0) {
		cout << termcolor::red << termcolor::bold
			 << "Oops, nenhum filme foi encontrado." << endl;
		return;
	}
	float t = float( clock () - begin_time ) /  CLOCKS_PER_SEC;
	
// -------------------------------------------
//      cria e configura a tabela de resultados
// -------------------------------------------
	
	int size = ids.size();
	tabulate::Table movies;
	movies.add_row({"ID", "Filme", "Ano", "Categorias", "Nota", "Total de notas"});
	for(int i=0; i<size; i++) {
    MovieHash *m = search(ids[i],m_hash);
    string genres = m->genres[0];
    for(int g=1; g<m->genres.size(); g++) {
    	genres += "\n" + m->genres[g];
    }
	
	
    if(m!=NULL){
      size_t sep = m->title.find_last_of('(');
      string title = m->title.substr(0,sep-1);
      string year  = m->title.substr(sep + 1, m->title.length());
      year.pop_back();
      movies.add_row({to_string(ids[i]), title, year, genres, floatToStr(m->avg_ratings, 3), to_string(m->n_ratings)});
    }
    else{
		  movies.add_row({to_string(ids[i]), "ops", "ops"});
    }
	}
	
	movies.column(1).format().width(25);
	movies.column(3).format().width(15);
	movies.column(0).format().
			font_color(tabulate::Color::cyan)
			.font_align(tabulate::FontAlign::center)
			.font_style({tabulate::FontStyle::bold});
	
//  reprinta o cabeçalho para facilitar leitura
//      em tabelas grandes
	if(size > 10) {
		movies.add_row({"ID", "Filme", "Ano", "Categorias", "Nota", "Total de notas"});
		for (size_t i = 0; i < 6; ++i) {
			movies[size+1][i].format()
					.font_color(tabulate::Color::cyan)
					.font_align(tabulate::FontAlign::center)
					.font_style({tabulate::FontStyle::bold});
		}
	}
	
	// formatacao da tabela
	for (size_t i = 0; i < 6; ++i) {
		movies[0][i].format()
				.font_color(tabulate::Color::cyan)
				.font_align(tabulate::FontAlign::center)
				.font_style({tabulate::FontStyle::bold});
		movies.column(i).format()
				.font_align(tabulate::FontAlign::center);
	}
	
	cout << "\n" << movies << "\n"
		<< "Resultado da busca por "
		<< termcolor::bold << termcolor::cyan << arg
		<< termcolor::reset << " ("
		<< termcolor::bold << termcolor::cyan << size
		<< termcolor::reset << " correspondências em "
		<< termcolor::bold << termcolor::cyan << floatToStr(t, 3)
		<< termcolor::reset << "s)\n";
	
}

void userSearch(MovieHash m_hash[], UserHash u_hash[], int id) {
	
	const clock_t begin_time = clock();
	
	UserHash *u = search(id, u_hash);
	
	if(!u) {
		cout << termcolor::red << termcolor::bold
		     << "Oops, nenhum usuário com ID "
		     << termcolor:: yellow << "#" << id << termcolor::red
		     << " foi encontrado." << endl;
		return;
	}
	
	vector<int> movies_id = u->movies;
	vector<float> ratings = u->ratings;
	vector<string> movies;
	vector<float> avg_ratings;
	vector<int> count;
	
	for(int i=0; i<movies_id.size(); i++) {
		MovieHash *m = search(movies_id[i], m_hash);
		movies.push_back(m->title);
		avg_ratings.push_back(m->avg_ratings);
		count.push_back(m->n_ratings);
	}
	
	float t = float( clock () - begin_time ) /  CLOCKS_PER_SEC;
	
	int size = movies_id.size();
	
	tabulate::Table table;
	
	table.add_row({"Nota dada pelo user", "Nota geral", "Total de notas", "Filme", "Ano"});
	for(int i=0; i<size; i++) {
		size_t sep = movies[i].find_last_of('(');
		string title = movies[i].substr(0,sep-1);
		string year  = movies[i].substr(sep + 1, movies[i].length());
		year.pop_back();
		table.add_row({floatToStr(ratings[i], 3), floatToStr(avg_ratings[i], 3), to_string(count[i]), title, year});
	}
	
	table.column(3).format().width(25);
	table.column(0).format().width(13);
	table.column(0).format()
			.font_color(tabulate::Color::cyan)
			.font_align(tabulate::FontAlign::center)
			.font_style({tabulate::FontStyle::bold});
	
	if(size > 10) {
		table.add_row({"Nota dada pelo user", "Nota geral", "Total de notas", "Filme", "Ano"});
		for (size_t i = 0; i < 5; ++i) {
			table[size+1][i].format()
					.font_color(tabulate::Color::cyan)
					.font_align(tabulate::FontAlign::center)
					.font_style({tabulate::FontStyle::bold});
		}
	}
	
	for (size_t i = 0; i < 5; ++i) {
		table[0][i].format()
				.font_color(tabulate::Color::cyan)
				.font_align(tabulate::FontAlign::center)
				.font_style({tabulate::FontStyle::bold});
		table.column(i).format()
				.font_align(tabulate::FontAlign::center);
	}
	
	cout << "\n" << table << "\n"
	     << "Resultado da busca por usuário "
	     << termcolor::bold << termcolor::cyan << "#" << id
	     << termcolor::reset << " ("
	     << termcolor::bold << termcolor::cyan << size
	     << termcolor::reset << " correspondências em "
	     << termcolor::bold << termcolor::cyan << floatToStr(t, 3)
	     << termcolor::reset << "s)\n";
	
}

void tagSearch(TagTrie *t_trie, MovieHash m_hash[], vector<string> tags) {
	
	const clock_t begin_time = clock();
	vector<int> ids;
	
	for(int i=0; i<tags.size(); i++) {
		if(i==0) {
			ids = t_trie->prefixSearch(tags[i]);
			quicksort_hoare(ids, 0, ids.size()-1);
		}else{
			vector<int> aux = t_trie->prefixSearch(tags[i]);
			quicksort_hoare(aux, 0, aux.size()-1);
			
			vector<int> v(ids.size() + aux.size());
			vector<int>::iterator it, st;
			
			it = set_intersection(ids.begin(),
			                      ids.end(),
			                      aux.begin(),
			                      aux.end(),
			                      v.begin());
			ids = v;
			quicksort_hoare(ids, 0, ids.size()-1);
			
		}
	}
	
	// remove duplicadas
	ids.erase(unique(ids.begin(),ids.end()),ids.end());
	// remove 0 se houver
	ids.erase(remove(ids.begin(), ids.end(), 0), ids.end());
	
	int size = ids.size();
	if(size == 0) {
		cout << termcolor::red << termcolor::bold
		     << "Oops, nenhum filme foi encontrado." << endl;
		return;
	}
	float t = float( clock () - begin_time ) /  CLOCKS_PER_SEC;
	
	
	tabulate::Table tags_table;
	
	tags_table.add_row({"ID", "Filme", "Ano", "Categorias", "Nota", "Total de notas"});
	for(int i=0; i<size; i++) {
		MovieHash *m = search(ids[i], m_hash);
		
		if(m!=NULL){
			string genres = m->genres[0];
			for(int g=1; g<m->genres.size(); g++) {
				genres += "\n" + m->genres[g];
			}
			size_t sep = m->title.find_last_of('(');
			string title = m->title.substr(0,sep-1);
			string year  = m->title.substr(sep + 1, m->title.length());
			year.pop_back();
			tags_table.add_row({to_string(ids[i]), title, year, genres, floatToStr(m->avg_ratings, 3), to_string(m->n_ratings)});
		}
		else{
			tags_table.add_row({to_string(ids[i]), "ops", "ops"});
		}
	}
	
	tags_table.column(1).format().width(25);
	tags_table.column(2).format().width(8);
	tags_table.column(3).format().width(15);
	tags_table.column(0).format().
					font_color(tabulate::Color::cyan)
			.font_align(tabulate::FontAlign::center)
			.font_style({tabulate::FontStyle::bold});
	
	
	if(size > 10) {
		tags_table.add_row({"ID", "Filme", "Ano", "Categorias", "Nota", "Total de notas"});
		for (size_t i = 0; i < 6; ++i) {
			tags_table[size+1][i].format()
					.font_color(tabulate::Color::cyan)
					.font_align(tabulate::FontAlign::center)
					.font_style({tabulate::FontStyle::bold});
		}
	}
	
	for (size_t i = 0; i < 6; ++i) {
		tags_table[0][i].format()
				.font_color(tabulate::Color::cyan)
				.font_align(tabulate::FontAlign::center)
				.font_style({tabulate::FontStyle::bold});
		tags_table.column(i).format()
				.font_align(tabulate::FontAlign::center);
	}
	
	string tags_conc = tags[0];
	for(int i=1; i < tags.size(); i++)
		tags_conc += ", " + tags[i];
	
	cout << "\n" << tags_table << "\n"
	     << "Resultado da busca por "
	     << termcolor::bold << termcolor::cyan << tags_conc
	     << termcolor::reset << " ("
	     << termcolor::bold << termcolor::cyan << size
	     << termcolor::reset << " correspondências em "
	     << termcolor::bold << termcolor::cyan << floatToStr(t, 3)
	     << termcolor::reset << "s)\n";
	
}


void topGenreSearch(GenreTrie *g_trie, MovieHash m_hash[], string arg, int n) {
	
	const clock_t begin_time = clock();
	vector<int> ids = g_trie->search(arg);
	if(ids.size() == 0) {
		cout << termcolor::red << termcolor::bold
		     << "Oops, nenhum filme foi encontrado." << endl;
		return;
	}

	vector<MovieHash*> ms = search(ids, m_hash);
	quicksort_hoare(ms, 0, ms.size()-1);
	
	float t = float( clock () - begin_time ) /  CLOCKS_PER_SEC;
	
	tabulate::Table movies;
	
	movies.add_row({"Nota", "Total de notas", "Filme", "Ano", "Categorias", "ID"});
	
	int size = ms.size();
	int validos = 0;

	int i=size-1;
	while (validos < n && i > 0){
		MovieHash *m = ms[i];
		
		string genres = m->genres[0];
		for(int g=1; g<m->genres.size(); g++) {
			genres += "\n" + m->genres[g];
		}
		
		
		if(m!=NULL) {
			
			if (m->n_ratings >= 1000) {
				
				validos++;
				
				size_t sep = m->title.find_last_of('(');
				string title = m->title.substr(0, sep - 1);
				string year = m->title.substr(sep + 1, m->title.length());
				year.pop_back();
				movies.add_row({floatToStr(m->avg_ratings, 3), to_string(m->n_ratings), title, year, genres,
				                to_string(ids[i])});
			}
		}
		else{
			movies.add_row({to_string(ids[i]), "ops", "ops"});
		}
		i--;
	}
	
	movies.column(2).format().width(25);
	movies.column(4).format().width(15);
	movies.column(0).format().
					font_color(tabulate::Color::cyan)
			.font_align(tabulate::FontAlign::center)
			.font_style({tabulate::FontStyle::bold});
	
	if(validos > 10) {
		movies.add_row({"Nota", "Total de notas", "Filme", "Ano", "Categorias", "ID"});
		for (size_t i = 0; i < 6; ++i) {
			movies[validos+1][i].format()
					.font_color(tabulate::Color::cyan)
					.font_align(tabulate::FontAlign::center)
					.font_style({tabulate::FontStyle::bold});
		}
	}
	
	for (size_t i = 0; i < 6; ++i) {
		movies[0][i].format()
				.font_color(tabulate::Color::cyan)
				.font_align(tabulate::FontAlign::center)
				.font_style({tabulate::FontStyle::bold});
		movies.column(i).format()
				.font_align(tabulate::FontAlign::center);
	}
	
	cout << "\n" << movies << "\n"
	     << "Resultado da busca por "
	     << termcolor::bold << termcolor::cyan << arg
	     << termcolor::reset << " ("
	     << termcolor::bold << termcolor::cyan << size
	     << termcolor::reset << " correspondências em "
	     << termcolor::bold << termcolor::cyan << floatToStr(t, 3)
	     << termcolor::reset << "s)\n";
	
}

// -------------------------------------------
//          parsing dos arquivos
// -------------------------------------------

void parseMovie(MovieTrie *m_trie, GenreTrie *g_trie, MovieHash m_hash[]) {
  ifstream f("movie_clean.csv");
  aria::csv::CsvParser parser(f);
	
  vector<string> movies;
  vector<vector<string>> genres;
  vector<int> ids;
  
//  cout << "\n>> Recebendo dados do arquivo de filmes..." << endl;
	
	int line = 0;
	
	for (auto& row : parser) {
		if(line) {
			int id = stoi(row[0]);
			string name = row[1];
			vector<string> g;
			// separa a string com as tags em um vetor
			size_t first = 0;
			size_t sep = row[2].find('|',0);
			while(sep!=string::npos){
				g.push_back(row[2].substr(first,sep-first));
				first = sep+1;
				sep = row[2].find('|',first);
			}
			g.push_back(row[2].substr(first,row[2].length()));
			
			movies.push_back(name);
			ids.push_back(id);
			genres.push_back(g);
		}
		line++;
	}
	f.close();
  
  populateMovieTrie(m_trie, movies, ids);
  populateGenreTrie(g_trie, genres, ids);
  populateMovieHash(m_hash, movies, ids, genres);
  
}

void parseTag(TagTrie *t_trie){
	ifstream f("tag_clean.csv");
	aria::csv::CsvParser parser(f);
	
	vector<string> tags;
	vector<int> movie_ids;
	vector<int> user_ids;
	
//	cout << "\n>> Recebendo dados do arquivo de tags..." << endl;
	
	int line = 0;
	// string name;
	
	for (auto& row : parser) {
		if(line) {
			int u_id = stoi(row[0]);
			int m_id = stoi(row[1]);
			string tag = row[2];
			
			tags.push_back(tag);
			movie_ids.push_back(m_id);
			user_ids.push_back(u_id);
		}
		line++;
	}
	f.close();
	
	populateTagTrie(t_trie, tags, movie_ids);
}

void parseRatings(UserHash u_hash[], MovieHash m_hash[]){
    ifstream f("rating.csv");
	aria::csv::CsvParser parser(f);
	
	vector<float> ratings;
	vector<int> user_ids;
	vector<int> movie_ids;
//
//	cout << "\n>> Recebendo dados do arquivo de ratings..." << endl;
	
	int line = 0;
	
	for (auto& row : parser) {
		if(line) {
			int u_id = stoi(row[0]);
			int m_id = stoi(row[1]);
			float ra = stof(row[2]);
			
			ratings.push_back(ra);
			movie_ids.push_back(m_id);
			user_ids.push_back(u_id);
    }	
		line++;
	}
  f.close();
	
	populateUserHash(u_hash, m_hash, ratings, movie_ids, user_ids);

}

// -------------------------------------------
//          funcao driver dos parsings
// -------------------------------------------

void parseFiles(MovieTrie *m_trie, GenreTrie *g_trie, MovieHash m_hash[], TagTrie *t_trie, UserHash u_hash[]) {
	
	using namespace indicators;
	
	// Hide cursor
	show_console_cursor(false);
	
	const clock_t begin_time = clock();
	
	cout << termcolor::reverse;
	
	ProgressBar bar{
			option::BarWidth{30},
			option::Start{"["},
			option::Fill{"■"},
			option::Lead{"■"},
			option::Remainder{"-"},
			option::End{"]"},
			option::PostfixText{"Carregando arquivo de filmes [0/3]"},
			option::ForegroundColor{Color::cyan},
			option::FontStyles{std::vector<FontStyle>{FontStyle::bold}}
	};
	
	bar.set_progress(0);
	parseMovie(m_trie, g_trie, m_hash);
	float t = float( clock () - begin_time ) /  CLOCKS_PER_SEC;
	bar.set_option(option::PostfixText{"Carregando arquivo de tags [1/3] ("
		+ floatToStr(t, 3) + "s)"});
	bar.set_progress(100/3);
	parseTag(t_trie);
	t = float( clock () - begin_time ) /  CLOCKS_PER_SEC;
	bar.set_option(option::PostfixText{"Carregando arquivo de ratings [2/3] ("
		+ floatToStr(t, 3) + "s)"});
	bar.set_progress(200/3);
	parseRatings(u_hash, m_hash);
	
	t = float( clock () - begin_time ) /  CLOCKS_PER_SEC;
	bar.set_option(option::PostfixText{"Todos arquivos carregados em "
		+ floatToStr(t, 3) + "s."});
	bar.set_progress(100);
	// Show cursor
	show_console_cursor(true);
}

// -------------------------------------------
//          funcao driver do programa
// -------------------------------------------

void ops(MovieTrie *m_trie, GenreTrie *g_trie, MovieHash m_hash[], TagTrie *t_trie, UserHash u_hash[]) {
	
	bool exit = false;
	
	// loop de execução
	while(!exit) {
		
		cout << termcolor::white << termcolor::bold
			 << "\n\n>> Modo de operações: "
		     <<  "(movie, user, topN, tags, "
		     << termcolor::yellow << "clear"
		     << termcolor::white << ","
		     << termcolor::red << " exit"
		     << termcolor::white << ")\n";
		
		cout << " ‣ "
			 << termcolor::blue << termcolor::bold;
		
		string line;
		getline(cin, line);
		stringstream ss(line);
		string word;
		int i=0;
		
		while (ss >> word) {
			
			if(word == "movie" && i==0) {
				string args = ss.str();
				args = args.substr(args.find_first_of(" \t")+1);
				if(ss.str() == "movie" || args.find_first_not_of(' ') == string::npos) {
					cout << termcolor::red << termcolor::bold
					     << "Oops, você precisa ser mais específico! Insira ao menos uma palavra para buscar." << endl;
					cout << "Por exemplo: " << termcolor::yellow << "movie shrek" << endl;
					break;
				}
				movieSearch(m_trie, m_hash, args);
			} else
			
			if(word == "user" && i==0) {
				string args = ss.str();
				args = args.substr(args.find_first_of(" \t")+1);
				if(ss.str() == "user" || args.find_first_not_of(' ') == string::npos) {
					cout << termcolor::red << termcolor::bold
					     << "Oops, você precisa ser mais específico! Insira o ID do usuário para buscar." << endl;
					cout << "Por exemplo: " << termcolor::yellow << "user 1312" << endl;
					break;
				}
				if(!is_number(args)) {
					cout << termcolor::red << termcolor::bold
					     << "Oops, o ID a ser buscado precisa ser um número, e APENAS UM número." << endl;
					cout << "Por exemplo: " << termcolor::yellow << "user 1312" << endl;
					break;
				}
				userSearch(m_hash, u_hash, stoi(args));
			} else
			
			if(word == "tags" && i==0) {
				string args = ss.str();
				args = args.substr(args.find_first_of(" \t")+1);
				if(ss.str() == "tags" || args.find_first_not_of(' ') == string::npos) {
					cout << termcolor::red << termcolor::bold
					     << "Oops, você precisa ser mais específico! Insira ao menos uma palavra para buscar." << endl;
					cout << "Por exemplo: " << termcolor::yellow << "tags 'drugs'" << endl;
					break;
				}
				
				vector<string> tags;
				stringstream ss(args);
				string aux;
				bool first = false;
				while(getline(ss, aux, '\'')) {
					if(first) {
						tags.push_back(aux);
						first = false;
					}else{
						first = true;
					}
				}
				tagSearch(t_trie, m_hash, tags);
				
			} else
			
			if(word.find("top") != string::npos && i== 0) {
				
				string args = ss.str();
				string n = args.substr(args.find_first_of("p")+1);
				n = n.substr(0, n.find_first_of(" "));
				args = args.substr(args.find_first_of(" \t")+1);
				if(!is_number(n)) {
					cout << termcolor::red << termcolor::bold
					     << "Oops, você precisa ser mais específico! Insira um número para limitar a busca." << endl;
					cout << "Por exemplo: " << termcolor::yellow << "top10 'comedy'" << endl;
					break;
				}
				if(ss.str() == "tags" || args.find_first_not_of(' ') == string::npos) {
					cout << termcolor::red << termcolor::bold
					     << "Oops, você precisa ser mais específico! Insira uma categoria de filme para buscar." << endl;
					cout << "Por exemplo: " << termcolor::yellow << "top10 'comedy'" << endl;
					break;
				}
				
				string genre;
				bool first = false;
				while(getline(ss, args, '\'')) {
					if(first) {
						genre = args;
						first = false;
					}else{
						first = true;
					}
				}
				
				topGenreSearch(g_trie, m_hash, genre, stoi(n));
				
//				cout << genre << endl;
				
			} else
			
			if(word == "clear" && i==0) {
				intro();
			} else
			
			if(word == "exit" && i==0) {
				exit = true;
				cout << termcolor::white << termcolor::bold
					 << "\nAgradeçemos a dedicação ao ERE,  professor e monitores! "
					 << "\nAchamos que essa cadeira funcionou muito bem!" << endl;
				break;
			} else if(i==0){
				cout << termcolor::red << termcolor::bold
					 << "Comando inválido. Tente novamente." << endl;
			}
			
			i++;
		}
	}
}

int main() {
	
	intro();
	
    MovieTrie m_trie;
    GenreTrie g_trie;
    TagTrie t_trie;
    MovieHash m_hash[MOVIE_HASH_SIZE];
    UserHash  u_hash[USER_HASH_SIZE];
    
    parseFiles(&m_trie, &g_trie, m_hash, &t_trie, u_hash);
    ops(&m_trie, &g_trie, m_hash, &t_trie, u_hash);
}
