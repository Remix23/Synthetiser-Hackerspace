#include <stdio.h>

#include <config.hpp>
#include <notes.hpp>
#include <engine.hpp>

#include <iostream>

using namespace std;

void printBuff (double buff[MAXTRACKS])
{
  cout << "[ ";
  for (int i = 0; i < MAXTRACKS; i++)
  {
    cout << buff[i] << ", ";
  }
  cout << "]\n";
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