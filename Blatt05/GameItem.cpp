//
// Created by paul on 21.12.18.
//

#include "GameItem.hpp"

namespace model {
    GameItem::GameItem(Vec pos, Vec size) : rect(pos, size) {}

    auto GameItem::getPosition() const -> Vec {
        return (rect.topLeft() + rect.bottomRight()) * 0.5;
    }

    auto GameItem::getDimension() const -> Vec {
        return rect.getSize();
    }

    auto GameItem::getBoundingRect() const -> Rect {
        return rect;
    }
}
