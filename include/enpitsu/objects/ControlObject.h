#ifndef ENPITSU_CONTROLOBJECT_H
#define ENPITSU_CONTROLOBJECT_H

#include "Object.h"

namespace enpitsu
{
    /**
     * An object that doesn't draw on the screen, but ticks nonetheless
     */
    class ControlObject : public Object
    {
    public:
        using Object::Object;
    };

} // enpitsu

#endif //ENPITSU_CONTROLOBJECT_H
