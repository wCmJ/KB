#ifndef HEADER_H_
#define HEADER_H_

#include <string>

namespace http{
namespace server{

struct header{
    std::string name;
    std::string value;
};

}}

#endif