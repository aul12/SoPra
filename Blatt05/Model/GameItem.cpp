//
// Created by paul on 21.12.18.
//

#include "GameItem.hpp"

namespace model {
    GameItem::GameItem(Vec pos, Vec size) : rect(pos-size*0.5, size) {}

    auto GameItem::getPosition() const -> Vec {
        return (rect.topLeft() + rect.bottomRight()) * 0.5;
    }

    void GameItem::setPosition(Vec pos) {
        rect.setAnchor(pos-this->getSize()*0.5);
    }

    auto GameItem::getSize() const -> Vec {
        return rect.getSize();
    }

    auto GameItem::getBoundingRect() const -> Rect {
        return rect;
    }
}
