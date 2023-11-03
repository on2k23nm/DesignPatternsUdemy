#include <iostream>

#include "FunctionalFactory.h"

using namespace std;

int main(int argc, char *argv[])
{
   DrinkWithVolumeFactory dwvf; 

   auto t = dwvf.makeDrink("Tea");
   auto c = dwvf.makeDrink("Coffee");

   return 0;
}