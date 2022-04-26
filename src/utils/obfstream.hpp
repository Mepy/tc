#ifndef tc_utils_obfstream_hpp
#define tc_utils_obfstream_hpp

#include <fstream>

namespace tc {
namespace utils {

struct obfstream
{
private:
    std::ofstream os;
public:
    obfstream(std::string path):os(path){}
    ~obfstream(){}

    template<typename T>
    inline obfstream& operator<<(const T& ref)
    { os.write((const char*)&ref, sizeof(T)); return *this; }
    template<typename T>
    inline obfstream& operator<<(const T&& ref)
    { return (*this)<<ref; }

    inline obfstream& seek(std::__1::streampos pos)
    { os.seekp(pos); return *this; }
};

}}

#endif