#include "ByteBuffer.h"

void ByteBuffer::push(char latestByte) {
  // Add the byte to the buffer and increment the count
  buffer[bufferSize] = latestByte;
  bufferSize++;

  // If we're greater than BYTEBUFFER_MAX_SIZE 
  // we're going to overflow so just go back to the beginning
  if(bufferSize > BYTEBUFFER_MAX_SIZE) {
    bufferSize = 0;
  }
}

void ByteBuffer::empty() {
  // Clear the buffer
  for(unsigned int i = 0; i < BYTEBUFFER_MAX_SIZE; i++)
  {
    buffer[i] = 0;
  }

  bufferSize = 0;
}

unsigned int ByteBuffer::getSize() {
  return bufferSize;
}

char ByteBuffer::getByte(unsigned int idx) {
  if(idx <= BYTEBUFFER_MAX_SIZE) {
    return buffer[idx];
  } else {
    return 0;
  }
}

void ByteBuffer::asString(char * result) {
  for(int i = 0; i < bufferSize; i++) {
    result[i] = buffer[i];
  }

  result[bufferSize] = '\0';
}

