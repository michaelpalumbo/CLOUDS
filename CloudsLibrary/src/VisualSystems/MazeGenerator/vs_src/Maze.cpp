//
//  Maze.cpp
//  MazeGenerator
//
//  Created by Gal Sasson on 10/25/13.
//
//

#include "Maze.h"

#define SIDE_WALLS

Maze::Maze(float cSize, float wThickness, float wHeight, ofVec3f p)
{
    cellSize = cSize;
    wallThickness = wThickness;
    wallHeight = wHeight;
    pos = p;
    
    for (int i=0; i<NUM_CELLS_X; i++) {
        for (int j=0; j<NUM_CELLS_Y; j++)
        {
            cells[i][j] = new MazeCell(i, j, cellSize,
                wallThickness, wallHeight);
        }
    }
    
    currentCell = NULL;
    exitCell = NULL;
    
    finishedGenerating = false;
    finishedSolving = false;
    step = 0;
    currentYLimit = 40;
}

Maze::~Maze()
{
    for (int i=0; i<NUM_CELLS_X; i++)
    {
        for (int j=0; j<NUM_CELLS_Y; j++)
        {
            delete cells[i][j];
        }
    }
}

void Maze::generate()
{
    // set starting (exit) point
    int randX = 0;
    int randY = 0;
    currentCell = cells[randX][randY];
    currentCell->visit();
    currentCell->mazeExit = true;
    cellStack.push(currentCell);
    exitCell = currentCell;
    finishedGenerating = false;
    
    // generate the maze
    while (!finishedGenerating) {
        generateStep();
    }
    
    buildModel();
}

void Maze::buildModel()
{
    int verts = 0;
    int faces = 0;
    
    for (int j=0; j<NUM_CELLS_Y; j++) {
        for (int i=0; i<NUM_CELLS_X; i++) {
            verts += cells[i][j]->getVertexCount();
            faces += cells[i][j]->getFaceCount();
        }
    }
    
    ofVec3f* vertexData = new ofVec3f[verts];
    ofIndexType* indexData = new ofIndexType[faces*3];
    ofVec3f* normalData = new ofVec3f[faces];
    
    int vertsCounter=0;
    int indexCounter=0;
    int normalCounter=0;
    for (int j=0; j<NUM_CELLS_Y; j++) {
        for (int i=0; i<NUM_CELLS_X; i++) {
            indexCounter += cells[i][j]->fillIndexData(indexData, vertsCounter, indexCounter);
            vertsCounter += cells[i][j]->fillVertexData(vertexData, vertsCounter);
            normalCounter += cells[i][j]->fillNormalData(normalData, normalCounter);
        }
    }
	
	//LB
//    geometry.setVertexData(vertexData, vertsCounter, GL_STATIC_DRAW);
//    geometry.setIndexData(indexData, indexCounter, GL_STATIC_DRAW);
//    geometry.setNormalData(normalData, normalCounter, GL_STATIC_DRAW);
//    indexCount = indexCounter;
	
	
	//LB: we want it to be faceted correct?
	//
	//	-the issue seems to be that the normals are set per vertex rather then per face
	//
	//	-here I'm making new arrays out of the data coming in from the cells. with one vertex & normal per index.
	//
	//	-you probably don't need indices if it's not a smooth mesh... I commented them out.
	//
	//	-I've disregarded the old normals and am recalculating them here, it'll be a little faster to pass them hard coded from the cells. I did
	//	it this way so that I wouldn't mess with your code too much
	//
	
	vector<ofVec3f> vertices(indexCounter);
	vector<ofVec3f> normals(indexCounter);
//	vector<ofIndexType> indices(indexCounter);
	for (int i=0; i<indexCounter; i+=6)
	{
		vertices[i] = vertexData[ indexData[i] ];
		vertices[i+1] = vertexData[ indexData[i+1] ];
		vertices[i+2] = vertexData[ indexData[i+2] ];
		vertices[i+3] = vertexData[ indexData[i+3] ];
		vertices[i+4] = vertexData[ indexData[i+4] ];
		vertices[i+5] = vertexData[ indexData[i+5] ];
		
		ofVec3f faceNormal = normalFrom3Points(vertices[i], vertices[i+1], vertices[i+2]);
		normals[i] = faceNormal;
		normals[i+1] = faceNormal;
		normals[i+2] = faceNormal;
		normals[i+3] = faceNormal;
		normals[i+4] = faceNormal;
		normals[i+5] = faceNormal;
		
//		indices[i] = i;
//		indices[i+1] = i+1;
//		indices[i+2] = i+2;
//		indices[i+3] = i+3;
//		indices[i+4] = i+4;
//		indices[i+5] = i+5;
	}
	
    
    geometry.setVertexData( &vertices[0], vertices.size(), GL_STATIC_DRAW);
    geometry.setNormalData( &normals[0], normals.size(), GL_STATIC_DRAW);
//    geometry.setIndexData( &indices[0], indices.size(), GL_STATIC_DRAW);
	
    indexCount = indexCounter;
    
    delete vertexData;
    delete indexData;
    delete normalData;
	
	//LB
	vertices.clear();
	normals.clear();
//	indices.clear();
}

