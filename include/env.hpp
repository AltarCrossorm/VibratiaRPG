#pragma once
#include <stdfloat>
#include <map>
#include <string>
#include <variant>

enum class EnvTag {STRING,INT,FLOAT};
using EnvValue = std::variant<long long, long double, std::string>;

struct EnvFormat {
    EnvTag tag;
    EnvValue content;
    EnvFormat()
    :tag(EnvTag::INT)
    {}
};

class Env
{
    std::map<std::string,EnvFormat*> *envDict = nullptr;
    static Env* instance;
public:
    Env(const Env&) = delete;
    Env(const Env&&) = delete;
    Env& operator=(const Env&) = delete;
    Env& operator=(const Env&&) = delete;

    Env(const std::string envFile);
    ~Env();

    static Env* getInstance(void);


    void get(const std::string&& variable, short&       value,        short&& default_val = 0  );
    void get(const std::string&& variable, int&         value,          int&& default_val = 0  );
    void get(const std::string&& variable, long&        value,         long&& default_val = 0  );
    void get(const std::string&& variable, long long&   value,    long long&& default_val = 0  );
    void get(const std::string&& variable, float&       value,        float&& default_val = 0.0);
    void get(const std::string&& variable, double&      value,       double&& default_val = 0.0);
    void get(const std::string&& variable, long double& value,  long double&& default_val = 0.0);
    void get(const std::string&& variable, std::string& value,  std::string&& default_val = "" );
    void get(const std::string&& variable, const char *&value,  std::string&& default_val = "" );
    
};
