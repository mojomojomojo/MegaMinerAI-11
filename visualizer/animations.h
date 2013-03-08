#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "reefAnimatable.h"
 #include <QElapsedTimer>

namespace visualizer
{

    struct StartAnim: public Anim
    {
      public:
        void animate( const float& t, AnimData *d, IGame* game );

    };

    class DrawAnimation : public Anim
    {
    public:
        DrawAnimation( SpriteAnimation* animation ) : m_animation(animation) {}
        void animate( const float& t, AnimData* d, IGame* game );

    private:
        SpriteAnimation* m_animation;
    };

    class DrawMap: public Anim
    {
        public:
        DrawMap( Map* map ) : m_Map(map)
        {
            timer.start();
        }

        void animate( const float& t, AnimData* d, IGame* game );

        private:
            Map *m_Map;
            QElapsedTimer timer;

    }; // DrawBackground

    class DrawFish: public Anim
    {
    public:
        DrawFish(Fish* fish) : m_Fish(fish) {}

        void animate(const float &t, AnimData *d, IGame *game);

    private:
        Fish* m_Fish;
    };//DrawFish

  
    class DrawSomething: public Anim
    {
        public:
            DrawSomething( Something* something ) { m_Something = something; }
            void animate( const float& t, AnimData* d, IGame* game );
        
        private:
            Something *m_Something;

    }; // DrawBackground
}

#endif // ANIMATION_H
