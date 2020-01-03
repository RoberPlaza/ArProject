#ifndef CFG_FILE__
#define CFG_FILE__


#include <map>
#include <string>


using namespace std;


/**
 * @brief Simple interface to acces a configuration file.
 * 
 * This class reads the content of a file specified in the 
 * constructor and "dumps" the content to a map, so the users 
 * may access it with more ease.
 * 
 */
class ConfigFile
{
public:

    /**
     * @brief Construct a new Config File object
     * 
     * @param filePath Path of the file to read.
     */
    ConfigFile (const string &filePath = "./Config/Game.cfg");

    /**
     * @brief Construct a new Config File object
     * 
     * @param other base object to carry on construction.
     */
    ConfigFile (const ConfigFile &other);

    /**
     * @brief Access a given key.
     * 
     * @warning May throw exceptions if the key is invalid.
     * 
     * @param key String of the value to access.
     * @return const string& map value required.
     */
    const string &operator[] (const string &key);

    /**
     * @brief Access a given key.
     * 
     * @warning May throw exceptions if the key is invalid.
     * 
     * @param key String of the value to access.
     * @return const string& map value required.
     */
    const string &operator() (const string &key);

#ifdef DEBUG
    void ToString ();
#endif // DEBUG

private:

    /**
     * @brief Content of the file dumped in a map of strings.
     * 
     */
    map<string, string> configContent;

    /**
     * @brief Internal functions, pseudo LL(1) compiler.
     * 
     * @param line of a file
     * @return string with the module
     */
    string GetModule(const string &line);

    /**
     * @brief Internal functions, pseudo LL(1) compiler.
     * 
     * @param line of a file
     * @return string with the module
     */
    void AddLine(const string &line, const string &module);

};


#endif // !CFG_FILE__
