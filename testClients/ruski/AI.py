#-*-python-*-
from BaseAI import BaseAI
from GameObject import *
import random
import time

class AI(BaseAI):
  """The class implementing gameplay logic."""

  myCoves = []
  myFish = []

  @staticmethod
  def username():
    return "ruski"

  @staticmethod
  def password():
    return "password"

  ##This function is called once, before your first turn
  def init(self):
    print "Init"
    self.getMyCoves()
    return

  ##This function is called once, after your last turn
  def end(self):
    self.printMyFish()
    print "The End"
    return

  def getMyFish(self):
    self.myFish = []
    for fish in self.fishes:
      if fish.owner is self.playerID:
        self.myFish.append(fish)
    return

  def attemptSpawn(self, x, y, species):
    me = self.players[self.playerID]
    if x < 0 or x > self.mapWidth:
      return False
    if y < 0 or y > self.mapHeight:
      return False

    if self.getCurrentSeason() is not species.season:
      return False

    #print "Spawn Food: %i    Species Cost: %i" % (me.spawnFood, species.cost)
    if me.spawnFood < species.cost:
      return False

    species.spawn(x, y)
    return True

  def getMyCoves(self):
    print "Find coves."
    self.myCoves = []
    for tile in self.tiles:
      if tile.owner is self.getPlayerID():
        self.myCoves.append(tile)
    return

  def printMyCoves(self):
    print "MY COVES:"
    for cove in self.myCoves:
      print "(%i, %i)" % (cove.x, cove.y),
    return

  def printTiles(self):
    print "TILES:"
    for tile in self.tiles:
      print "%i:(%i, %i)" % (tile.id, tile.x, tile.y),
    return

  def printSpecies(self):
    print "SPECIES:"
    for spec in self.species:
      print "%i %s" % (spec.index, spec.name)

  def printPlayers(self):
    print "PLAYERS:"
    for play in self.players:
      print "%s %i" % (play.playerName, play.id)
    return

  def printMyFish(self):
    print "MY FISH:"
    for fish in self.myFish:
      print "%i %s (%i, %i)" % (fish.id, self.species[fish.species].name, fish.x, fish.y)
    return

  ##This function is called each time it is your turn
  ##Return true to end your turn, return false to ask the server for updated information
  def run(self):
    print "Starting Turn #%i" % self.turnNumber
    self.getMyFish()
    self.printMyFish()
    self.printSpecies()
    time.sleep(.25)

    for fish in self.myFish:
      fish.move(fish.x+1, fish.y)

    for spec in self.species:
      for cove in self.myCoves:
        self.attemptSpawn(cove.x, cove.y, spec)

    return 1

  def __init__(self, conn):
    BaseAI.__init__(self, conn)
