#pragma once
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

vector<string> split(string str, char pattern) {

	int posInit = 0;
	int posFound = 0;
	string splitted;
	vector<string> results;

	while (posFound >= 0) {
		posFound = str.find(pattern, posInit);
		splitted = str.substr(posInit, posFound - posInit);
		posInit = posFound + 1;
		results.push_back(splitted);
	}

	return results;
}


class Video {
public:
	void setId(string id);
	string getId() {
		return id;
	}
	void setName(string a) {
		name = a;
	}
	string getName() {
		return name;
	}
	void setDuration(int a) {
		duration = a;
	}
	int getDuration() const {
		return duration;
	}
	void setGenre(string a) {
		genre = a;
	}
	string getGenre() const {
		return genre;
	}
	void setRate(int b) {
		rate = b;
	}
	int getRate() const {
		return rate;
	}

	friend ostream& operator<<(ostream& os, const Video& video)
	{
		os << video.name << "\t" << video.duration << "\t" << video.genre << "\t" << video.rate << endl;
		return os;
	}

private:
	string id;
	string name;
	int duration;
	string genre;
	int rate;
};
void Video::setId(string b) {
	id = b;
}

class Movie : public Video {
public:
	Movie() {
		setTitle("");
		setId("0");
		setName("");
		setDuration(0);
		setGenre("");
		setRate(0);
	}
	Movie(string title, string id, string name, int duration, string genre) {
		setTitle(title);
		setId(id);
		setName(name);
		setDuration(duration);
		setGenre(genre);
		setRate(0);
	}
	Movie(string title, string id, string name, int duration, string genre, int rate) {
		setTitle(title);
		setId(id);
		setName(name);
		setDuration(duration);
		setGenre(genre);
		setRate(rate);
	}
	void setTitle(string a) {
		title = a;
	}
	string getTitle() const {
		return title;
	}

	friend ostream& operator<<(ostream& os, const Movie& mov)
	{
		os << mov.getTitle() << "\t" << mov.getDuration() << "\t" << mov.getGenre() << "\t" << mov.getRate() << endl;
		return os;
	}
private:
	string title;
};

class Episode : public Video {
public:
	Episode() {
		setTitle("");
		setSeason(0);
		setId("0");
		setName("");
		setDuration(0);
		setGenre("");
		setNumOfEpisode(0);
		setRate(0);
	}
	Episode(string title, int season, string id, string name, int duration, string genre, int numOfEpisode) {
		setTitle(title);
		setSeason(season);
		setId(id);
		setName(name);
		setDuration(duration);
		setGenre(genre);
		setNumOfEpisode(numOfEpisode);
		setRate(0);
	}
	Episode(string title, int season, string id, string name, int duration, string genre, int numOfEpisode, int rate) {
		setTitle(title);
		setSeason(season);
		setId(id);
		setName(name);
		setDuration(duration);
		setGenre(genre);
		setNumOfEpisode(numOfEpisode);
		setRate(rate);
	}

	void setTitle(string a) {
		title = a;
	}
	string getTitle() const {
		return title;
	}
	void setSeason(int b) {
		season = b;
	}
	int getSeason() {
		return season;
	}
	void setNumOfEpisode(int b) {
		numOfEpisode = b;
	}
	int getNumOfEpisode() {
		return numOfEpisode;
	}

	friend ostream& operator<<(ostream& os, const Episode& ep)
	{
		os << ep.getTitle() << "\t" << ep.getDuration() << "\t" << ep.getGenre() << "\t" << ep.getRate() << endl;
		return os;
	}

private:
	string title;
	int season;
	int numOfEpisode;
};

class Series {
public:
	string name;
	vector<Episode> episodes;

	Series() {
		name = "";
	}
	Series(string a) {
		name = a;
	}
};

