#include "buffer.h"

Buffer::Buffer()
{
	begin = 0;
	end = 0;
	buffer = new uint8_t[BUFFER_SIZE];
}


BUFFER_SIZE_TYPE Buffer::length() volatile
{
	return (end - begin + BUFFER_SIZE) % BUFFER_SIZE;
}


BufferStatus Buffer::read(uint8_t *byte) volatile
{
	if (status() == BUFFERSTATUS_EMPTY) return BUFFERSTATUS_EMPTY;
  
	*byte = buffer[begin];
	begin = (begin + 1) % BUFFER_SIZE;
        
	return BUFFERSTATUS_OK;
}


BufferStatus Buffer::write(uint8_t byte) volatile 
{
	uint8_t next = (end + 1) % BUFFER_SIZE;
        
  if (status() == BUFFERSTATUS_FULL) return BUFFERSTATUS_FULL;
        
  buffer[end] = byte;
  end = next;
        
  return BUFFERSTATUS_OK;
}


BufferStatus Buffer::status() volatile
{
	if (begin == end) return BUFFERSTATUS_EMPTY;
	
	uint8_t next = (end + 1) % BUFFER_SIZE;
	if (next == begin) return BUFFERSTATUS_FULL;
	
	return BUFFERSTATUS_OK;
}

uint8_t *Buffer::content() volatile
{
  uint8_t *bufferContent = new uint8_t [BUFFER_SIZE];
    
  BUFFER_SIZE_TYPE index = 0;
  uint8_t byte;
    
  while (read(&byte) != BUFFERSTATUS_EMPTY)
		bufferContent[index++] = byte;
    
  return bufferContent;
}
