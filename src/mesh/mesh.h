// sparselizard - Copyright (C) 2017-2018 A. Halbach and C. Geuzaine, University of Liege
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to <alexandre.halbach at ulg.ac.be>.


#ifndef MESH_H
#define MESH_H

#include <string>
#include "nodes.h"
#include "elements.h"
#include "physicalregions.h"
#include "disjointregions.h"
#include "universe.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "wallclock.h"
#include "physicalregion.h"
#include "gmshinterface.h"
#include "element.h"
#include <memory>
#include "shape.h"
#include "rawshape.h"
#include "myspanningtree.h"

class nodes;
class elements;
class shape;
class myspanningtree;

class mesh
{
	private:
        
        nodes mynodes;
        elements myelements;
        physicalregions myphysicalregions;
        disjointregions mydisjointregions;

        std::string filename = "";

        // The spanning tree is not yet defined if the vector is empty.
        // If not empty the spanning tree is at vector index [0].
        std::vector<myspanningtree> myspantree = {};
        

        // 'readfromfile' hands over to the function reading the format of the mesh file.
        void readfromfile(std::string);
        // 'writetofile' hands over to the function writing the format of the mesh file.
        void writetofile(std::string);

        // 'sortbybarycenters' sorts the elements (and nodes) according to 
        // the x then y then z coordinates of their barycenter. Round off
        // noise on the coordinates is taken into account in the sorting.
        void sortbybarycenters(void);
        // 'removeduplicates' removes the duplicated elements (and nodes).
        void removeduplicates(void);
        
        // 'printcount' prints the number of elements for every type.
        void printcount(void);
	
	public:
        
        mesh(void);
        mesh(std::string filename, int verbosity = 1);
        mesh(std::vector<shape> inputshapes, int verbosity = 1);
        
        nodes* getnodes(void);
        elements* getelements(void);
        physicalregions* getphysicalregions(void);
        disjointregions* getdisjointregions(void);

        // Load from file name:
        void load(std::string name, int verbosity = 1);	
        // Load from shape vector:
        void load(std::vector<shape> inputshapes, int verbosity = 1);	

        // Write to file name:
        void write(std::string name, int verbosity = 1);		
        
        // 'shift' translates the mesh in the 'x', 'y' and 'z' direction.
        void shift(double x, double y, double z);
        // 'rotate' rotates the mesh by ax, ay and az degrees around the x, y and z axis respectively.
        void rotate(double ax, double ay, double az);	
        
        // 'getmeshdimension' gives n for a mesh whose highest element dimension is n.
        int getmeshdimension(void);

        // Get a pointer to the tree spanning the whole mesh:
        myspanningtree* getspanningtree(void);     
        
        void writespanningtree(std::string filename);
        

        // FOR DEBUG. The physical regions are replaced by disjoint regions + 1:
        void writewithdisjointregions(std::string);
        // Print the disjoint region list in every physical region:
        void printphysicalregions(void);
        // Print the physical region list in every disjoint region:
        void printdisjointregions(void);
};


#endif
 
