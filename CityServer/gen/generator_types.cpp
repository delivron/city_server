#include "generator_types.h"

#include "../util/to_vector.h"
#include "../util/filesystem.h"

using namespace std;
using namespace gen;
using namespace util;

void gen::initializeFromXml(const XmlTree& xmlTree, ProbabilityByName& carProbabilities) {
    XmlTree carsTree = xmlTree.get_child("Cars", XmlTree{});
    float popularitySum = 0.0f;

    for (const auto& i : carsTree) {
        const XmlTree& carTree = i.second;
        string name = carTree.get("<xmlattr>.name", "");
        float popularity = carTree.get("<xmlattr>.popularity", 1.0f);

        if (!name.empty()) {
            popularitySum += popularity;
            carProbabilities[name] = popularity;
        }
    }

    for (auto& i : carProbabilities) {
        i.second /= popularitySum;
    }
}

void gen::initializeFromXml(const XmlTree& xmlTree, RoofsByName& buldingRoofs) {
    XmlTree roofsTree = xmlTree.get_child("Roofs", XmlTree{});

    for (const auto& i : roofsTree) {
        const XmlTree& roofTree = i.second;
        string building = roofTree.get("<xmlattr>.building", "");
        string variants = roofTree.get("<xmlattr>.variants", "");
        float y = roofTree.get("<xmlattr>.y", 0.0f);

        if (!building.empty() && !variants.empty()) {
            buldingRoofs[building] = { toVector<string>(variants), y };
        }
    }
}

void gen::initializeFromXml(const XmlTree& xmlTree, StringsByName& variants) {
    XmlTree variantsTree = xmlTree.get_child("VariantsList", XmlTree{});

    for (const auto& i : variantsTree) {
        const XmlTree& varinatTree = i.second;
        string id = varinatTree.get("<xmlattr>.id", "");
        string value = varinatTree.get("<xmlattr>.value", "");

        if (!id.empty() && !value.empty()) {
            variants[id] = toVector<string>(value);
        }
    }
}

void gen::initializeFromXml(const XmlTreesByPath& xmlTrees, PresetsByName& presets) {
    for (const auto& [path, tree] : xmlTrees) {
        string name = getFileName(path);
        initializeFromXml(tree, presets[name]);
    }
}
