#include "Ship.h"

Ship::Ship(size_t length, Orientation orientation)
    : length(length), orientation(orientation), segments(length, Whole) {
    validate(length);
}

size_t Ship::getLength() const {
    return length;
}

Ship::Orientation Ship::getOrientation() const {
    return orientation;
}

Ship::SegmentState Ship::getSegmentState(size_t index) const {
    checkIndex(index);
    return segments[index];
}

void Ship::hitSegment(size_t index) {
    checkIndex(index);
    if (segments[index] == Whole) {
        segments[index] = Damage;
    } else if (segments[index] == Damage) {
        segments[index] = Destroyed;
    }
}

bool Ship::isDestroyed() const {
    for (const auto& segment : segments) {
        if (segment != Destroyed) {
            return false;
        }
    }
    return true;
}

void Ship::validate(size_t length) {
    if (length < 1 || length > 4) {
        throw std::invalid_argument("Длина должна быть от 1 до 4");
    }
}

void Ship::checkIndex(size_t index) const {
    if (index >= length) {
        throw std::out_of_range("Неверный индекс сегмента");
    }
}
