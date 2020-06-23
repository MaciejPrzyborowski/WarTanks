#include "World.h"

World::World()
{

}

World::~World()
{

}

void World::addObject(TypeObject type)
{
    //// DO ZMIANY CAŁOŚĆ (TYMCZASOWE ROZWIĄZANIE DO URUCHOMIENIA KODU ////
    if(type == TypeObject::Land)
    {
        objects_.emplace_back(make_unique<Land>(4, 0.2));
    }
    else if(type == TypeObject::Tank)
    {
        Land *land;
        for(auto &el : objects_)
        {
            auto L = dynamic_cast<Land *>(el.get());
            if(L)
            {
                land = L;
            }
        }
        if(PlayerIndex == 1)
        {
            objects_.emplace_back(make_unique<Tank>(PlayerIndex, TankTextureSrc1, *land));
        }
        else
        {
            objects_.emplace_back(make_unique<Tank>(PlayerIndex, TankTextureSrc2, *land));
        }
        PlayerIndex++;
    }
    if(PlayerIndex == 3)
    {
        for(auto &el : objects_)
        {
            auto T = dynamic_cast<Tank *>(el.get());
            if(T)
            {
                for(auto &el2 : objects_)
                {
                    auto T2 = dynamic_cast<Tank *>(el2.get());
                    if(T2 != T)
                    {
                        T->enemy = T2;
                    }
                }
            }
        }
    }
}

void World::addObject(WorldObject *object)
{
    objects_.emplace_back(unique_ptr<WorldObject> (object));
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
