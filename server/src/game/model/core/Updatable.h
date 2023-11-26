#ifndef TP_WORMS_UPDATABLE_H
#define TP_WORMS_UPDATABLE_H

class Updatable {
public:
    virtual void update(int it, int rate) = 0;
};

#endif //TP_WORMS_UPDATABLE_H
