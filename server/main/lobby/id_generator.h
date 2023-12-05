#ifndef __SERVER_ID_GENERATOR_H__
#define __SERVER_ID_GENERATOR_H__

#include <cstdint>
#include <queue>

class IDGenerator {
public:
    IDGenerator();
    ~IDGenerator() = default;

    uint32_t getNextID();
    void releaseID(uint32_t id);

private:
    uint32_t next_id;
    std::queue<uint32_t> released_ids;
};


#endif  // _SERVER_ID_GENERATOR_H__
