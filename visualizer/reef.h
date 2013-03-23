#ifndef REEF_H
#define REEF_H

#include <QObject>
#include <QThread>
#include <QElapsedTimer>
#include "igame.h"
#include "animsequence.h"
#include <map>
#include <string>
#include <list>
#include "reefAnimatable.h"

// The Codegen's Parser
#include "parser/parser.h"
#include "parser/structures.h"

using namespace std;

namespace visualizer
{
    struct Rect
    {
        int left;
        int top;
        int right;
        int bottom;
    };

    struct ReefInfo
    {
        ReefInfo(int health, int food) : currentReefHealth(health), spawnFood(food) {}

        int currentReefHealth;
        int spawnFood;
    };


    class Reef: public QThread, public AnimSequence, public IGame
    {
        Q_OBJECT;
        Q_INTERFACES( visualizer::IGame );
        public: 
            Reef();
            ~Reef();

            PluginInfo getPluginInfo();
            void loadGamelog( std::string gamelog );

            void run(); //main function
            void setup();
            void destroy();

            void preDraw();
            void postDraw();

            void addCurrentBoard();
    
            map<string, int> programs;
            
            list<int> getSelectedUnits();

             static const int SEA_OFFSET = 4;

        private:
            parser::Game *m_game;  // The Game Object from parser/structures.h that is generated by the Codegen
            QElapsedTimer m_WaterTimer;
            bool m_suicide;

            list<int> m_selectedUnitIDs;
            std::vector<ReefInfo> m_ReefInfo;
            std::vector<std::map<int,BasicTrash> > m_Trash;
            std::vector<std::vector<parser::Species> > m_Species;

            void BuildWorld(class Map* pMap);

            void GetSelectedRect(Rect& out) const;

            void RenderWorld();

            void RenderObjectSelection();

            void RenderSpecies();

            void RenderPlayerInfo();

            void RenderPlayerName(unsigned int id, float xPos = 1.0f);
            void RenderReefHealthBar(unsigned int id, float xPos = 1.0f);

            template< class T >
            bool DrawQuadAroundObj(const T& datastruct, const typename T::key_type& key)
            {
              auto iter = datastruct.find(key);

              if(iter != datastruct.end())
              {
                const auto& obj = iter->second;

                renderer->setColor( Color( 1.0, 0.4, 0.4, 0.6 ) );
                renderer->drawQuad(obj.x,obj.y,1,1);
                return true;
              }

              return false;
            }
    }; 

} // visualizer

#endif // REEF_H
