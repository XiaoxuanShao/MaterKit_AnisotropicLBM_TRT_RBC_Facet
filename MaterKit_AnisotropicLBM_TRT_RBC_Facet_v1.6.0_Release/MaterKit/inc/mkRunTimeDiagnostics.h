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
#ifndef MK_RUN_TIME_DIAGNOSTICS_H
#define MK_RUN_TIME_DIAGNOSTICS_H

#include "MaterKit.h"
#include "mkGlobalDefs.h"
#include "mkMpiManager.h"
#include <string>
#include <fstream>
#include <exception>

namespace mkt {

class DiagnosticFileSingleton {
public:
    DiagnosticFileSingleton(std::string fName_);
    ~DiagnosticFileSingleton();
    void write(std::string message);
private:
    DiagnosticFileSingleton();
    std::ofstream* ofile;
    std::string fName;
};

DiagnosticFileSingleton& warningFile();

/// Invoke this function on all processes. If one process yields true,
///   a warning is issued to the warning file.
void mkWarning(bool issueWarning, std::string message);

/// Invoke this function at least on main process. If the main process
///  yields true, a warning is issued to the warning file.
void mkWarning(std::string message);

/// Invoke this function on all processes. If one process yields true,
///   all processes launch an exception.
void mkMemoryError(bool issueError, std::string message);

/// Invoke this function on all processes. All processes must agree on the
///   fact that there is an error.
void mkMemoryError(std::string message);

/// Invoke this function on all processes. The main process decides if
///   there is an error or not.
void mkMainProcMemoryError(bool issueError, std::string message);

MK_API void mkIOError(bool issueError, std::string message);
MK_API void mkIOError(std::string message);
MK_API void mkMainProcIOError(bool issueError, std::string message);

MK_API void mkNetworkError(bool issueError, std::string message);
MK_API void mkNetworkError(std::string message);
MK_API void mkMainProcNetworkError(bool issueError, std::string message);

void mkLogicError(bool issueError, std::string message);
void mkLogicError(std::string message);
void mkMainProcLogicError(bool issueError, std::string message);

class mkException : public std::exception
{ };

class mkMemoryException : public mkException {
public:
    mkMemoryException(std::string message_) throw();
    virtual ~mkMemoryException() throw() { }
    virtual const char* what() const throw();
private:
    std::string message;
};

class mkIOException : public mkException {
public:
    mkIOException(std::string message_) throw();
    virtual ~mkIOException() throw() { }
    virtual const char* what() const throw();
private:
    std::string message;
};

class mkNetworkException : public mkException {
public:
    mkNetworkException(std::string message_) throw();
    virtual ~mkNetworkException() throw() { }
    virtual const char* what() const throw();
private:
    std::string message;
};

class mkLogicException : public mkException {
public:
    mkLogicException(std::string message_) throw();
    virtual ~mkLogicException() throw() { }
    virtual const char* what() const throw();
private:
    std::string message;
};

class mkOutOfRangeException : public mkException {
public:
    mkOutOfRangeException(std::string message_) throw();
    virtual ~mkOutOfRangeException() throw() { }
    virtual const char* what() const throw();
private:
    std::string message;
};

}  // namespace mkt

#endif  // RUN_TIME_DIAGNOSTICS_H
