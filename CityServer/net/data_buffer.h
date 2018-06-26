#pragma once

#include <memory>
#include <cstdint>

#include <boost/asio.hpp>

#include "net_types.h"

namespace net {

    class DataBuffer {
    public:
        DataBuffer();

        size_t                              getSize() const noexcept;
        size_t                              getAvailable() const noexcept;
        boost::asio::mutable_buffer         getBuffer() const;
        void                                resetReadingPointer() noexcept;
        void                                resetWritingPointer() noexcept;
        void                                resetPointers() noexcept;
        void                                resize(size_t newCapacity);
        void                                writeBytes(const void* bytes, size_t bytesCount);
        void                                writeFromSocket(const TcpSocketPtr& socket, size_t bytesCount);

        template<typename T>
        void                                write(const T& value);
        
        template<typename T>
        void                                read(T& value);
        
    private:
        void                                resizeIfNeed(size_t addBytes);
        void                                correctPointer(size_t& pointer) noexcept;

        std::shared_ptr<uint8_t[]>          _data;
        size_t                              _writingPointer;
        size_t                              _readingPointer;
        size_t                              _capacity;
    };

    using DataBufferPtr                     = std::shared_ptr<DataBuffer>;

    template<typename T>
    void DataBuffer::write(const T& value) {
        writeBytes(&value, sizeof(T));
    }

    template<typename T>
    void DataBuffer::read(T& value) {
        if (getAvailable() >= sizeof(T)) {
            memcpy(&value, &_data[_readingPointer], sizeof(T));
            _readingPointer += sizeof(T);
        }
    }

}
