
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