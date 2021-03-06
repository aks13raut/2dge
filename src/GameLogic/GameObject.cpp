#include "GameObject.hpp"

#include "spdlog/spdlog.h"

void GameObject::setPosition(sf::Vector2f pos){
    m_position = pos;
    m_sprite.setPosition(pos);
    m_AABB.top = pos.y;
    m_AABB.left = pos.x;
}

void GameObject::setPosition(float x, float y){
    m_position.x = x;
    m_position.y = y;
    m_sprite.setPosition(x,y);
    m_AABB.top = y;
    m_AABB.left = x;
}

void GameObject::setSize(float w,float h){
    m_sprite.scale({w/16,h/16});
    m_AABB.width = w;
    m_AABB.height = h;
}

void GameObject::setAABB(const tmx::FloatRect& AABB){
    m_AABB.top = AABB.top;
    m_AABB.left = AABB.left;
    m_AABB.height = AABB.height;
    m_AABB.width = AABB.width;
}

const sf::FloatRect& GameObject::getAABB(){
    return m_AABB;
}

bool GameObject::intersects(const sf::FloatRect& target){
    return m_AABB.intersects(target);
}

bool GameObject::intersects(GameObject& target){
    return m_AABB.intersects(target.m_AABB);
}

bool GameObject::intersects(const std::vector<GameObject*>& list){
    for(auto obj : list){
        if(intersects(obj->getAABB()))
            return true;
    }
    return false;
}

bool GameObject::contains(const sf::Vector2f& point){
    return m_AABB.contains(point);
}

void GameObject::setTexture(const sf::Texture& texture){
    m_sprite.setTexture(texture);
}

void GameObject::setTextureRect(const sf::IntRect &rectangle)  {
    m_sprite.setTextureRect(rectangle);
}

void GameObject::scale(const sf::Vector2f scl){
    m_sprite.scale(scl);
}

void GameObject::setSpeed(int spd){
    m_speed = spd;
}

sf::Vector2f GameObject::getPosition(){
    return m_position;
}

void GameObject::addProp(std::string key,std::string value){
    m_properties[key] = value;
}
std::string GameObject::getProp(std::string key){
    if(m_properties.find(key) != m_properties.end())
        return m_properties[key];
    return "NOTFOUND";
}


void GameObject::handleEvent(sf::Event event){

    switch(event.type) {
    
        case sf::Event::KeyPressed:
        switch (event.key.code) {
            case sf::Keyboard::Up:
            displacement.y = -1*m_speed;
            break;
            case sf::Keyboard::Down:
            displacement.y = m_speed;
            break;
            case sf::Keyboard::Left:
            displacement.x = -1*m_speed;
            break;
            case sf::Keyboard::Right:
            displacement.x = m_speed;
            break;
        }
        break;

        case sf::Event::KeyReleased:
        switch (event.key.code) {
            case sf::Keyboard::Up:
            if(displacement.y < 0)
                displacement.y = 0;
            break;
            case sf::Keyboard::Down:
            if(displacement.y > 0)
                displacement.y = 0;
            break;
            case sf::Keyboard::Left:
            if(displacement.x < 0)
                displacement.x = 0;
            break;
            case sf::Keyboard::Right:
            if(displacement.x > 0)
                displacement.x = 0;
            break;
        }
        break;
    }
}

void GameObject::move(sf::Vector2f disp){
    m_position += disp;
    m_sprite.setPosition(m_position);
    m_AABB.top += disp.y;
    m_AABB.left += disp.x;
    m_revertDisp.x = -1.5*disp.x;
    m_revertDisp.y = -1.5*disp.y;
}

void GameObject::revertMove(){
    m_position += m_revertDisp;
    m_sprite.setPosition(m_position);
    m_AABB.top += m_revertDisp.y;
    m_AABB.left += m_revertDisp.x;
}

const sf::Vector2f GameObject::getDisplacement(){
    return displacement;
}

void GameObject::update(sf::Time deletaTime){
    move(displacement);
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}