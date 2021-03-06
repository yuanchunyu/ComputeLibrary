/*
 * Copyright (c) 2016-2020 Arm Limited.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef ARM_COMPUTE_NEMAGNITUDEPHASEKERNEL_H
#define ARM_COMPUTE_NEMAGNITUDEPHASEKERNEL_H

#include "arm_compute/core/Types.h"
#include "src/core/NEON/INEKernel.h"

namespace arm_compute
{
class ITensor;

/** Template interface for the kernel to compute magnitude and phase */
template <MagnitudeType mag_type, PhaseType phase_type>
class NEMagnitudePhaseKernel : public INEKernel
{
public:
    const char *name() const override
    {
        return "NEMagnitudePhaseKernel";
    }
    /** Default constructor */
    NEMagnitudePhaseKernel();
    /** Prevent instances of this class from being copied (As this class contains pointers) */
    NEMagnitudePhaseKernel(const NEMagnitudePhaseKernel &) = delete;
    /** Default move constructor */
    NEMagnitudePhaseKernel(NEMagnitudePhaseKernel &&) = default;
    /** Prevent instances of this class from being copied (As this class contains pointers) */
    NEMagnitudePhaseKernel &operator=(const NEMagnitudePhaseKernel &) = delete;
    /** Default move assignment operator */
    NEMagnitudePhaseKernel &operator=(NEMagnitudePhaseKernel &&) = default;
    /** Destructor */
    ~NEMagnitudePhaseKernel() = default;

    /** Initialise the kernel's input, output.
     *
     * @note At least one of out1 or out2 must be set
     *
     * @param[in]  gx        Gradient X tensor. Data type supported: S16.
     * @param[in]  gy        Gradient Y tensor. Data type supported: S16.
     * @param[out] magnitude (Optional) The output tensor - Magnitude. Data type supported: S16.
     * @param[out] phase     (Optional) The output tensor - Phase. Data type supported: U8.
     */
    void configure(const ITensor *gx, const ITensor *gy, ITensor *magnitude, ITensor *phase);

    // Inherited methods overridden:
    void run(const Window &window, const ThreadInfo &info) override;

private:
    /** Function to perform magnitude on the given window
     *
     * @param[in] window Region on which to execute the kernel
     */
    void magnitude(const Window &window);
    /** Function to perform phase on the given window
     *
     * @param[in] window Region on which to execute the kernel
     */
    void phase(const Window &window);
    /** Function to perform magnitude and phase on the given window
     *
     * @param[in] window Region on which to execute the kernel
     */
    void magnitude_phase(const Window &window);

private:
    /** Common signature for all the specialised MagnitudePhase functions
     *
     * @param[in] window Region on which to execute the kernel.
     */
    using MagnitudePhaseFunctionPtr = void (NEMagnitudePhaseKernel::*)(const Window &window);
    /** MagnitudePhase function to use for the particular formats passed to configure() */
    MagnitudePhaseFunctionPtr _func;
    const ITensor            *_gx;        /**< Input gradient X */
    const ITensor            *_gy;        /**< Input gradient Y */
    ITensor                  *_magnitude; /**< Output - Magnitude */
    ITensor                  *_phase;     /**< Output - Phase */
};
} // namespace arm_compute
#endif /* ARM_COMPUTE_NEMAGNITUDEPHASEKERNEL_H */
