#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>

#ifndef BUFFER_SIZE
	#define BUFFER_SIZE 16
#endif //BUFFER_SIZE

#ifndef BUFFER_SIZE_TYPE
	#define BUFFER_SIZE_TYPE uint8_t
#endif //BUFFER_SIZE_TYPE

enum BufferStatus
{
	BUFFERSTATUS_OK,
	BUFFERSTATUS_FULL,
	BUFFERSTATUS_EMPTY
};

class Buffer
{
	uint8_t *buffer;
	uint8_t begin;
	uint8_t end;	
	
public:
	Buffer();
	virtual ~Buffer(){ delete[] buffer; }
	
	BUFFER_SIZE_TYPE length() volatile;
	
	BufferStatus read(uint8_t *byte) volatile;
	BufferStatus write(uint8_t byte) volatile;
	BufferStatus status() volatile;
	
	uint8_t *content() volatile;
};



#endif //BUFFER_H
