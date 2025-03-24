// UTF-8编码
#include <geo3dml/Geometry.h>

using namespace geo3dml;

Geometry::Geometry() {
    vertexProperty_ = nullptr;
    edgeProperty_ = nullptr;
    faceProperty_ = nullptr;
    voxelProperty_ = nullptr;
}

Geometry::~Geometry() {
    if (vertexProperty_) {
        delete vertexProperty_;
    }
    if (edgeProperty_) {
        delete edgeProperty_;
    }
    if (faceProperty_) {
        delete faceProperty_;
    }
    if (voxelProperty_) {
        delete voxelProperty_;
    }
}

void Geometry::SetProperty(ShapeProperty* prop, ShapeProperty::SamplingTarget t) {
    prop->Target(GetID(), t);
    switch (t) {
    case ShapeProperty::SamplingTarget::Vertex: {
        if (vertexProperty_ != prop) {
            if (vertexProperty_) {
                delete vertexProperty_;
            }
            vertexProperty_ = prop;
        }
        break;
    }
    case ShapeProperty::SamplingTarget::Edge: {
        if (edgeProperty_ != prop) {
            if (edgeProperty_) {
                delete edgeProperty_;
            }
            edgeProperty_ = prop;
        }
        break;
    }
    case ShapeProperty::SamplingTarget::Face: {
        if (faceProperty_ != prop) {
            if (faceProperty_) {
                delete faceProperty_;
            }
            faceProperty_ = prop;
        }
        break;
    }
    case ShapeProperty::SamplingTarget::Voxel: {
        if (voxelProperty_ != prop) {
            if (voxelProperty_) {
                delete voxelProperty_;
            }
            voxelProperty_ = prop;
        }
        break;
    }
    default:
        break;
    }
}

ShapeProperty* Geometry::GetProperty(ShapeProperty::SamplingTarget t) const {
    switch (t) {
    case ShapeProperty::SamplingTarget::Vertex:
        return vertexProperty_;
    case ShapeProperty::SamplingTarget::Edge:
        return edgeProperty_;
    case ShapeProperty::SamplingTarget::Face:
        return faceProperty_;
    case ShapeProperty::SamplingTarget::Voxel:
        return voxelProperty_;
    default:
        return nullptr;
    }
}
