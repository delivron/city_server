#include "server.h"
#include "query_handler.h"
#include "request_manager.h"
#include "header_description.h"

using namespace std;
using namespace net;
using namespace obj;

QueryHandler::QueryHandler(const obj::Scene& demoScene, const obj::Scene& cityScene) noexcept
    : _demoScene(demoScene)
    , _cityScene(cityScene) {}

uint32_t QueryHandler::handle(const QueryDescription& query) {
    HeaderDescription header;
    query.dataBuffer->resetReadingPointer();
    query.dataBuffer->read(header);

    _currentTransactionId = header.transactionId;

    switch (header.code) {
    case QueryCode::HELLO:
        return handleHelloQuery(query);

    //case QueryCode::GET_DEMO_SCENE:
        //return handleDemoSceneQuery(query->socket);

    //case QueryCode::GET_NEAR_OBJECTS:
        //query->inputStream.readBytes(cameraPosition, sizeof(cameraPosition));
        //query->inputStream.read(&radius);
        //return handleGetNearObjectsQuery(query->socket, vec3(cameraPosition[0], cameraPosition[1], cameraPosition[2]), radius);

    //case QueryCode::GET_NEAR_NODES:
        //query->inputStream.readBytes(cameraPosition, sizeof(cameraPosition));
        //query->inputStream.read(&radius);
        //return handleGetNearNodes(query->socket, vec3(cameraPosition[0], cameraPosition[1], cameraPosition[2]), radius);

    //case QueryCode::GET_NODE_STATIC_OBJECTS:
        /*count = 0;
        query->inputStream.readBytes(&count, sizeof(count));

        identifiers.resize(count);

        for (unsigned int& element : identifiers) {
            query->inputStream.read(&element);
        }
        */
        //return handleGetNodeStaticObjects(query->socket, identifiers);

    //case QueryCode::GET_DYNAMIC_OBJECTS:
        //query->inputStream.readBytes(cameraPosition, sizeof(cameraPosition));
        //query->inputStream.read(&radius);
        //return handleGetDynamicObjects(query->socket, vec3(cameraPosition[0], cameraPosition[1], cameraPosition[2]), radius);
    }

    return 0;
}

void QueryHandler::addHeader(const DataBufferPtr& dataBuffer, uint16_t transactionId, uint32_t dataSize, QueryCode code) const {
    HeaderDescription header;
    header.transactionId = transactionId;
    header.dataSize = dataSize;
    header.code = code;
    dataBuffer->write(header);
}

uint32_t QueryHandler::handleHelloQuery(const QueryDescription& query) const {
    const size_t MESSAGE_MAX_SIZE = 128;
    string message = "Welcome to the City Server v" + Server::getFullVersion();
    message += string(MESSAGE_MAX_SIZE - message.length(), '\0');

    DataBufferPtr outputBuffer = make_shared<DataBuffer>();
    uint32_t dataSize = sizeof(QueryCode) + MESSAGE_MAX_SIZE;
    addHeader(outputBuffer, _currentTransactionId, dataSize, QueryCode::HELLO);
    outputBuffer->writeBytes(message.c_str(), message.length());

    RequestManager::instance().send(query.socket, outputBuffer);
    
    return static_cast<uint32_t>(outputBuffer->getSize());
}

uint32_t QueryHandler::handleDemoSceneQuery(const QueryDescription& query) const {
    return 0;
}

uint32_t QueryHandler::handleGetNearObjectsQuery(const QueryDescription& query, const glm::vec3& position, float radius) const {
    return 0;
}

uint32_t QueryHandler::handleGetNearNodes(const QueryDescription& query, const glm::vec3& position, float radius) const {
    return 0;
}

uint32_t QueryHandler::handleGetNodeStaticObjects(const QueryDescription& query, const std::vector<uint32_t>& nodeIdentifiers) const {
    return 0;
}
