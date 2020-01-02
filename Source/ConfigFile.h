#ifndef CFG_FILE__
#define CFG_FILE__


#include <map>
#include <string>


using namespace std;


class ConfigFile
{
public:

    ConfigFile (const string &filePath = "./Config/Game.cfg");

    const string &operator[] (const string &key);

    const string &operator() (const string &key);

private:

    map<string, string> configContent;

    string GetModule(const string &line);

    void AddLine(const string &line, const string &module);

};


#endif // !CFG_FILE__
