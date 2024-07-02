
#ifndef VERTEXPOSITION_H
#define VERTEXPOSITION_H

enum class VertexPositionType {
UpVertex,
UpRightVertex,
BottomRightVertex,
BottomVertex,
BottomLeftVertex,
UpLeftVertex
};

class VertexPosition
{
public:
static VertexPositionType convertToVertexPositionType(int num)
{
    switch (num) 
    {
    case 1:
        return VertexPositionType::UpVertex;
        break;
    case 2:
        return VertexPositionType::UpRightVertex;
        break;
    case 3:
        return VertexPositionType::BottomRightVertex;
        break;
    case 4:
        return VertexPositionType::BottomVertex;
        break;
    case 5:
        return VertexPositionType::BottomLeftVertex;
        break;
    case 6:
            return VertexPositionType::UpLeftVertex;
        break;
    default:
        std::cout<<"Warning:Invalid vertex position."<<std::endl;
        return VertexPositionType::UpVertex;
    }


}


};


#endif
