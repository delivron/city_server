#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "header_description.h"
#include "net_handler_interface.h"

#include "../obj/scene.h"

namespace net {

    class QueryHandler : public NetHandlerInterface {
    public:
        QueryHandler(const obj::Scene& demoScene, const obj::Scene& cityScene) noexcept;

        uint32_t                        handle(const QueryDescription& query);
        
    private:
        void                            addHeader(const DataBufferPtr& dataBuffer, uint16_t transactionId, uint32_t dataSize, QueryCode code) const;
        uint32_t                        handleHelloQuery(const QueryDescription& query) const;
        uint32_t                        handleDemoSceneQuery(const QueryDescription& query) const;
        uint32_t                        handleGetNearObjectsQuery(const QueryDescription& query, const glm::vec3& position, float radius) const;
        uint32_t                        handleGetNearNodes(const QueryDescription& query, const glm::vec3& position, float radius) const;
        uint32_t                        handleGetNodeStaticObjects(const QueryDescription& query, const std::vector<uint32_t>& nodeIdentifiers) const;

        uint16_t                        _currentTransactionId;
        const obj::Scene&               _demoScene;
        const obj::Scene&               _cityScene;
    };

}
