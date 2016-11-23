/**
 * @file    CShmChunk.h
 * @brief   共享内存类型Chunk头文件
 * @note
 *
 * CShmChunk是基于共享内存的IChunk实现类。\n
 *
 * @author  guoyue
 * @version 1.0
 * @date    2013-3-5
 * @bug     无
 * @warning 无
 */
#ifndef CSHMCHUNK_H_
#define CSHMCHUNK_H_

#include "CChunk.h"

/**
 * @class CShmChunk CShmChunk.h "\source\dce\src\main\util\shm\CShmChunk.h"
 * @brief 共享内存类型Chunk.
 * @note
 * CShmChunk是基于共享内存的IChunk实现类。其内部维护了一个共享内存环境管理区结构体。\n
 */
class CShmChunk: public CChunk
{
public:

    /** @brief CShmChunk构造函数*/
    CShmChunk();

    /** @brief CShmChunk析构函数*/
    virtual ~CShmChunk();

    /** @brief 根据传入的偏移位置计算相对于共享内存基地址的偏移指针*/
    virtual void* getPtr(shm_offset_t offset = 0);

    /** @brief 根据传入的偏移指针计算相对于共享内存基地址的偏移位置*/
    virtual shm_offset_t getOffset(void* ptr);

    /** @brief 取出整个共享内存Chunk长度*/
    virtual shm_size_t getChunkSize();

    /** @brief 取出共享内存Chunk已使用长度*/
    virtual shm_size_t getChunkUsed();

    /** @brief 取出共享内存Chunk剩余可使用长度*/
    virtual shm_size_t getChunkFree();

    /** @brief 设置共享内存Chunk已使用长度*/
    virtual void setChunkUsed(shm_size_t chunkUsed);

    /** @brief 设置整个共享内存Chunk长度*/
    virtual void setChunkSize(shm_size_t chunkSize);

    /** @brief 设置共享内存基地址指针*/
    virtual void setBasePtr(void *ptrShm);

    /** @brief 构造读写器*/
    virtual IReader *buildReader();

    /** @brief 构造管理区*/
    virtual IHash *buildChunk(shm_size_t shmSize);

    /** @brief 重建管理区*/
    virtual IHash *rebuildChunk();

    /** @brief 构造资源分配器*/
    virtual IAlloctor *buildAlloctor();

protected:
    char *ptrBase;		///<共享内存基地址指针

};

#endif /* CSHMCHUNK_H_ */
