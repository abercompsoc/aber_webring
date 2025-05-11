#include "crow_all.h"

#include <fstream>
#include <cctype>
#include <cstddef>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <stdio.h>

typedef struct
{
  int index;
  std::string url;
  std::string name;
  std::string email;  
}Page;

class Ring
{
private:
  int pageCounter = 0;
  std::vector<Page*>* pages = new std::vector<Page*>();

  int getIndexOfName(std::string name)
  {
    int requestIndex = -1;
    for (int i = 0; i < pages->size(); i++)
    {
      if ((*pages)[i]->name == name)
      {
        requestIndex = i;
        break;  
      }
    }
    return requestIndex;
  }

public:
  ~Ring()
  {
    for (Page* page : *pages)
    {
      delete page;
    }  

    delete pages;
  }
  
  void collectPages(std::filesystem::path path)
  {
    std::ifstream* file = new std::ifstream(path);
    std::string line;
    while (std::getline(*file, line))
    {
        std::stringstream lineStream(line);

        if (line.size() == 0)
          continue;
        
        std::string url;
        std::string name;

        std::getline(lineStream, url, ',');
        std::getline(lineStream, name, ',');

        printf("index %d: url: %s, name: %s\n", pageCounter, url.c_str(), name.c_str());
      
        Page* page = new Page{pageCounter++, url, name};
        pages->push_back(page);
    }
  }

  bool nameIsInRing(std::string name)
  {
    return getIndexOfName(name) != -1;
  }

  std::string getRandomUrl()
  {
    int index = rand() % pages->size();
    Page* selectedPage = (*pages)[index];
    return selectedPage->url;
  }

  std::string left(std::string startingName)
  {
    int leftIndex = getIndexOfName(startingName);
    if (leftIndex == -1)
      return NULL;

    leftIndex--;
    if (leftIndex < 0)
      leftIndex = pages->size()-1;
    return (*pages)[leftIndex]->url;
  }
  
  std::string right(std::string startingName)
  {
    int rightIndex = getIndexOfName(startingName);
    if (rightIndex == -1)
      return NULL;

    rightIndex++;
    if (rightIndex >= pages->size())
      rightIndex = 0;
    return (*pages)[rightIndex]->url;
  }
};


std::string str_tolower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); }
                  );
    return s;
}

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    fprintf(stderr, "No file given to collect pages from, check readme.");
    return 1;
  }
  
  std::filesystem::path path = argv[1];

  Ring* ring = new Ring();
  ring->collectPages(path);

  crow::SimpleApp app;
  
  CROW_ROUTE(app, "/")([ring](){
    auto page = crow::mustache::load_text("index.html");
    return page;
  });

  CROW_ROUTE(app, "/random/")([ring](){
      crow::response response;
      response.redirect(ring->getRandomUrl());
      return response;
    });

  CROW_ROUTE(app, "/<string>/")([](std::string name){
      crow::response response;
      response.write("You didnt list a direction o_o?");
      response.code = 400;
      return response;
  });
  
  CROW_ROUTE(app, "/<string>/<string>")([ring](std::string name, std::string direction)
  {
    if (!ring->nameIsInRing(name))
    {
      crow::response response;
      response.write("The name you started your request from isnt in the ring :( \nFeel free to contact aber comp-soc and ask to be added");
      response.code = 400;
      return response;
    }
    
    if (str_tolower(direction) == "left")
    {
      std::string resultingUrl = ring->left(name);
      crow::response response;
      response.redirect(resultingUrl);
      return response;
    }
    else if (str_tolower(direction) == "right")
    {
      std::string resultingUrl = ring->right(name);
      crow::response response;
      response.redirect(resultingUrl);
      return response;
    }
    else
    {
      crow::response response;
      response.write("You requested an impossible direction around the ring :/");
      response.code = 400;
      return response;
    }
  });
  
  app.port(18080).run();


  
  delete ring;
}


