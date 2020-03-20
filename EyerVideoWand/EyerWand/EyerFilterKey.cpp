#include "EyerWand.hpp"

namespace Eyer
{
    EyerFilterKey::EyerFilterKey()
    {

    }

    EyerFilterKey::EyerFilterKey(const EyerFilterKey & fk)
    {
        *this = fk;
    }

    EyerFilterKey & EyerFilterKey::operator = (const EyerFilterKey & fk)
    {
        t = fk.t;
        level = fk.level;

        for(int i=0; i<fk.filterNameList.getLength(); i++){
            int filterType = -1;
            fk.filterNameList.find(i, filterType);
            if(filterType != -1){
                filterNameList.insertBack(filterType);
            }
        }
        return *this;
    }
}
