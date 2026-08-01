#include <fstream>
#include <filesystem>
#include <iostream>
#include "env.hpp"
#include "config.hpp"

namespace fs = std::filesystem;

Env* Env::instance = nullptr;

Env* Env::getInstance(void){
    return instance;
}

Env::Env(const std::string envFile) {
    this->instance = this;
    this->envDict = new std::map<std::string,EnvFormat*>;
    fs::path envPath = fs::path(ROOT_DIRECTORY) / envFile;

    std::ifstream f(envPath);
    std::string varName, varVal;
    if(f.is_open())
    {
        while(f) {
            int next_char = f.peek();

            if (next_char == EOF) break;

            if (next_char == '#' || next_char == '\n' || next_char == '\r') {
                std::string dummy;
                std::getline(f, dummy); 
                continue;
            }

            getline(f,varName,'=');
            getline(f,varVal);

            // strip trimmed variable spaces
            varName.erase(0, varName.find_first_not_of(" \t"));
            varName.erase(varName.find_last_not_of(" \t") + 1);

            // strip trimmed value spaces
            varVal.erase(0, varVal.find_first_not_of(" \t"));
            varVal.erase(varVal.find_last_not_of(" \t") + 1);

            EnvFormat *fmt = new EnvFormat;
            try {
                if(std::stoll(varVal) != std::stold(varVal)) {
                    fmt->tag = EnvTag::FLOAT;
                    fmt->content = std::stod(varVal);
                } else {
                    fmt->tag = EnvTag::INT;
                    fmt->content = std::stoi(varVal);
                }
            } catch (std::exception& e) { // Force exception if the data is a string
                fmt->tag = EnvTag::STRING;
                if(varVal.size()>=2 && 
                 ((varVal.front() == '"' && varVal.back() == '"') ||
                  (varVal.front() == '\'' && varVal.back() == '\'')))
                {
                    varVal = varVal.substr(1,varVal.size() -2);
                }
                fmt->content = varVal;
            }

            if (!varName.empty())
                (*this->envDict)[varName] = fmt;
            else
                delete fmt;
        }
    }
    else
    {
        std::cerr << ".env file non ouvrable, l'objet sera vide." << std::endl;
    }
}

Env::~Env() {
    delete envDict;
}

void Env::get(const std::string&& variable, short& value, short&& default_val) {
    if(this->envDict->contains(variable) && (*this->envDict)[variable]->tag == EnvTag::INT) {
        value = std::get<long long>((*this->envDict)[variable]->content);
    } else {
        value = default_val;
    }
}

void Env::get(const std::string&& variable, int& value, int&& default_val) {
    if(this->envDict->contains(variable) && (*this->envDict)[variable]->tag == EnvTag::INT) {
        value = std::get<long long>((*this->envDict)[variable]->content);
    } else {
        value = default_val;
    }
}

void Env::get(const std::string&& variable, long& value, long&& default_val) {
    if(this->envDict->contains(variable) && (*this->envDict)[variable]->tag == EnvTag::INT) {
        value = std::get<long long>((*this->envDict)[variable]->content);
    } else {
        value = default_val;
    }
}

void Env::get(const std::string&& variable, long long& value, long long&& default_val) {
    if(this->envDict->contains(variable) && (*this->envDict)[variable]->tag == EnvTag::INT) {
        value = std::get<long long>((*this->envDict)[variable]->content);
    } else {
        value = default_val;
    }
}

void Env::get(const std::string&& variable, float& value, float&& default_val) {
    if(this->envDict->contains(variable) && (*this->envDict)[variable]->tag == EnvTag::FLOAT) {
        value = std::get<long double>((*this->envDict)[variable]->content);
    } else {
        value = default_val;
    }
}


void Env::get(const std::string&& variable, double& value, double&& default_val) {
    if(this->envDict->contains(variable) && (*this->envDict)[variable]->tag == EnvTag::FLOAT) {
        value = std::get<long double>((*this->envDict)[variable]->content);
    } else {
        value = default_val;
    }
}

void Env::get(const std::string&& variable, long double& value, long double&& default_val) {
    if(this->envDict->contains(variable) && (*this->envDict)[variable]->tag == EnvTag::FLOAT) {
        value = std::get<long double>((*this->envDict)[variable]->content);
    } else {
        value = default_val;
    }
}


void Env::get(const std::string&& variable, std::string& value, std::string&& default_val) {
    if(this->envDict->contains(variable) && (*this->envDict)[variable]->tag == EnvTag::STRING) {
        value = std::get<std::string>((*this->envDict)[variable]->content);
    } else {
        value = default_val;
    }
}

void Env::get(const std::string&& variable, const char *&value, std::string&& default_val) {
    if(this->envDict->contains(variable) && (*this->envDict)[variable]->tag == EnvTag::STRING) {
        value = std::get<std::string>((*this->envDict)[variable]->content).c_str();
    } else {
        value = default_val.c_str();
    }
}
