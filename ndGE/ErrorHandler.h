#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <string>

namespace ndGE {
    extern void fatalError(const std::string &message);    //!< Prints error message, quits SDL and program
}

#endif // ERRORHANDLER_H
