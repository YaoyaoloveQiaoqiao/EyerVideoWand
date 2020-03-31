#include "MBWand.hpp"

namespace MB
{
    MBWandResource::MBWandResource()
    {

    }

    MBWandResource::~MBWandResource()
    {

    }

    int MBWandResource::SetPath(MBString _resPath)
    {
        resPath = _resPath;
        return 0;
    }
}