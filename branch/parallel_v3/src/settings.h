//==================================================================================================
// Name        : settings.h
// Author      : Raghavan Lakshmanan
// Version     : 1.0
// Copyright   : See the copyright notice in the README file.
// Description : This file contains the classes for boundary conditions and settings read from file.
//==================================================================================================

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "constants.h"

//==================================================================================================
// class bndc ==> BOUNDARY CONDITION SPECIFICATION CLASS
//==================================================================================================
class bndc
{
    private:
        friend class inputSettings;
        int BCType;
        double BCValue;
        double HTC;  // Heat transfer coefficient only for mixed boundary conditions

    protected:
        
    public:
        ///DEFAULT CONSTRUCTOR
        bndc(){};

        ///SETTERS
        void setType    (int value)     {BCType = value;};
        void setValue   (double value)  {BCValue = value;};
        void setHTC     (double value)  {HTC = value;};

        ///GETTERS
        int     getType()   {return BCType;};
        double  getValue()  {return BCValue;};
        double  getHTC()    {return HTC;};
};


//==================================================================================================
//class inputSettings ==> SETTINGS DATA STRUCTURE
//==================================================================================================
// Input parameters are stored in this class. readSettingsFile() method does the job: It opens the
// settings.in file, reads the parameters and assigns them to the private variables.
//==================================================================================================
class inputSettings
{
    private:
        /// PRIVATE VARIABLES
        string  title;      // title of the document
        string	wdir;	    // working directory
        string  minfFile;   // information file name
        string  mxyzFile;   // node coordinates file name
        string  mienFile;   // connctivity file name
        string  mrngFile;   // boundary info file name
        string  dataFile;   // data file name
        string  mprmFile;   // element permutation file name
        string  nprmFile;   // node permutation file name
        double  initT;      // initial value of the temperature
        double  D;          // Diffusion coefficient
        double  source;     // Heat source term
        int     nIter;      // number of maximum time steps
        double  dt;         // time step size
        int     dwf;        // Data write frequency
        bndc    BC[5];      // 5 face groups (4 side edges and one for internal nodes)

       
        
    protected:

    public:
        /// DEFAULT CONSTRUCTOR ///
        inputSettings();

        /// DESTRUCTOR
        ~inputSettings(){};

        /// GETTERS ///  
        string          getTitle()      {return title;};
        string          getWdir()       {return wdir;};
        string          getMinfFile()   {return minfFile;};
        string          getMxyzFile()   {return mxyzFile;};
        string          getMienFile()   {return mienFile;};
        string          getMrngFile()   {return mrngFile;};
        string          getDataFile()   {return dataFile;};
        string          getMprmFile()   {return mprmFile;};
        string          getNprmFile()   {return nprmFile;};
        double          getInitT()      {return initT;};
        double          getD()          {return D;};
        double          getSource()     {return source;};
        bndc*           getBC(int i)    {return &BC[i];};
        int             getNIter()      {return nIter;};
        double          getDt()         {return dt;};
        int             getDwf()        {return dwf;};

        /// PUBLIC INTERFACE METHOD
        void readSettingsFile();
};



#endif /* SETTINGS_H_ */
