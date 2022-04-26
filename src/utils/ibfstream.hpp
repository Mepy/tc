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
    inline ibfstream& seek(std::__1::streampos pos)
    { is.seekg(pos); return *this; }
};

}}

#endif