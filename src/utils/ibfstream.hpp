#ifndef tc_utils_ibfstream_hpp
#define tc_utils_ibfstream_hpp

#include <fstream>

namespace tc {
namespace utils {

struct ibfstream
{
private:
    std::ifstream is;
public:
    ibfstream(std::string path):is(path){}
    ~ibfstream(){}

    template<typename T>
    inline ibfstream& operator>>(T& ref)
    {
        is.read((       char*)&ref, sizeof(T));
        return *this;
    }
    inline ibfstream& seek(std::streampos pos)
    { is.seekg(pos); return *this; }
    inline std::streampos tell()
    { return is.tellg(); }
    inline ibfstream& move(std::streamoff off)
    { is.seekg(off, std::ios::cur); return *this; }
};

}}

#endif