#ifndef REQUEST_H_
#define REQUEST_H_

#include <string>
#include <vector>
#include "head.h"

namespace http{
namespace server{

struct request{
    std::string method;
    std::string url;
    int http_version_major;
    int http_version_minor;
    std::vector<header> headers;
};

}}

#endif