void Maze::update(ofCamera *cam)
{
//    if (!finishedGenerating) {
//        for (int i=0; i<4; i++) {
//            generateStep();
//        }
//    }
}

void Maze::draw(ofCamera *cam)
{
    ofPushMatrix();
    ofTranslate(pos);
    
	//LB
    //geometry.drawElements(GL_TRIANGLES, indexCount);
	
	//LB
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	geometry.draw(GL_TRIANGLES, 0, indexCount);
	glDisable(GL_CULL_FACE);
	
    
#if 0
    // for tiling
    int yStart = cam->getPosition().z/cellSize-5;
    int yLimit = min(yStart+(int)ParamManager::getInstance().showAhead,NUM_CELLS_Y);
    if (yStart < 0) {
        yStart = 0;
    }
    float length = (float)yLimit - yStart;
    float middle = (float)yStart + length/2;

    // draw the ground
    ofFill();
    ofSetColor(ParamManager::getInstance().getGroundColor());
    ofPushMatrix();
    ofTranslate(NUM_CELLS_X*cellSize/2, -wallHeight/2, middle*cellSize);
    ofScale(NUM_CELLS_X*cellSize+120, 1, length*cellSize);
    ofBox(1);
    ofPopMatrix();
    
    // draw side walls
#ifdef SIDE_WALLS
    ofSetColor(ParamManager::getInstance().getSideWallsColor());
    ofPushMatrix();
    ofTranslate(-0.1, 800-wallHeight/2, middle*cellSize);
    ofScale(wallThickness, 1600, length*cellSize);
    ofBox(1);
    ofPopMatrix();
    ofPushMatrix();
    ofTranslate(NUM_CELLS_X*cellSize+0.1, 800-wallHeight/2, middle*cellSize);
    ofScale(wallThickness, 1600, length*cellSize);
    ofBox(1);
    ofPopMatrix();
#endif
    
    // draw the cells
    for (int i=0; i<NUM_CELLS_X; i++)
    {
        for (int j=yStart; j<yLimit; j++)
        {
            cells[i][j]->draw(currentCell == cells[i][j]);
        }
    }
#endif
    
    ofPopMatrix();
}

float Maze::getWidth()
{
    return NUM_CELLS_X*cellSize;
}

void Maze::generateStep()
{
    if (finishedGenerating) { return; }
    bool valid = false;
    std::vector<int> available_dirs;
    for (int i=0;i<4;i++)
    {
        available_dirs.push_back(i);
        
        
    }
    while (!valid) {
        int curx = currentCell->getX();
        int cury = currentCell->getY();
        int dir_idx = int(ofRandom(available_dirs.size()));
        int dir = available_dirs[dir_idx];
        
        switch(dir) {
            case 0:
                if (cury > 0 && cells[curx][cury-1]->notVisited()) {
                    currentCell->top = false;
                    currentCell = cells[curx][cury-1];
                    currentCell->visit();
                    currentCell->bottom = false;
                    cellStack.push(currentCell);
                    valid = true;
                } else {
                    available_dirs.erase(available_dirs.begin() + dir_idx);
                }
                break;
            case 1:
                if (curx < NUM_CELLS_X-1 && cells[curx+1][cury]->notVisited()) {
                    currentCell->right = false;
                    currentCell = cells[curx+1][cury];
                    currentCell->visit();
                    currentCell->left = false;
                    cellStack.push(currentCell);
                    valid = true;
                } else {
                    available_dirs.erase(available_dirs.begin() + dir_idx);
                }
                break;
            case 2:
                if (cury < min(NUM_CELLS_Y-1,currentYLimit-1) && cells[curx][cury+1]->notVisited()) {
                    currentCell->bottom = false;
                    currentCell = cells[curx][cury+1];
                    currentCell->visit();
                    currentCell->top = false;
                    cellStack.push(currentCell);
                    valid = true;
                } else {
                    available_dirs.erase(available_dirs.begin() + dir_idx);
                }
                break;
            case 3:
                if (curx > 0 && cells[curx-1][cury]->notVisited()) {
                    currentCell->left = false;
                    currentCell = cells[curx-1][cury];
                    currentCell->visit();
                    currentCell->right = false;
                    cellStack.push(currentCell);
                    valid = true;
                } else {
                    available_dirs.erase(available_dirs.begin() + dir_idx);
                }
                break;
        }  // end switch
        if (!valid && available_dirs.size() == 0) {
            if (!cellStack.empty()) {
                currentCell = cellStack.top();
                cellStack.pop();
            }
            else {
                int prevLimit = currentYLimit;
                currentYLimit += 60;
                if (prevLimit > NUM_CELLS_Y) {
                    finishedGenerating = true;
                    currentCell = NULL;
                }
                else {
                    currentCell = cells[0][prevLimit+1];
                }
            }
            valid = true;
        }
    } // end while
}

