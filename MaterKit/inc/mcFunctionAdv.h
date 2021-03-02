//========================================================//
// Author      : SUN DongKe                               //
// Copyright   : All rights reserved.                     //
// Description : C++, Ansi-style                          //
// Last updated: 2013.12.21 by SUN DongKe                 //
//========================================================//
// SUN DongKe, Ph.D                                       //
// E-Mail      : sundongke@gmail.com                      //
//========================================================//
#ifndef MK_FUNCTIONADV_H
#define MK_FUNCTIONADV_H

#include "mkGlobalDefs.h"
#include "cfsTINYXML_xmlIO.h"
#include "cfsTINYXML_xmlIO.hh"

namespace mkt
{
	using namespace std;
	using namespace cfs;

	extern const double epsilon;
	extern const string paraXmlFileName;
	extern const XMLreader document_para;

	extern void alarm(const int times);

	extern int  str_erase(string &str, const string src);
	extern int  str_replace(string &str, const string &src, const string &dest);
	extern bool folder_exist(const string &strPath);
	extern bool dir_exists(const string& dirName_in);

	extern bool search_elements(vector<string> & target_element);
	extern bool create_batchfiles(const string * result_pname, const string * sample_fname );

	extern void IterativeNestedLoop(const int depth, const int max);

	extern void create_possible_component_1(vector<vector<double > > & X_target, vector<vector<double > > & X_range, int N);
	extern int  create_possible_component_2(vector<vector<double > > & X_target, vector<vector<double > > & X_range, int N_element);

	extern bool vectors_are_equal(vector<double> & vector_lhs, vector<double> vector_rhs);
	extern void clear_redundance_compoents(vector<vector<double > > & X_target);

	extern void create_reasonable_component(vector<vector<double > > & X_target, vector<vector<double > > & X_range, int N);
}
#endif
