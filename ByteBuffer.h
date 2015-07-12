#ifndef ByteBuffer_h
#define ByteBuffer_h

#define BYTEBUFFER_MAX_SIZE 64

class ByteBuffer
{
  public:
    void push(char latestByte);
    void empty();
    unsigned int getSize();
    char getByte(unsigned int idx);
    void asString(char * result);
  private:
    char buffer[BYTEBUFFER_MAX_SIZE];
    unsigned int bufferSize = 0;
};

#endif
