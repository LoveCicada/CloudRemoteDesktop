
#include <iostream>
#include "CBaseHelper.h"
#include <QGuiApplication>


bool CBaseHelper::IsSpecilaKeyPress(int32_t nModifier)
{
    bool bRet = false;
    Qt::KeyboardModifiers modifier = static_cast<Qt::KeyboardModifiers>(nModifier);
    
    switch (modifier)
    {
    case Qt::NoModifier:
        bRet = false; break;
    case Qt::ShiftModifier:
        bRet = true; break;
    case Qt::ControlModifier:
        bRet = true; break;
    case Qt::AltModifier:
        bRet = true; break;
    case Qt::MetaModifier:
        bRet = true; break;
    case Qt::KeypadModifier:
        bRet = true; break;
    case Qt::GroupSwitchModifier:
        bRet = true; break;
    case Qt::KeyboardModifierMask:
        bRet = true; break;

    default:
        break;
    }

    return bRet;
}

bool CBaseHelper::IsTabKeyPress(int32_t nModifier)
{
    bool bRet = false;
    Qt::KeyboardModifiers curModifier = QGuiApplication::keyboardModifiers();

    static_cast<bool>(bRet);
    static_cast<int32_t>(nModifier);
    static_cast<int32_t>(curModifier);

    //if(curModifier == )
    //QKeyEvent()


    return false;
}
