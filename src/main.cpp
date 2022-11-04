#include <stdio.h>

#include <config.hpp>
#include <notes.hpp>
#include <engine.hpp>

#include <iostream>

void printBuff (double buff[MAXTRACKS])
{
  std::cout << "[ ";
  for (int i = 0; i < MAXTRACKS; i++)
  {
    std::cout << buff[i] << ", ";
  }
  std::cout << "]\n";
}

int main() {


  double buff[BUFFSIZE] = {0}; 

  Engine eng (false);

  eng.setTrack(440, 0);
  eng.activateTrack(0);

  for (int k = 0; k < 5; k++)
  {
    for (int i = 0; i < BUFFSIZE; i++)
    {
      buff[i] = eng.process();
    }
  }

  eng.printChannels();

  return 0;
}