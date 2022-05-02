#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "aads.h"
#include <stdlib.h>

const int INF = 1000000;

struct adjacency_matrix{
    br3nder::List<std::string>* cities;
    int** matrix;

    friend std::ostream& operator<<(std::ostream& out, adjacency_matrix& m){
        if(m.cities){
            out << "cities: " << *m.cities << std::endl << "matrix:\n";
            for(int i = 0; i < 7; i++){
                for(int j = 0; j < 7; j++) {
                    if (m.matrix[i][j] == INF)
                        out << "inf ";
                    else
                        out << m.matrix[i][j] << " ";
                }
                out << std::endl;
            }
        }
        else
            out << "no cities!";
    }

    adjacency_matrix(): cities(nullptr), matrix(nullptr) {};
};

std::string read(std::ifstream &file) {
    std::string s = "", str;
    if (file.good()) {
        char symbol;
        while (!file.eof()) {
            std::getline(file, s);
            str += s + '\n';
        }
    }
    return str;
}

br3nder::List<std::string> get_cities(std::string &s) {
    br3nder::List<std::string> cities;
    std::string city = "";
    for (int i = 0; i < s.length(); i++) {
        if(city != "" && s[i] == ';' && !cities.find(&city)){
            cities.push_back(city);
            city = "";
        }
        else if(cities.find(&city))
            city = "";
        else if((s[i] < '0' || s[i] > '9') && s[i] != '\n' && s[i] != ';')
            city += s[i];
    }
    return cities;
}

int road_value_converter(std::string s){
    if(s == "N/A")
        return INF;
    else
        return std::stoi(s);
}

int** get_road_value(std::string &s, adjacency_matrix &adj_matrix){
    std::string city1 = "", city2 = "", road1 = "", road2 = "";
    int delimiter_count = 0;

    int** matrix = new int*[adj_matrix.cities->size()];
    for(int i = 0; i < adj_matrix.cities->size(); i++)
        matrix[i] = new int[adj_matrix.cities->size()];

    for(int i = 0; i < adj_matrix.cities->size(); i++) {
        for (int j = 0; j < adj_matrix.cities->size(); j++)
            matrix[i][j] = INF;
    }

    for(int i = 0; i < s.length(); i++){
        if(s[i] == ';'){
            delimiter_count++;
            continue;
        }
        if(s[i] == '\n'){
            matrix[adj_matrix.cities->get_index(city1)][adj_matrix.cities->get_index(city2)] = road_value_converter(road1);
            matrix[adj_matrix.cities->get_index(city2)][adj_matrix.cities->get_index(city1)] = road_value_converter(road2);
            city1 = city2 = road1 = road2 = "";
            delimiter_count++;
            continue;
        }
        if (delimiter_count % 4 == 0)
            city1 += s[i];
        else if (delimiter_count % 4 == 1)
            city2 += s[i];
        else if (delimiter_count % 4 == 2)
            road1 += s[i];
        else if (delimiter_count % 4 == 3 && s[i] != '\n')
            road2 += s[i];

    }
    return matrix;
}

void make_adjacency_matrix(std::ifstream& file, adjacency_matrix& adj_matrix){
    std::string s = read(file);
    br3nder::List<std::string> cities = get_cities(s);
    int** matrix = new int*[cities.size()];
    for(int i = 0; i < cities.size(); i++)
        matrix[i] = new int[cities.size()];

    adj_matrix.cities = &cities;
    adj_matrix.matrix = get_road_value(s, adj_matrix);

}

void ford_focus(adjacency_matrix& adj_matrix){
    int from, to, weight;
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            if(i == j) continue;
            for(int k = 0; k < 7; k++){
                if(j==k) continue;
                if(adj_matrix.matrix[i][j] > adj_matrix.matrix[i][k] + adj_matrix.matrix[k][j])
                    adj_matrix.matrix[i][j] = adj_matrix.matrix[i][k] + adj_matrix.matrix[k][j];
            }
        }
    }

    for(int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++){
            if(adj_matrix.matrix[i][j] == INF)
                std::cout << "inf ";
            else
                std::cout << adj_matrix.matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

}

int get_min_path_value(adjacency_matrix* adj_matrix, std::string from, std::string to) {
    return adj_matrix->matrix[adj_matrix->cities->get_index(from)][adj_matrix->cities->get_index(to)];
}