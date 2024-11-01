#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <stdexcept>

class Ship {
public:
    enum SegmentState { Whole, Damage, Destroyed };
    enum Orientation { Horizontal, Vertical };

    Ship(size_t length, Orientation orientation);
    size_t getLength() const;
    Orientation getOrientation() const;
    SegmentState getSegmentState(size_t index) const;
    void hitSegment(size_t index);
    bool isDestroyed() const;

private:
    size_t length;
    Orientation orientation;
    std::vector<SegmentState> segments;

    static void validate(size_t length);
    void checkIndex(size_t index) const;
};

#endif
