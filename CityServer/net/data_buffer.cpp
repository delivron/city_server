#include "data_buffer.h"

using namespace std;
using namespace net;
using namespace boost::asio;

DataBuffer::DataBuffer() {
    _writingPointer = 0;
    _readingPointer = 0;
    _capacity = 32;
    _data = shared_ptr<uint8_t[]>(new uint8_t[_capacity]);
}

size_t DataBuffer::getSize() const noexcept {
    return _writingPointer;
}

size_t DataBuffer::getAvailable() const noexcept {
    return _writingPointer - _readingPointer;
}

mutable_buffer DataBuffer::getBuffer() const {
    return buffer(&_data[0], getSize());
}

void DataBuffer::resetReadingPointer() noexcept {
    _readingPointer = 0;
}

void DataBuffer::resetWritingPointer() noexcept {
    _writingPointer = 0;
}

void DataBuffer::resetPointers() noexcept {
    resetReadingPointer();
    resetWritingPointer();
}

void DataBuffer::resize(size_t newCapacity) {
    if (newCapacity == 0) {
        return;
    }

    auto oldData = _data;
    _data = shared_ptr<uint8_t[]>(new uint8_t[newCapacity]);

    size_t bytesToCopy = min(_writingPointer, newCapacity);
    memcpy(&_data[0], &oldData[0], bytesToCopy);

    _capacity = newCapacity;
    correctPointer(_writingPointer);
    correctPointer(_readingPointer);
}

void DataBuffer::writeBytes(const void* bytes, size_t bytesCount) {
    resizeIfNeed(bytesCount);

    memcpy(&_data[_writingPointer], bytes, bytesCount);

    _writingPointer += bytesCount;
}

void DataBuffer::writeFromSocket(const TcpSocketPtr& socket, size_t bytesCount) {
    size_t bytesToWrite = min(socket->available(), bytesCount);
    resizeIfNeed(bytesToWrite);

    socket->read_some(buffer(&_data[_writingPointer], bytesToWrite));

    _writingPointer += bytesToWrite;
}

void DataBuffer::resizeIfNeed(size_t addBytes) {
    size_t resultSize = _writingPointer + addBytes;
    if (resultSize > _capacity) {
        resize(max(2 * _capacity, resultSize));
    }
}

void DataBuffer::correctPointer(size_t& pointer) noexcept {
    if (pointer > _capacity) {
        pointer = _capacity;
    }
}
