#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "reefAnimatable.h"

namespace visualizer
{
    struct StartAnim : public Anim
    {
      public:
        void animate( const float& t, AnimData *d, IGame* game );

    };

    class DrawSprite : public Anim
    {
    public:
        DrawSprite( BaseSprite* sprite ) : m_sprite(sprite) {}
        void animate( const float& t, AnimData* d, IGame* game );

    private:
        BaseSprite* m_sprite;
    };

    class DrawAnimation : public Anim
    {
    public:
        DrawAnimation( SpriteAnimation* animation ) : m_animation(animation) {}
        void animate( const float& t, AnimData* d, IGame* game );

    private:
        SpriteAnimation* m_animation;
    };

    class DrawMap : public Anim
    {
        public:

        DrawMap( Map* map ) : m_Map(map) {}

        void animate( const float& t, AnimData* d, IGame* game );

        private:
            Map *m_Map;


    }; // DrawBackground

    class DrawFish : public Anim
    {
    public:
        DrawFish(Fish* fish) : m_Fish(fish) {}

        void animate(const float &t, AnimData *d, IGame *game);

    private:
        Fish* m_Fish;
    };//DrawFish
    
    class DrawTrash : public Anim
    {
    public:
        DrawTrash(Trash* trash) : m_Trash(trash) {}
        
        void animate(const float &t, AnimData *d, IGame *game);
        
    private:
        Trash *m_Trash;
    };//DrawTrash

    class DrawHUD : public Anim
    {
    public:
        DrawHUD(HUDInfo* pInfo) : m_pHud(pInfo) {}

        void animate(const float &t, AnimData *d, IGame *game);

    private:

        HUDInfo* m_pHud;
    };

}

#endif // ANIMATION_H
