#include "animations.h"
#include "reef.h"

#include <assert.h>

namespace visualizer
{
    Color GetTeamColor(int team)
    {
        // todo: need to change these colors
        return (team == 1) ? Color(1.0f,.7f,0.1f,1.0f) : Color(0.1f,1.0f,0.1f,1.0f);
    }

    void DrawMap::animate(const float& t, AnimData*, IGame* game)
    {
        // draw a blue background
        game->renderer->setColor(Color(0.0f,0.0f,1.0f,1.0f));
        game->renderer->drawQuad(0.0f,0.0f,m_Map->GetWidth(),m_Map->GetHeight());

        game->renderer->setColor(Color(1.0f,.8f,1.0f,1.0f));

        // render each tile on the map
        for (int x = 0; x < m_Map->GetWidth(); x++)
        {
          for (int y = 0; y < m_Map->GetHeight(); y++)
          {
              Map::Tile& tile = (*m_Map)(y,x);

              if(tile.bCove)
              {
                  game->renderer->drawAnimQuad(x,y,1,1,"coral",tile.spriteId);
              }
          }
        }
    }

    void DrawSprite::animate(const float &t, AnimData *d, IGame *game)
    {
        game->renderer->setColor( Color(1.0f,1.0f,1.0f,1.0f) );
        game->renderer->drawTexturedQuad(m_sprite->x, m_sprite->y, m_sprite->dx, m_sprite->dy,m_sprite->m_sprite);
    }

    void DrawAnimation::animate(const float& t, AnimData*, IGame* game )
    {

        if(m_animation->enable.empty() || game->options->getNumber(m_animation->enable) > 0.0f)
        {
            game->renderer->setColor( Color(1.0f,1.0f,1.0f,1.0f) );
            game->renderer->drawAnimQuad( m_animation->x, m_animation->y, m_animation->dx, m_animation->dy, m_animation->m_sprite , (int)(m_animation->frames * t));
        }

    }


    void DrawFish::animate(const float &t, AnimData *d, IGame *game)
    {
        unsigned int index = (unsigned int)(m_Fish->m_moves.size() * t);
        float subT = m_Fish->m_moves.size() * t - index;

        glm::vec2 diff = m_Fish->m_moves[index].to - m_Fish->m_moves[index].from;
        glm::vec2 pos = m_Fish->m_moves[index].from + diff * subT;

        game->renderer->setColor( GetTeamColor(m_Fish->owner) );
        game->renderer->drawTexturedQuad(pos.x,pos.y,1.5,1.5,"fish",m_Fish->flipped || (diff.x > 0.0f));
    }
    
    void DrawTrash::animate(const float &t, AnimData *d, IGame *game)
    {
        /*if((m_Trash->moveTurn == game->timeManager->getTurn()) && t < 0.8f)
            return;*/

        // todo: someone needs to make the trash get darker based on the amount of trash
        game->renderer->setColor( Color( 1.0f, 1.0f, 1.0f, 1.0f ) );
        game->renderer->drawTexturedQuad(m_Trash->x,m_Trash->y,1,1,"trash");

        stringstream stream;
        stream << m_Trash->amount;
        game->renderer->setColor( Color( 1.0f, 1.0f, 1.0f, 1.0f ) );
        game->renderer->drawText(m_Trash->x,m_Trash->y,"Roboto",stream.str(),5);

    }

}

