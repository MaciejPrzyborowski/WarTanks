#include "World.h"

World::World()
{

}

World::~World()
{

}

WorldObject * World::addObject(ObjectType type)
{
    if(type == ObjectType::Land)
    {
        objects_.emplace_back(make_unique<Land>(4, 0.2));
    }
    else if(type == ObjectType::Tank)
    {
        if(PlayerIndex == 1)
        {
            objects_.emplace_back(make_unique<Tank>(PlayerIndex, TankTextureSrc1));
        }
        else
        {
            objects_.emplace_back(make_unique<Tank>(PlayerIndex, TankTextureSrc2));
        }
        PlayerIndex++;
    }
    return objects_.back().get();
}

WorldObject * World::addObject(WorldObject *object)
{
    objects_.emplace_back(unique_ptr<WorldObject> (object));
    return objects_.back().get();
}

void World::drawAll(sf::RenderWindow &window)
{
    for(auto object = objects_.begin(); object != objects_.end(); object++)
    {
        if(!(*object)->isDestructed_)
        {
            (*object)->draw(window);
        }
    }
}

void World::stepAll(const float &elapsed)
{
    for(auto object = objects_.begin(); object != objects_.end(); object++)
    {
        if(!(*object)->isDestructed_)
        {
            (*object)->step(elapsed);
        }
    }
}

void World::resetAll()
{
    for(auto object = objects_.begin(); object != objects_.end(); object++)
    {
        if(!(*object)->isDestructed_)
        {
            (*object)->reset();
        }
    }
}

void World::getCollisionAll()
{
    for(auto object = objects_.begin(); object != objects_.end();)
    {
        if((*object) -> isDestructed_)
        {
            object = objects_.erase(object);
        }
        else
        {
            for(auto objectNext = objects_.begin(); objectNext != objects_.end(); objectNext++)
            {
                if(object != objectNext)
                {
                    (*object)->getCollison(*(*objectNext).get());
                }
            }
            object++;
        }
    }
}
