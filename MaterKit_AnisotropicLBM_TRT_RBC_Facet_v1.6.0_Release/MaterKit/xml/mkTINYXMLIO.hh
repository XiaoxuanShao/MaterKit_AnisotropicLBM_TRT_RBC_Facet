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
#pragma once
#ifndef MK_XML_IO_HH
#define MK_XML_IO_HH

#include "mkTINYXMLIO.h"
#include "mkRunTimeDiagnostics.h"
#include "mkMpiManager.h"
#include <typeinfo>
#include <cctype>

#include <streambuf>
#include <istream>
#include <ostream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <algorithm>

namespace mkt {

template <typename T>
void XMLreaderProxy::read(T& value) const {
    if (!reader) return;
    std::stringstream valueStr(reader->getText(id));
    T tmp = T();
    if (!(valueStr>>tmp)) {
        mkIOError(std::string("Cannot read value from XML element ") + reader->getName());
    }
    value = tmp;
}
//2014.06.28 dongke
inline std::string tolower(std::string arg) {
    std::string result(arg.size(), ' ');
    std::transform(arg.begin(), arg.end(), result.begin(), ::tolower);
    return result;
}
//2014.06.28 dongke
inline std::string toupper(std::string arg) {
    std::string result(arg.size(), ' ');
    std::transform(arg.begin(), arg.end(), result.begin(), ::toupper);
    return result;
}

template <>
inline void XMLreaderProxy::read<bool>(bool& value) const {
    if (!reader) return;
    std::stringstream valueStr(reader->getText(id));
    std::string word;
    valueStr >> word;
    // Transform to lower-case, so that "true" and "false" are case-insensitive.
//    word = util::tolower(word);//2014.06.28 dongke
    word = tolower(word);
    if (word=="true") {
        value = true;
    }
    else if (word=="false") {
        value=false;
    }
    else {
        mkIOError(std::string("Cannot read boolean value from XML element ") + reader->getName());
    }
}

template <>
inline void XMLreaderProxy::read<std::string>(std::string& entry) const {
    if (!reader) return;
    entry = reader->getText(id);
}

template <typename T>
bool XMLreaderProxy::readNoThrow(T& value) const {
    if (!reader) return false;
    std::stringstream valueStr(reader->getText(id));
    T tmp = T();
    if (!(valueStr >> tmp)) {
        return false;
    }
    value = tmp;
    return true;
}

template <>
inline bool XMLreaderProxy::readNoThrow<bool>(bool& value) const {
    if (!reader) return false;
    std::stringstream valueStr(reader->getText(id));
    std::string word;
    valueStr >> word;
    // Transform to lower-case, so that "true" and "false" are case-insensitive.
//    word = util::tolower(word);//2014.06.28 dongke
    word = tolower(word);
    if (word=="true") {
        value = true;
        return true;
    }
    else if (word=="false") {
        value=false;
        return true;
    }
    return false;
}

template <>
inline bool XMLreaderProxy::readNoThrow<std::string>(std::string& entry) const {
    if (!reader) return false;
    entry = reader->getText(id);
    return true;
}

template <typename T>
void XMLreaderProxy::read(std::vector<T>& values) const {
    if (!reader) return;
    std::stringstream multiValueStr(reader->getText(id));
    std::string word;
    std::vector<T> tmp(values);
    while (multiValueStr>>word) {
        std::stringstream valueStr(word);
        T value;
        if (!(valueStr >> value)) {
            mkIOError(std::string("Cannot read value array from XML element ") + reader->getName());
        }
        tmp.push_back(value);
    }
    values.swap(tmp);
}

template <typename T>
bool XMLreaderProxy::readNoThrow(std::vector<T>& values) const {
    if (!reader) return false;
    std::stringstream multiValueStr(reader->getText(id));
    std::string word;
    std::vector<T> tmp(values);
    while (multiValueStr>>word) {
        std::stringstream valueStr(word);
        T value;
        if (!(valueStr >> value)) {
            return false;
        }
        tmp.push_back(value);
    }
    values.swap(tmp);
    return true;
}

//template <typename T, int N>
//void XMLreaderProxy::read(Array<T,N>& values) const {
//    if (!reader) return;
//    std::stringstream multiValueStr(reader->getText(id));
//    std::string word;
//    values.resetToZero();
//    int i=0;
//    while (multiValueStr>>word && i<N) {
//        std::stringstream valueStr(word);
//        T value;
//        if (!(valueStr >> value)) {
//            mkIOError(std::string("Cannot read value array from XML element ") + reader->getName());
//        }
//        values[i] = value;
//        ++i;
//    }
//}

//template <typename T, int N>
//bool XMLreaderProxy::readNoThrow(Array<T,N>& values) const {
//    if (!reader) return false;
//    std::stringstream multiValueStr(reader->getText(id));
//    std::string word;
//    int i=0;
//    while (multiValueStr>>word && i<N) {
//        std::stringstream valueStr(word);
//        T value;
//        if (!(valueStr >> value)) {
//            return false;
//        }
//        values[i] = value;
//        ++i;
//    }
//    return true;
//}

template<typename T> void XMLwriter::set(T const& value)
{
    std::stringstream valuestr;
    valuestr << value;
    valuestr >> data_map[currentId].text;
}

template<typename T> void XMLwriter::set(std::vector<T> const& values)
{
    std::stringstream valuestr;
    for (pluint i=0; i<values.size(); ++i) {
        if (i != 0) {
            valuestr << " ";
        }
        valuestr << values[i];
    }
    data_map[currentId].text = valuestr.str();
}

//template<typename T, int N> void XMLwriter::set(Array<T,N> const& values)
//{
//    std::stringstream valuestr;
//    for (pluint i=0; i<N; ++i) {
//        if (i != 0) {
//            valuestr << " ";
//        }
//        valuestr << values[i];
//    }
//    data_map[currentId].text = valuestr.str();
//}

template<> inline void XMLwriter::set<bool>(bool const& value)
{
    if (value) {
        data_map[currentId].text = "True";
    }
    else {
        data_map[currentId].text = "False";
    }
}

template<typename ostrT>
void XMLwriter::toOutputStream(ostrT& ostr, int indent) const {
    if (!global::mpi().isMainProcessor()) return;
    if (data_map.empty()) return;

    if (isDocument) {
        ostr << "<?xml version=\"1.0\" ?>\n";
        std::vector<XMLwriter*> const& children = data_map.begin()->second.children;
        for (pluint iNode=0; iNode<children.size(); ++iNode) {
            children[iNode]->toOutputStream(ostr);
        }
    }
    else {
        std::map<int,Data>::const_iterator it = data_map.begin();
        for (; it != data_map.end(); ++it) {
            std::vector<XMLwriter*> const& children = it->second.children;
            std::string const& text = it->second.text;
            std::string indentStr(indent, ' ');
            ostr << indentStr << "<" << name;
            if (data_map.size()>1 || it->first!=0) {
                ostr << " id=\"" << it->first << "\"";
            }
            if (children.empty()) {
                ostr << ">";
            }
            else {
                ostr << ">\n";
            }
            if (!text.empty()) {
                if (children.empty()) {
                    ostr << " " << text << " ";
                }
                else {
                    ostr << indentStr << "    " << text << "\n";
                }
            }
            for (pluint iNode=0; iNode<children.size(); ++iNode) {
                children[iNode]->toOutputStream(ostr, indent+4);
            }
            if (!children.empty()) {
                ostr << indentStr;
            }
            ostr << "</" << name << ">\n";
        }
    }
}

}  // namespace mkt

#endif  // XML_IO_HH
