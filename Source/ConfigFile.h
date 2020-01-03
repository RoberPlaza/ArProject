#ifndef CFG_FILE__
#define CFG_FILE__


#include <map>
#include <string>


using namespace std;


class ConfigFile
{
public:

    ConfigFile (const string &filePath = "./Config/Game.cfg");

    ConfigFile (const ConfigFile &other);

    const string &operator[] (const string &key);

    const string &operator() (const string &key);

    void ToString ();

private:

    map<string, string> configContent;

    string GetModule(const string &line);

    void AddLine(const string &line, const string &module);


};


#endif // !CFG_FILE__
