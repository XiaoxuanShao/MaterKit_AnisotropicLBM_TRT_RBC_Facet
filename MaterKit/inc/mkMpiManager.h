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
#ifndef CFS_MPI_MANAGER_H
#define CFS_MPI_MANAGER_H

#include "mkGlobalDefs.h"

#ifdef CFS_MPI_PARALLEL
#include "mpi.h"
#include <vector>
#include <string>
#endif

namespace mkt {

namespace global {

#ifdef MK_MPI_PARALLEL

/// Wrapper functions that simplify the use of MPI
class MpiManager {
public:
    /// Initializes the MPI manager and the MPI machine.
    void init(int *argc, char ***argv, bool verbous=false);
    /// Initializes the MPI manager, but assumes that the MPI
    ///   machine is handled by another instance.
    void init(MPI_Comm globalCommunicator_);
    /// Initializes the MPI manager, but assumes that the MPI
    ///   machine is handled by another instance.
    void init();
    /// Returns the number of processes
    int getSize() const;
    /// Returns the process ID
    int getRank() const;
    /// Returns process ID of main processor
    int bossId() const;
    /// Tells whether current processor is main processor
    bool isMainProcessor() const;
    /// Returns universal MPI-time in seconds
    double getTime() const;
    /// Returns the global communicator for this program or library instance.
    MPI_Comm getGlobalCommunicator() const;

    /// Synchronizes the processes
    void barrier();

    /// Sends data at *buf, blocking
    template <typename T>
    void send( T *buf, int count, int dest, int tag = 0 );

    /// Sends data at *buf, non blocking
    template <typename T>
    void iSend( T *buf, int count, int dest, MPI_Request* request, int tag = 0 );

    /// Sends data at *buf, assuming that receiver is ready.
    template <typename T>
    void rSend( T *buf, int count, int dest, int tag = 0 );

    /// Sends data at *buf, non blocking and request free
    template <typename T>
    void iSendRequestFree( T *buf, int count, int dest, int tag = 0 );

    /// Receives data at *buf, blocking
    template <typename T>
    void receive( T *buf, int count, int source, int tag = 0 );

    /// Receives data at *buf, non blocking
    template <typename T>
    void iRecv( T *buf, int count, int source, MPI_Request* request, int tag = 0 );

    /// Send and receive data between two partners
    template <typename T>
    void sendRecv( T *sendBuf, T *recvBuf, int count, int dest,
                   int source, int tag = 0 );

    /// Sends data to master processor
    template <typename T>
    void sendToMaster( T* sendBuf, int sendCount, bool iAmRoot );

    /// Scatter data from one processor over multiple processors
    template <typename T>
    void scatterV( T *sendBuf, T *recvBuf, int* sendCounts, int root = 0 );

    /// Gather data from multiple processors to one processor
    template <typename T>
    void gatherV( T* sendBuf, T* recvBuf, int *recvCounts, int root = 0 );


    /// Broadcast data from one processor to multiple processors
    template <typename T>
    void bCast( T* sendBuf, int sendCount, int root = 0 );

    /// Special case for broadcasting strings. Memory handling is automatic.
    void bCast( std::string& message, int root = 0 );

    /// Broadcast data when root is unknown to other processors
    template <typename T>
    void bCastThroughMaster( T* sendBuf, int sendCount, bool iAmRoot );

    /// Reduction operation toward one processor
    template <typename T>
    void reduce( T sendVal, T& recvVal, MPI_Op op, int root = 0 );

    /// Element-per-element reduction of a vector of data
    template <typename T>
    void reduceVect( std::vector<T>& sendVal, std::vector<T>& recvVal,
                     MPI_Op op, int root = 0 );

    /// Inplace element-per-element reduction of a vector of data; result
    ///   available on all MPI threads.
    template <typename T>
    void allReduceVect( std::vector<T>& sendRecvVal, MPI_Op op );

    /// Reduction operation, followed by a broadcast
    template <typename T>
    void reduceAndBcast(T& reductVal, MPI_Op op, int root = 0 );

    /// Complete a non-blocking MPI operation
    void wait(MPI_Request* request, MPI_Status* status);

private:
    /// Implementation code for Scatter
    template <typename T>
    void scatterv_impl(T *sendBuf, int* sendCounts, int* displs,
                       T* recvBuf, int recvCount, int root);

    /// Implementation code for Gather
    template <typename T>
    void gatherv_impl(T* sendBuf, int sendCount, T* recvBuf, int* recvCounts,
                      int* displs, int root);
private:
    MpiManager();
    ~MpiManager();
private:
    int numTasks, taskId;
    bool ok;
    bool responsibleForMpiMachine;
    MPI_Comm globalCommunicator;

friend MpiManager& mpi();
};

#else  // #ifdef MK_MPI_PARALLEL

class MpiManager {
public:
    /// Initializes the mpi manager
    void init(int *argc, char ***argv, bool verbous=false) { }
    /// Initializes the MPI manager, but assumes that the MPI
    ///   machine is handled by another instance.
    void init() { }
    /// Returns the number of processes
    int getSize() const { return 1; }
    /// Returns the process ID
    int getRank() const { return 0; }
    /// Returns process ID of main processor
    int bossId() const { return 0; }
    /// Tells whether current processor is main processor
    bool isMainProcessor() const { return true; }
    /// Broadcast data from one processor to multiple processors
    template <typename T>
    void bCast(T* sendBuf, int sendCount, int root = 0) { }
    /// Special case for broadcasting strings. Memory handling is automatic.
    void bCast(std::string& message, int root = 0) { }
    /// Synchronizes the processes
    void barrier() { }

friend MpiManager& mpi();
};

#endif  // CFS_MPI_PARALLEL

inline MpiManager& mpi() {
    static MpiManager instance;
    return instance;
}

}  // namespace global

}  // namespace mkt


#endif  // MPI_MANAGER_H
