#include "animations.h"
#include "reef.h"

namespace visualizer
{

    void DrawMap::animate(const float& t, AnimData*, IGame* game)
    {
        game->renderer->setColor(Color(1.0f,0.5f,1.0f,1.0f));

        // render each tile on the map
        for (int x = 0; x < m_Map->GetWidth(); x++)
        {
          for (int y = 0; y < m_Map->GetHeight(); y++)
          {
              Map::Tile& tile = (*m_Map)(y,x);

              if(tile.isCove > 0)
              {
                  game->renderer->drawAnimQuad(x,y,1,1,"coral",tile.spriteId);
              }
              else
              {

              }
          }
        }


        float fSeconds = timer.elapsed() / 1000.0f;

        // todo: change the direction of the water based on time

        // blend water map ontop of all the tiles
        game->renderer->setColor(Color(1.0,1.0f,1.0f,0.4f));
        game->renderer->drawSubTexturedQuad(0,0,m_Map->GetWidth(),m_Map->GetHeight(),(fSeconds)/53.0f,-(fSeconds)/53.0f,1.0f,1.0f,"water");
        //game->renderer->drawTexturedQuad(0,0,m_Map->GetWidth(),m_Map->GetHeight(),"water");
    }

    void DrawAnimation::animate(const float& t, AnimData*, IGame* game )
    {

        if(m_animation->enable.empty() || game->options->getNumber(m_animation->enable) > 0.0f)
        {
            game->renderer->setColor( Color(1.0f,1.0f,1.0f,1.0f) );
            game->renderer->drawAnimQuad( m_animation->x, m_animation->y, m_animation->dx, m_animation->dy, m_animation->animation , (int)(m_animation->frames * t));
        }

    }

    void StartAnim::animate( const float& /* t */, AnimData * /* d */, IGame* /*game*/ )
    {
    }

    void DrawSomething::animate( const float& /*t*/, AnimData * /*d*/, IGame* game )
    {
        // Set the color to red
        game->renderer->setColor( Color( 1, 0, 0, 1 ) );
        // Draw a 2x2 rectangle at (1,1), with the top left corner of the screen being the origin
        game->renderer->drawQuad( 1, 1, 2, 2 );
    }
}