class Manager {
public:
	int option;
	vector<Video> dbVideos;
	vector<Movie> dbMovies;
	vector<Series> dbSeries;
	void option1() {
		string filename = "formatoArchivo.txt";
		ifstream file(filename.c_str());
		string line;
		vector<string> results;
		getline(file, line);
		getline(file, line);

		while (getline(file, line)) {
			//cout << line << endl;
			results = split(line, ',');

			/*for (int i = 0; i < results.size(); i++) {
				cout << results[i] << endl;
			}*/

			if (results[0] == "p") {
				dbVideos.push_back(Movie(results[2], results[1], results[2], stoi(results[3]), results[4]));
				dbMovies.push_back(Movie(results[2], results[1], results[2], stoi(results[3]), results[4]));
			}
			else if (results[0] == "c") {
				vector<string> splitArray = split(results[1], '-');
				//char *season;
				//season.append(splitArray.at(1).at(2));
				//strcat_s(season, &splitArray.at(1).at(1));
				//strcat_s(season, &splitArray.at(1).at(2));
				//string season = "" + splitArray.at(1).at(1) + splitArray.at(1).at(2);
				string seriesName = results[5];
				bool exists = false;
				Episode newEpisode = Episode(results[2], (int)splitArray.at(1).at(2), results[1], results[2], stoi(results[3]), results[4], stoi(results[6]));
				for (int i = 0; i < dbSeries.size(); i++) {
					if (seriesName == dbSeries.at(i).name) {
						exists = true;
						dbSeries.at(i).episodes.push_back(newEpisode);
					}
				}
				if (!exists) {
					Series serie = Series(seriesName);
					serie.episodes.push_back(newEpisode);
					dbSeries.push_back(serie);
				}
				dbVideos.push_back(newEpisode);
			}
		}

		file.close();

		/*while (!file.eof()) {
			file >> line;
			cout << line << endl;
		}*/

		/*
		while (getline(file, line))
		{
			stringstream stream(line);
			string valor;

			cout << "Contenido de la linea:\n";
			while (getline(stream, valor, ','))
			{
				cout << "valor leido: " << valor << '\n';
			}
			cout << "Fin de la linea\n";
		}*/


	}
	void option2() {
		cout << endl << "1. Filtrar videos por calificacion." << endl;
		cout << "2. Filtrar videos por genero." << endl;
		cout << "Opcion: ";
		cin >> option;

		if (option == 1) {
			cout << "Ingresa la calificacion a buscar (1-5): ";
			cin >> option;

			cout << endl << "Videos con " << option << " estrellas." << endl;
			for (int i = 0; i < dbVideos.size(); i++) {
				if (dbVideos.at(i).getRate() == option) {
					cout << dbVideos.at(i);
				}
			}
		}
		else if (option == 2) {
			cout << endl << "1. Drama." << endl;
			cout << "2. Accion." << endl;
			cout << "3. Misterio." << endl;
			cout << "Genero: ";
			cin >> option;
			string genreFilter = "";
			switch (option) {
			case 1:
				genreFilter = "drama";
				break;
			case 2:
				genreFilter = "accion";
				break;
			case 3:
				genreFilter = "misterio";
				break;
			}

			cout << endl << "Videos del genero -" << option << "- ." << endl;
			for (int i = 0; i < dbVideos.size(); i++) {
				if (dbVideos.at(i).getGenre() == genreFilter) {
					cout << dbVideos.at(i);
				}
			}
		}
	}
	void option3() {
		int rateFilter;
		cout << endl;
		for (int i = 0; i < dbSeries.size(); i++) {
			cout << i << ". " << dbSeries.at(i).name << endl;
		}
		cout << "Serie: ";
		cin >> option;

		//cin >> seriesName;
		cout << endl << "Ingresa la calificacion a buscar." << endl;
		cout << "Calificacion: ";
		cin >> rateFilter;

		cout << endl << "Episodios de " << dbSeries.at(option).name << " con calificacion de " << rateFilter << " estrellas." << endl;
		for (int j = 0; j < dbSeries.at(option).episodes.size(); j++) {
			if (rateFilter == dbSeries.at(option).episodes.at(j).getRate()) {
				cout << dbSeries.at(option).episodes.at(j);
			}
		}

	}
	void option4() {
		int rateFilter;
		cout << endl << "Ingresa la calificacion a buscar." << endl;
		cout << "Calificacion: ";
		cin >> rateFilter;

		cout << endl << "Peliculas con calificacion de " << rateFilter << " estrellas." << endl;
		for (int i = 0; i < dbMovies.size(); i++) {
			if (rateFilter == dbMovies.at(i).getRate()) {
				cout << dbMovies.at(i);
			}
		}
	}
	void option5() {
		string idFilter;
		int newRate;
		cout << endl << "Escribe el ID del video que quieras calificar." << endl;
		cout << "ID: ";
		cin >> idFilter;

		for (int i = 0; i < dbVideos.size(); i++) {
			if (idFilter == dbVideos.at(i).getId()) {
				cout << "Escribe la calificacion: ";
				cin >> newRate;
				dbVideos.at(i).setRate(newRate);
			}
		}


	}
};
