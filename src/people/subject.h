//
// Created by Lage Ragnarsson on 21.09.21.
//

#ifndef NOMAD_SUBJECT_H
#define NOMAD_SUBJECT_H

namespace people {
    class Subject {
    public:
        virtual void fuse(float &uncertainty, const Subject &other, const float otherUncertainty) {}
    };
}
#endif //NOMAD_SUBJECT_H
