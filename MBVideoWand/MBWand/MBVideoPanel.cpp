#include "MBWand.hpp"

namespace MB
{
    MBVideoPanel::MBVideoPanel()
    {
    }

    MBVideoPanel::~MBVideoPanel()
    {
    }

    MBVideoPanel::MBVideoPanel(const MBVideoPanel & panel)
    {
        *this = panel;
    }

    MBVideoPanel & MBVideoPanel::operator = (const MBVideoPanel & panel)
    {
        mvp = panel.mvp;
        frame = panel.frame;
        return *this;
    }

    int MBVideoPanel::GetYDate(unsigned char * yData)
    {
        frame.GetYData(yData);
        return 0;
    }

    int MBVideoPanel::GetUDate(unsigned char * uData)
    {
        frame.GetUData(uData);
        return 0;
    }

    int MBVideoPanel::GetVDate(unsigned char * vData)
    {
        frame.GetVData(vData);
        return 0;
    }

    int MBVideoPanel::GetW()
    {
        return frame.GetWidth();
    }

    int MBVideoPanel::GetH()
    {
        return frame.GetHeight();
    }

    int MBVideoPanel::SetData(MBAVFrame & _frame)
    {
        frame = _frame;
        return 0;
    }

    MBMat4x4 MBVideoPanel::GetMVPMat()
    {
        return mvp;
    }
}