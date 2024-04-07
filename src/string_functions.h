#ifndef AQUASENSE_STRING_FUNCTIONS
#define AQUASENSE_STRING_FUNCTIONS

#include "deps.h"

namespace as
{

#ifdef _WIN32
#   define PATH_SEP "\\\\"
#else
#   define PATH_SEP "/"
#endif

class  Path
{
public:
    Path() {};
    ~Path() {};

    Path& operator<<(std::string child);
    std::string Get();

    static std::string GetData(std::string p);
    static std::string GetData(Path& p) { return GetData(p.Get()); };

    friend std::ostream& operator<<(std::ostream& os, Path path);

private:
    std::vector<std::string> childs;

};

}

#endif // AQUASENSE_STRING_FUNCTIONS
