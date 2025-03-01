//==================================================================================================
// Name        : tri.h
// Author      : A. Emre Ongut
// Version     : 1.3
// Copyright   : See the copyright notice in the README file.
// Description : Class definitions for triangular elements. There are different classes for storing
//               variables at node and element level.
//==================================================================================================

#ifndef TRI_H_
#define TRI_H_

#include "settings.h"

/*!
 * \brief This class defines LINEAR TRIANGULAR MASTER ELEMENT.
 * 
 * In the mesh, there are elements with different sizes and shapes. Instead of integrating the 
 * equations on each element, we use a reference element, which simplifies the integration.
 * Note that the reference element is same for all the elements in the mesh.
 */
class triMasterElement
{
    private:
        /// PRIVATE VARIABLES
        double point[2];    // ksi and eta for each GQ point
        double weight;      // weight of each GQ point
        double S[3];        // Shape functions
        double dSdKsi[3];   // ksi derivatives of shape functions
        double dSdEta[3];   // eta derivatives of shape functions
        
    protected:

    public:
        /// DEFAULT CONSTRUCTOR
        triMasterElement(){};

        /// DESTRUCTOR
        ~triMasterElement(){};

        /// GETTERS
        double getPoint(int i)  {return point[i];};
        double getWeight()      {return weight;};
        double getS(int i)      {return S[i];};
        double getDSdKsi(int i) {return dSdKsi[i];};    
        double getDSdEta(int i) {return dSdEta[i];};    

        /// PUBLIC INTERFACE METHODS
        void setupGaussQuadrature();
        void evaluateShapeFunctions();
};


/*!
 * \brief This class defines NODE LEVEL DATA STRUCTURE.
 *
 * This data structure holds any kind of variable that are defined at node points.
 * These variables can be x,y coordinates, temperature values or any other value that is necessary
 * during the solution stage. 
 */
class triNode
{
    private:
        /// PRIVATE VARIABLES
        double x;   // x-coordinate
        double y;   // y-ccordinate
        double T;   // Temperature
	int BC_type;// assign boundary type if it is boundary node

        // maybe some more variables can be necessary for the solver ?

    protected:

    public:
        /// DEFAULT CONSTRUCTOR
        triNode(){x=0.0f; y=0.0f; T=0.0f; BC_type=0;};

        /// DESTRUCTOR
        ~triNode(){};

        /// SETTERS
        void setX  	(double value) {x = value;};
        void setY  	(double value) {y = value;};
        void setT  	(double value) {T = value;};
        void setBC_type (int value)    {BC_type = value;};

        /// GETTERS
        double getX()    {return x;};
        double getY()    {return y;};
        double getT()    {return T;};
        int getBC_type() {return BC_type;};
};


/*!
 * \brief This class defines ELEMENT LEVEL DATA STRUCTURE.
 * 
 * This data structure holds the variables determined for an element.
 * An element have a connectivity (the node numbers of the element) and face groups which indicates
 * which face has which boundary condition type. Other than these you will need to define element
 * mass stiffness matrices or any other matrices that will be necessary during the solution stage.
 */
class triElement
{
    private:
        /// PRIVATE VARIABLES
        int conn[nen];
        int FG[nef];
	double J[4];
	double J_inv[4];
	double det_J_abs;
	double K[9];
	double M[3];
	double F[3];
	double B[3];
	double RHS[3];
        // and some more variables that you will need during the solution stage...

    protected:

    public:
        /// DEFAULT CONSTRUCTOR
        triElement(){ B[0]=0.0f; B[1]=0.0f; B[2]=0.0f; };

        /// DESTRUCTOR
        ~triElement(){};

        /// SETTERS

        void setConn (int i, int value) {conn[i] = value;};
        void setFG   (int i, int value) {FG[i] = value;};
        void setJ    (double* value) 	{std::memcpy(J,value,4*sizeof(double));};
        void setJinv (double* value) 	{std::memcpy(J_inv,value,4*sizeof(double));};
        void setDetJ (double value) 	{det_J_abs = value;};
        void setK    (double* value) 	{std::memcpy(K,value,9*sizeof(double));};
        void setM    (double* value) 	{std::memcpy(M,value,9*sizeof(double));};
        void setF    (double* value) 	{std::memcpy(F,value,3*sizeof(double));};
        void setB    (double* value) 	{std::memcpy(B,value,3*sizeof(double));};
        void setRHS    (double* value) 	{std::memcpy(RHS,value,3*sizeof(double));};

        /// GETTERS

        int  getConn (int index) {return conn[index];};
        int  getFG   (int index) {return FG[index];}
        double* getJ () 	 {return J;};
        double* getJinv () 	 {return J_inv;};
        double getDetJ () 	 {return det_J_abs;};
        double* getK ()		 {return K;};
        double* getM ()		 {return M;};
        double* getF ()		 {return F;};
        double* getB ()		 {return B;};
        double* getRHS ()	 {return RHS;};
};


/*!
 * \brief This class defines MESH DATA STRUCTURE.
 * 
 * This class is used to keep the pointers to node and element data structures. It is more
 * convinient to pass the pointer to this class rather than passin the pointers to both element and
 * node arrays during function calls. So it is just for simplification.
 */
class triMesh
{
    private:
        /// PRIVATE VARIABLES
        int ne;                     // total number of elements
        int nn;                     // number of nodes
        triNode*            node;   // pointer for node level data structure
        triElement*         elem;   // pointer for element level data structure
        triMasterElement*   ME;     // pointer for reference element

        /// PRIVATE METHODS
        void swapBytes(char*, int, int);
        
    protected:

    public:
        /// DEFAULT CONSTRUCTOR
        triMesh(){};

        /// DESTRUCTOR       
        ~triMesh()
        {
            delete[] node;
            delete[] elem;
            delete[] ME;
        };

        /// GETTERS

        int                 getNe()             {return ne;};
        int                 getNn()             {return nn;};
        triNode*            getNode (int index) {return &node[index];};
        triElement*         getElem (int index) {return &elem[index];};
        triMasterElement*   getME   (int index) {return &ME[index];};

        /// PUBLIC INTERFACE METHOD
        void readMeshFiles(inputSettings*);
        void writeDataFile(inputSettings*);
};


#endif /* TRI_H_ */
