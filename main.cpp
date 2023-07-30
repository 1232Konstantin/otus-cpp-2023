
#include "Editor/CmdApplication.h"

int main()
{
  std::istringstream iss("\
        CreateDocument Doc1.img\n\
        CreatePrimitive (1,2) (3,4) (5,6)\n\
        CreatePrimitive (7,8) (9,10)\n\
        ImportDocument Doc2.img\n\
        CreatePrimitive (11,12) (13,14) (15,16)\n\
        CreatePrimitive (17,18) (19,20)\n\
        ExportDocument ExDoc.img\n\
        CreatePrimitive (21,22) (23,24) (25,26)\n\
        DeleteLastNPrimitives 2\n\
        Exit\n\
    ");

  Editor::FCmdApplication app{iss};
  app.Begin();

  return 0;
}


/*


class D
{
public:
  bool DFunc(const std::string& str)
  {
    std::cout << "str=" << str << std::endl;
    return true;
  }
  bool print_add(const int& i) 
  { 
    std::cout << 10 + i << '\n'; 
    return true;
  }
  void foo(int n) {
    std::cout << "A::foo(" << n << ")\n";
  }
};

*/
/*
#include <string>
#include <iostream>
#include <memory>
#include <functional>

#include "Editor/Layers/Domain/Private/Document.h"
#include "IStorage.h"
#include "Editor/Layers/Domain/Private/Storage.h"
#include "Editor/Layers/Presentation/Private/GUI.h"

using namespace Editor;


template<class A>
class Btn
{
public:
  explicit Btn(const std::function<bool(const A& Arg)>& InFunc)
    : Func(InFunc)
  {
  }

  bool Call(const A& a)
  {
    return Func(a);
  }

  std::function<bool(const A& Arg)> Func;
};

class Control
{
public:

  Control()
  {
    d = std::make_shared<FStorage>(std::make_shared<FGUI>());
    
    //CBtn = std::make_shared<Btn<std::string>>(std::bind(&Control::CreateDocumentImpl, *this, std::placeholders::_1));
  }

  bool CallS(const std::string& a)
  {
    return CBtn->Call(a);
  }

  bool CreateDocumentImpl(const std::string& a)
  {
    return d->CreateDocument(a);
  }

  std::shared_ptr<IStorage> d;
  std::shared_ptr<Btn<std::string>> CBtn;
};


#include <string>
#include <iostream>
#include <memory>
#include <functional>

#include "IStorage.h"
#include "IGUI.h"
using namespace Editor;

int main()
{
  std::shared_ptr<IStorage> s = StorageFactory::Create(GUIFactory::Create());
  s->CreateDocument("Name");
}
*/