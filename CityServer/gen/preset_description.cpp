#include "preset_description.h"

#include "../util/to_vector.h"

using namespace std;
using namespace gen;
using namespace util;

string getObjectName(const XmlTree& objectTree, int& id) {
    string name = objectTree.get("<xmlattr>.name", "");
    if (name.empty()) {
        name = "@object#" + to_string(id); // имя объекта по умолчанию
        id++;
    }
    return name;
}

bool isCorrectDepend(const ObjectDescription& object, const ObjectsByName& nameToObject) {
    return !object.depend.empty()
        && !object.isInverseDepend
        && nameToObject.find(object.depend) != end(nameToObject);
}

void initializeTransform(const XmlTree& objectTree, ObjectDescription& object, const ObjectsByName& nameToObject) {
    bool correctDepend = isCorrectDepend(object, nameToObject);

    try {
        object.transform.position.x = objectTree.get<float>("Transform.Translate.<xmlattr>.x");
    }
    catch (const runtime_error&) {
        if (correctDepend) {
            object.transform.position.x = nameToObject.at(object.depend).transform.position.x;
        }
    }

    try {
        object.transform.position.y = objectTree.get<float>("Transform.Translate.<xmlattr>.y");
    }
    catch (const runtime_error&) {
        if (correctDepend) {
            object.transform.position.y = nameToObject.at(object.depend).transform.position.x;
        }
        else {
            object.transform.isDeafultPositionY = true;
        }
    }

    try {
        object.transform.position.z = objectTree.get<float>("Transform.Translate.<xmlattr>.z");
    }
    catch (const runtime_error&) {
        if (correctDepend) {
            object.transform.position.z = nameToObject.at(object.depend).transform.position.x;
        }
    }

    try {
        string anglesLine = objectTree.get<string>("Transform.Rotate.<xmlattr>.y");
        object.transform.yAngles = toVector<float>(anglesLine);
    }
    catch (const runtime_error&) {
        if (correctDepend) {
            object.transform.yAngles = nameToObject.at(object.depend).transform.yAngles;
        }
    }
}

void gen::initializeFromXml(const XmlTree& xmlTree, PresetDescription& preset) {
    XmlTree presetTree = xmlTree.get_child("Preset", XmlTree{});
    int id = 0;

    preset.width = presetTree.get<uint16_t>("<xmlattr>.width", 0);
    preset.height = presetTree.get<uint16_t>("<xmlattr>.height", 0);

    for (const auto& i : presetTree) {
        const XmlTree& objectTree = i.second;
        ObjectDescription object;
        
        string depend = objectTree.get("<xmlattr>.depend", "");
        string inverseDepend = objectTree.get("<xmlattr>.inverse-depend", "");

        if (!depend.empty()) {
            object.depend = depend;
        }
        else if (!inverseDepend.empty() && (preset.objects.find(inverseDepend) != end(preset.objects))) {
            object.depend = inverseDepend;
            object.isInverseDepend = true;
        }
            
        initializeTransform(objectTree, object, preset.objects);

        string variants = objectTree.get("Model.<xmlattr>.variants", "");
        object.modelVariants = toVector<string>(variants);
        if (object.modelVariants.size() == 0 && isCorrectDepend(object, preset.objects)) {
            object.modelVariants = preset.objects[object.depend].modelVariants;
        }

        string name = getObjectName(objectTree, id);
        preset.objects[name] = object;
    }
}
