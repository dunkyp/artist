/*
 * Copyright 2019 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/**************************************************************************************************
 *** This file was autogenerated from GrColorMatrixFragmentProcessor.fp; do not modify.
 **************************************************************************************************/
#ifndef GrColorMatrixFragmentProcessor_DEFINED
#define GrColorMatrixFragmentProcessor_DEFINED
#include "include/core/SkTypes.h"
#include "include/core/SkM44.h"

#include "src/gpu/GrCoordTransform.h"
#include "src/gpu/GrFragmentProcessor.h"
class GrColorMatrixFragmentProcessor : public GrFragmentProcessor {
public:
    SkPMColor4f constantOutputForConstantInput(const SkPMColor4f& input) const override {
        SkColor4f color;
        if (unpremulInput) {
            color = input.unpremul();
        } else {
            color.fR = input.fR;
            color.fG = input.fG;
            color.fB = input.fB;
            color.fA = input.fA;
        }
        auto v4 = m.map(color.fR, color.fG, color.fB, color.fA) + v;
        color = {v4.x, v4.y, v4.z, v4.w};
        color.fA = SkTPin(color.fA, 0.f, 1.f);
        if (clampRGBOutput) {
            color.fR = SkTPin(color.fR, 0.f, 1.f);
            color.fG = SkTPin(color.fG, 0.f, 1.f);
            color.fB = SkTPin(color.fB, 0.f, 1.f);
        }
        if (premulOutput) {
            return color.premul();
        } else {
            return {color.fR, color.fG, color.fB, color.fA};
        }
    }

    static std::unique_ptr<GrFragmentProcessor> Make(const float matrix[20],
                                                     bool unpremulInput,
                                                     bool clampRGBOutput,
                                                     bool premulOutput) {
        SkM44 m44(matrix[0], matrix[1], matrix[2], matrix[3], matrix[5], matrix[6], matrix[7],
                  matrix[8], matrix[10], matrix[11], matrix[12], matrix[13], matrix[15], matrix[16],
                  matrix[17], matrix[18]);
        SkV4 v4 = {matrix[4], matrix[9], matrix[14], matrix[19]};
        return std::unique_ptr<GrFragmentProcessor>(new GrColorMatrixFragmentProcessor(
                m44, v4, unpremulInput, clampRGBOutput, premulOutput));
    }
    GrColorMatrixFragmentProcessor(const GrColorMatrixFragmentProcessor& src);
    std::unique_ptr<GrFragmentProcessor> clone() const override;
    const char* name() const override { return "ColorMatrixFragmentProcessor"; }
    SkM44 m;
    SkV4 v;
    bool unpremulInput;
    bool clampRGBOutput;
    bool premulOutput;

private:
    GrColorMatrixFragmentProcessor(
            SkM44 m, SkV4 v, bool unpremulInput, bool clampRGBOutput, bool premulOutput)
            : INHERITED(kGrColorMatrixFragmentProcessor_ClassID,
                        (OptimizationFlags)kConstantOutputForConstantInput_OptimizationFlag)
            , m(m)
            , v(v)
            , unpremulInput(unpremulInput)
            , clampRGBOutput(clampRGBOutput)
            , premulOutput(premulOutput) {}
    GrGLSLFragmentProcessor* onCreateGLSLInstance() const override;
    void onGetGLSLProcessorKey(const GrShaderCaps&, GrProcessorKeyBuilder*) const override;
    bool onIsEqual(const GrFragmentProcessor&) const override;
    GR_DECLARE_FRAGMENT_PROCESSOR_TEST
    typedef GrFragmentProcessor INHERITED;
};
#endif