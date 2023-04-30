#ifndef ENPITSU_DRAWABLE_H
#define ENPITSU_DRAWABLE_H

namespace enpitsu
{
    class Drawable
    {
    public:
        Drawable() = default;

        virtual ~Drawable() = default;

    protected:
        virtual void draw() = 0;
    };
}

#endif //ENPITSU_DRAWABLE_H
