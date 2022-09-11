#include "list.hpp"
void dbgCtorList() {
#ifdef ENABLE_CTOR_DBG_PRINTs
    std::cout << "dbg[ctor] initializer list \n";
#endif
}

void dbgCtorCopy() {
#ifdef ENABLE_CTOR_DBG_PRINTs
    std::cout << "dbg[ctor] copy\n";
#endif
}

void dbgCtorMove() {
#ifdef ENABLE_CTOR_DBG_PRINTs
    std::cout << "dbg[ctor] move\n";
#endif
}

void dbgCtorAssigCopy() {
#ifdef ENABLE_CTOR_DBG_PRINTs
    std::cout << "dbg[ctor] copy - assignment\n";
#endif
}

void dbgCtorAssignMove()
{
#ifdef ENABLE_CTOR_DBG_PRINTs
    std::cout << "dbg[ctor] move - assignment \n";
#endif
}