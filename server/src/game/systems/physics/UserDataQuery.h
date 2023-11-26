#ifndef TP_WORMS_USERDATAQUERY_H
#define TP_WORMS_USERDATAQUERY_H

#include "box2d/box2d.h"
#include <iostream>

class UserDataQuery {
public:
public:
    template <typename T>
    T* get_user_data_as_type(b2Fixture* fixture);

    template <typename T>
    T* get_object_from_fixture(b2Fixture* fixtureA, b2Fixture* fixtureB);
};

template <typename T>
T* UserDataQuery::get_user_data_as_type(b2Fixture* fixture) {
    b2FixtureUserData userData = fixture->GetUserData();
    if (userData.pointer == 0) {
        return nullptr;
    }
    if (typeid(T) == typeid(*reinterpret_cast<T*>(userData.pointer))) {
        return reinterpret_cast<T*>(userData.pointer);
    } else {
        return nullptr;
    }
    return reinterpret_cast<T*>(userData.pointer);
}

template <typename T>
T* UserDataQuery::get_object_from_fixture(b2Fixture* fixtureA, b2Fixture* fixtureB) {
    T* objectA = get_user_data_as_type<T>(fixtureA);
    T* objectB = get_user_data_as_type<T>(fixtureB);

    // Return the first non-null object (if any)
    return (objectA != nullptr) ? objectA : objectB;
}

#endif //TP_WORMS_USERDATAQUERY_H
