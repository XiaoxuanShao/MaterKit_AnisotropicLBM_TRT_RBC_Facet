//============================================================================
//              Anisotropic LBM 3D code
//============================================================================
// Author      : DongKe SUN
// Version     : 2010.09.30 MoonLight
// Copyright   : All rights reserved.
// Description : C++, Ansi-style
// Last updated: 2021.01.28 by DongKe SUN
//============================================================================
// SUN DongKe, Ph.D
// Website     : http://www.materkit.com
// E-Mail      : dksun@seu.edu.cn 
//============================================================================

#ifndef MK_XML_IO_H
#define MK_XML_IO_H

#include <string>
#include <vector>
#include <map>
#include "tinyxml.h"
#include "mkTriangleSet.h"

#include "MaterKit.h"

namespace mkt {

class MK_API XMLreader;
class MK_API XMLreaderProxy;
class MK_API XMLwriter;

class XMLreader {
public:
    XMLreader( std::string fName );
    XMLreader( std::vector<TiXmlNode*> pParentVect );
    ~XMLreader();
    void print(int indent) const;
    XMLreaderProxy operator[] (std::string name) const;
    XMLreaderProxy getElement(std::string name, int id) const;
    std::string getName() const;
    std::string getText() const;
    std::string getText(int id) const;
    int getFirstId() const;
    std::string getFirstText() const;
    bool idExists(int id) const;
    bool getNextId(int& id) const;
    std::vector<XMLreader*> const& getChildren(int id) const;
private:
    void mainProcessorIni(TiXmlNode* pParent);
    void mainProcessorIni(std::vector<TiXmlNode*> pParentVect);
    void slaveProcessorIni();
    XMLreader();
private:
    struct Data {
        std::string text;
        std::vector<XMLreader*> children;
    };
private:
    std::string name;
    std::map<int,Data> data_map;
    //static XMLreader notFound;
};

class XMLreaderProxy {
public:
    XMLreaderProxy(XMLreader const* reader_);
    XMLreaderProxy(XMLreader const* reader_, int id_);
    template <typename T> void read(T& values) const;
    template <typename T> bool readNoThrow(T& values) const;
    template <typename T> void read(std::vector<T>& values) const;
    template <typename T> bool readNoThrow(std::vector<T>& values) const;
    template <typename T, int N> void read(Array<T,N>& values) const;
    template <typename T, int N> bool readNoThrow(Array<T,N>& values) const;
    XMLreaderProxy operator[] (std::string name) const;
    XMLreaderProxy operator[] (int newId) const;
    bool isValid() const;
    int getId() const;
    XMLreaderProxy iterId() const;
    std::string getName() const;
    std::vector<XMLreader*> const& getChildren() const;
private:
    XMLreader const* reader;
    int id;
};

class XMLwriter {
public:
    XMLwriter();
    ~XMLwriter();
    template<typename T> void set(T const& value);
    void setString(std::string const& value);
    template<typename T> void set(std::vector<T> const& values);
    template<typename T, int N> void set(Array<T,N> const& values);
    XMLwriter& operator[] (std::string name);
    XMLwriter& operator[] (int id);
    template<typename ostrT>
    void toOutputStream(ostrT& ostr, int indent=0) const;
    void print(std::string fName) const;
private:
    XMLwriter( std::string name_ );
private:
    struct Data {
        std::string text;
        std::vector<XMLwriter*> children;
    };
private:
    bool isDocument;
    std::string name;
    std::map<int,Data> data_map;
    int currentId;
};

}  // namespace mk

#endif  // XML_IO_H
