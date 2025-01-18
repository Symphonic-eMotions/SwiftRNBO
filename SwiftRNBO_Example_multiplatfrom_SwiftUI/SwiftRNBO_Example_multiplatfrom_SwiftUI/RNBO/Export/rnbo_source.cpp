/*******************************************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER $200k in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below $200k annual revenue or funding.

For entities with OVER $200k in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing@cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
*******************************************************************************************************************/

#include "RNBO_Common.h"
#include "RNBO_AudioSignal.h"

namespace RNBO {


#define trunc(x) ((Int)(x))

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

class rnbomatic : public PatcherInterfaceImpl {
public:

class RNBOSubpatcher_48 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    class RNBOSubpatcher_44 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_48;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_44()
            {
            }
            
            ~RNBOSubpatcher_44()
            {
            }
            
            virtual RNBOSubpatcher_48* getPatcher() const {
                return static_cast<RNBOSubpatcher_48 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            inline number linearinterp(number frac, number x, number y) {
                return x + (y - x) * frac;
            }
            
            inline number cubicinterp(number a, number w, number x, number y, number z) {
                number a2 = a * a;
                number f0 = z - y - w + x;
                number f1 = w - x - f0;
                number f2 = y - w;
                number f3 = x;
                return f0 * a * a2 + f1 * a2 + f2 * a + f3;
            }
            
            inline number splineinterp(number a, number w, number x, number y, number z) {
                number a2 = a * a;
                number f0 = -0.5 * w + 1.5 * x - 1.5 * y + 0.5 * z;
                number f1 = w - 2.5 * x + 2 * y - 0.5 * z;
                number f2 = -0.5 * w + 0.5 * y;
                return f0 * a * a2 + f1 * a2 + f2 * a + x;
            }
            
            inline number cosT8(number r) {
                number t84 = 56.0;
                number t83 = 1680.0;
                number t82 = 20160.0;
                number t81 = 2.4801587302e-05;
                number t73 = 42.0;
                number t72 = 840.0;
                number t71 = 1.9841269841e-04;
            
                if (r < 0.785398163397448309615660845819875721 && r > -0.785398163397448309615660845819875721) {
                    number rr = r * r;
                    return 1.0 - rr * t81 * (t82 - rr * (t83 - rr * (t84 - rr)));
                } else if (r > 0.0) {
                    r -= 1.57079632679489661923132169163975144;
                    number rr = r * r;
                    return -r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
                } else {
                    r += 1.57079632679489661923132169163975144;
                    number rr = r * r;
                    return r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
                }
            }
            
            inline number cosineinterp(number frac, number x, number y) {
                number a2 = (1.0 - this->cosT8(frac * 3.14159265358979323846)) / (number)2.0;
                return x * (1.0 - a2) + y * a2;
            }
            
            number mstosamps(MillisecondTime ms) {
                return ms * this->sr * 0.001;
            }
            
            number samplerate() {
                return this->sr;
            }
            
            Index vectorsize() {
                return this->vs;
            }
            
            number maximum(number x, number y) {
                return (x < y ? y : x);
            }
            
            inline number safediv(number num, number denom) {
                return (denom == 0.0 ? 0.0 : num / denom);
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
                const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                this->dspexpr_02_perform(in1, this->dspexpr_02_in2, this->signals[0], n);
                this->dspexpr_04_perform(in1, this->dspexpr_04_in2, this->signals[1], n);
            
                this->slide_tilde_01_perform(
                    this->slide_tilde_01_x,
                    this->slide_tilde_01_up,
                    this->slide_tilde_01_down,
                    this->signals[2],
                    n
                );
            
                this->feedbackreader_01_perform(this->signals[3], n);
                this->delaytilde_01_perform(this->delaytilde_01_delay, this->signals[3], this->signals[4], n);
                this->dspexpr_01_perform(this->signals[4], this->signals[2], this->signals[5], n);
                this->signaladder_03_perform(this->signals[0], this->signals[5], this->signals[5], n);
                this->feedbackwriter_01_perform(this->signals[5], n);
                this->signalforwarder_01_perform(this->signals[3], out1, n);
                this->feedbackreader_02_perform(this->signals[3], n);
                this->delaytilde_02_perform(this->delaytilde_02_delay, this->signals[3], this->signals[0], n);
                this->dspexpr_03_perform(this->signals[0], this->signals[2], this->signals[4], n);
                this->signaladder_04_perform(this->signals[4], this->signals[1], this->signals[1], n);
                this->feedbackwriter_02_perform(this->signals[1], n);
                this->signalforwarder_02_perform(this->signals[3], out2, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 6; i++) {
                        this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                    }
            
                    this->feedbacktilde_01_feedbackbuffer = resizeSignal(this->feedbacktilde_01_feedbackbuffer, this->maxvs, maxBlockSize);
                    this->feedbacktilde_02_feedbackbuffer = resizeSignal(this->feedbacktilde_02_feedbackbuffer, this->maxvs, maxBlockSize);
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->delaytilde_01_dspsetup(forceDSPSetup);
                this->delaytilde_02_dspsetup(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& preset) {
                this->param_01_getPresetValue(getSubState(preset, "left_delay"));
                this->param_02_getPresetValue(getSubState(preset, "fb"));
                this->param_03_getPresetValue(getSubState(preset, "right_delay"));
            }
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
                this->updateTime(time);
            
                switch (index) {
                case 0:
                    {
                    this->param_01_value_set(v);
                    break;
                    }
                case 1:
                    {
                    this->param_02_value_set(v);
                    break;
                    }
                case 2:
                    {
                    this->param_03_value_set(v);
                    break;
                    }
                }
            }
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                case 0:
                    {
                    return this->param_01_value;
                    }
                case 1:
                    {
                    return this->param_02_value;
                    }
                case 2:
                    {
                    return this->param_03_value;
                    }
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 3;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                case 0:
                    {
                    return "left_delay";
                    }
                case 1:
                    {
                    return "fb";
                    }
                case 2:
                    {
                    return "right_delay";
                    }
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                case 0:
                    {
                    return "poly/stereo_delay/left_delay";
                    }
                case 1:
                    {
                    return "poly/stereo_delay/fb";
                    }
                case 2:
                    {
                    return "poly/stereo_delay/right_delay";
                    }
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
                {
                    switch (index) {
                    case 0:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 300;
                        info->min = 10;
                        info->max = 10000;
                        info->exponent = 1;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    case 1:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 0.25;
                        info->min = 0;
                        info->max = 1;
                        info->exponent = 1;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    case 2:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 400;
                        info->min = 10;
                        info->max = 10000;
                        info->exponent = 1;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    }
                }
            }
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                case 1:
                    {
                    {
                        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                        ParameterValue normalizedValue = (value - 0) / (1 - 0);
                        return normalizedValue;
                    }
                    }
                case 0:
                case 2:
                    {
                    {
                        value = (value < 10 ? 10 : (value > 10000 ? 10000 : value));
                        ParameterValue normalizedValue = (value - 10) / (10000 - 10);
                        return normalizedValue;
                    }
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                case 1:
                    {
                    {
                        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                        {
                            return 0 + value * (1 - 0);
                        }
                    }
                    }
                case 0:
                case 2:
                    {
                    {
                        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                        {
                            return 10 + value * (10000 - 10);
                        }
                    }
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                case 0:
                    {
                    return this->param_01_value_constrain(value);
                    }
                case 1:
                    {
                    return this->param_02_value_constrain(value);
                    }
                case 2:
                    {
                    return this->param_03_value_constrain(value);
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                case 2:
                    {
                    return addressOf(this->delaytilde_01_del_bufferobj);
                    break;
                    }
                case 3:
                    {
                    return addressOf(this->delaytilde_02_del_bufferobj);
                    break;
                    }
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 2;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void zeroDataRef(DataRef& ref) {
                ref->setZero();
            }
            
            void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
                this->updateTime(time);
            
                if (index == 2) {
                    this->delaytilde_01_del_buffer = new Float64Buffer(this->delaytilde_01_del_bufferobj);
                }
            
                if (index == 3) {
                    this->delaytilde_02_del_buffer = new Float64Buffer(this->delaytilde_02_del_bufferobj);
                }
            }
            
            void initialize() {
                this->delaytilde_01_del_bufferobj = initDataRef("delaytilde_01_del_bufferobj", true, nullptr, "buffer~");
                this->delaytilde_02_del_bufferobj = initDataRef("delaytilde_02_del_bufferobj", true, nullptr, "buffer~");
                this->assign_defaults();
                this->setState();
                this->delaytilde_01_del_bufferobj->setIndex(2);
                this->delaytilde_01_del_buffer = new Float64Buffer(this->delaytilde_01_del_bufferobj);
                this->delaytilde_02_del_bufferobj->setIndex(3);
                this->delaytilde_02_del_buffer = new Float64Buffer(this->delaytilde_02_del_bufferobj);
            }
            
            protected:
            
            void param_01_value_set(number v) {
                v = this->param_01_value_constrain(v);
                this->param_01_value = v;
                this->sendParameter(0, false);
            
                if (this->param_01_value != this->param_01_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_01_lastValue = this->param_01_value;
                }
            
                this->mstosamps_01_ms_set(v);
            }
            
            void param_02_value_set(number v) {
                v = this->param_02_value_constrain(v);
                this->param_02_value = v;
                this->sendParameter(1, false);
            
                if (this->param_02_value != this->param_02_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_02_lastValue = this->param_02_value;
                }
            
                this->slide_tilde_01_x_set(v);
            }
            
            void param_03_value_set(number v) {
                v = this->param_03_value_constrain(v);
                this->param_03_value = v;
                this->sendParameter(2, false);
            
                if (this->param_03_value != this->param_03_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_03_lastValue = this->param_03_value;
                }
            
                this->mstosamps_02_ms_set(v);
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 1;
            }
            
            Index getNumOutputChannels() const {
                return 2;
            }
            
            void initializeObjects() {
                this->delaytilde_01_del_init();
                this->delaytilde_02_del_init();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime());
            
                {
                    this->scheduleParamInit(0, 0);
                }
            
                {
                    this->scheduleParamInit(1, 0);
                }
            
                {
                    this->scheduleParamInit(2, 0);
                }
            }
            
            void allocateDataRefs() {
                this->delaytilde_01_del_buffer = this->delaytilde_01_del_buffer->allocateIfNeeded();
            
                if (this->delaytilde_01_del_bufferobj->hasRequestedSize()) {
                    if (this->delaytilde_01_del_bufferobj->wantsFill())
                        this->zeroDataRef(this->delaytilde_01_del_bufferobj);
            
                    this->getEngine()->sendDataRefUpdated(2);
                }
            
                this->delaytilde_02_del_buffer = this->delaytilde_02_del_buffer->allocateIfNeeded();
            
                if (this->delaytilde_02_del_bufferobj->hasRequestedSize()) {
                    if (this->delaytilde_02_del_bufferobj->wantsFill())
                        this->zeroDataRef(this->delaytilde_02_del_bufferobj);
            
                    this->getEngine()->sendDataRefUpdated(3);
                }
            }
            
            static number param_01_value_constrain(number v) {
                v = (v > 10000 ? 10000 : (v < 10 ? 10 : v));
                return v;
            }
            
            void delaytilde_01_delay_set(number v) {
                this->delaytilde_01_delay = v;
            }
            
            void mstosamps_01_out1_set(number v) {
                this->delaytilde_01_delay_set(v);
            }
            
            void mstosamps_01_ms_set(number ms) {
                this->mstosamps_01_ms = ms;
            
                {
                    this->mstosamps_01_out1_set(ms * this->sr * 0.001);
                    return;
                }
            }
            
            static number param_02_value_constrain(number v) {
                v = (v > 1 ? 1 : (v < 0 ? 0 : v));
                return v;
            }
            
            void slide_tilde_01_x_set(number v) {
                this->slide_tilde_01_x = v;
            }
            
            static number param_03_value_constrain(number v) {
                v = (v > 10000 ? 10000 : (v < 10 ? 10 : v));
                return v;
            }
            
            void delaytilde_02_delay_set(number v) {
                this->delaytilde_02_delay = v;
            }
            
            void mstosamps_02_out1_set(number v) {
                this->delaytilde_02_delay_set(v);
            }
            
            void mstosamps_02_ms_set(number ms) {
                this->mstosamps_02_ms = ms;
            
                {
                    this->mstosamps_02_out1_set(ms * this->sr * 0.001);
                    return;
                }
            }
            
            void dspexpr_02_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
                RNBO_UNUSED(in2);
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * 0.3;//#map:_###_obj_###_:1
                }
            }
            
            void dspexpr_04_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
                RNBO_UNUSED(in2);
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * 0.3;//#map:_###_obj_###_:1
                }
            }
            
            void slide_tilde_01_perform(number x, number up, number down, SampleValue * out1, Index n) {
                RNBO_UNUSED(down);
                RNBO_UNUSED(up);
                auto __slide_tilde_01_prev = this->slide_tilde_01_prev;
                auto iup = this->safediv(1., this->maximum(1., rnbo_abs(10)));
                auto idown = this->safediv(1., this->maximum(1., rnbo_abs(10)));
                Index i;
            
                for (i = 0; i < n; i++) {
                    number temp = x - __slide_tilde_01_prev;
                    __slide_tilde_01_prev = __slide_tilde_01_prev + ((x > __slide_tilde_01_prev ? iup : idown)) * temp;
                    out1[(Index)i] = __slide_tilde_01_prev;
                }
            
                this->slide_tilde_01_prev = __slide_tilde_01_prev;
            }
            
            void feedbackreader_01_perform(SampleValue * output, Index n) {
                auto& buffer = this->feedbacktilde_01_feedbackbuffer;
            
                for (Index i = 0; i < n; i++) {
                    output[(Index)i] = buffer[(Index)i];
                }
            }
            
            void delaytilde_01_perform(number delay, const SampleValue * input, SampleValue * output, Index n) {
                auto __delaytilde_01_crossfadeDelay = this->delaytilde_01_crossfadeDelay;
                auto __delaytilde_01_rampInSamples = this->delaytilde_01_rampInSamples;
                auto __delaytilde_01_ramp = this->delaytilde_01_ramp;
                auto __delaytilde_01_lastDelay = this->delaytilde_01_lastDelay;
            
                for (Index i = 0; i < n; i++) {
                    if (__delaytilde_01_lastDelay == -1) {
                        __delaytilde_01_lastDelay = delay;
                    }
            
                    if (__delaytilde_01_ramp > 0) {
                        number factor = __delaytilde_01_ramp / __delaytilde_01_rampInSamples;
                        output[(Index)i] = this->delaytilde_01_del_read(__delaytilde_01_crossfadeDelay, 0) * factor + this->delaytilde_01_del_read(__delaytilde_01_lastDelay, 0) * (1. - factor);
                        __delaytilde_01_ramp--;
                    } else {
                        number effectiveDelay = delay;
            
                        if (effectiveDelay != __delaytilde_01_lastDelay) {
                            __delaytilde_01_ramp = __delaytilde_01_rampInSamples;
                            __delaytilde_01_crossfadeDelay = __delaytilde_01_lastDelay;
                            __delaytilde_01_lastDelay = effectiveDelay;
                            output[(Index)i] = this->delaytilde_01_del_read(__delaytilde_01_crossfadeDelay, 0);
                            __delaytilde_01_ramp--;
                        } else {
                            output[(Index)i] = this->delaytilde_01_del_read(effectiveDelay, 0);
                        }
                    }
            
                    this->delaytilde_01_del_write(input[(Index)i]);
                    this->delaytilde_01_del_step();
                }
            
                this->delaytilde_01_lastDelay = __delaytilde_01_lastDelay;
                this->delaytilde_01_ramp = __delaytilde_01_ramp;
                this->delaytilde_01_crossfadeDelay = __delaytilde_01_crossfadeDelay;
            }
            
            void dspexpr_01_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void signaladder_03_perform(
                const SampleValue * in1,
                const SampleValue * in2,
                SampleValue * out,
                Index n
            ) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out[(Index)i] = in1[(Index)i] + in2[(Index)i];
                }
            }
            
            void feedbackwriter_01_perform(const SampleValue * input, Index n) {
                auto& buffer = this->feedbacktilde_01_feedbackbuffer;
            
                for (Index i = 0; i < n; i++) {
                    buffer[(Index)i] = input[(Index)i];
                }
            }
            
            void signalforwarder_01_perform(const SampleValue * input, SampleValue * output, Index n) {
                for (Index i = 0; i < n; i++) {
                    output[(Index)i] = input[(Index)i];
                }
            }
            
            void feedbackreader_02_perform(SampleValue * output, Index n) {
                auto& buffer = this->feedbacktilde_02_feedbackbuffer;
            
                for (Index i = 0; i < n; i++) {
                    output[(Index)i] = buffer[(Index)i];
                }
            }
            
            void delaytilde_02_perform(number delay, const SampleValue * input, SampleValue * output, Index n) {
                auto __delaytilde_02_crossfadeDelay = this->delaytilde_02_crossfadeDelay;
                auto __delaytilde_02_rampInSamples = this->delaytilde_02_rampInSamples;
                auto __delaytilde_02_ramp = this->delaytilde_02_ramp;
                auto __delaytilde_02_lastDelay = this->delaytilde_02_lastDelay;
            
                for (Index i = 0; i < n; i++) {
                    if (__delaytilde_02_lastDelay == -1) {
                        __delaytilde_02_lastDelay = delay;
                    }
            
                    if (__delaytilde_02_ramp > 0) {
                        number factor = __delaytilde_02_ramp / __delaytilde_02_rampInSamples;
                        output[(Index)i] = this->delaytilde_02_del_read(__delaytilde_02_crossfadeDelay, 0) * factor + this->delaytilde_02_del_read(__delaytilde_02_lastDelay, 0) * (1. - factor);
                        __delaytilde_02_ramp--;
                    } else {
                        number effectiveDelay = delay;
            
                        if (effectiveDelay != __delaytilde_02_lastDelay) {
                            __delaytilde_02_ramp = __delaytilde_02_rampInSamples;
                            __delaytilde_02_crossfadeDelay = __delaytilde_02_lastDelay;
                            __delaytilde_02_lastDelay = effectiveDelay;
                            output[(Index)i] = this->delaytilde_02_del_read(__delaytilde_02_crossfadeDelay, 0);
                            __delaytilde_02_ramp--;
                        } else {
                            output[(Index)i] = this->delaytilde_02_del_read(effectiveDelay, 0);
                        }
                    }
            
                    this->delaytilde_02_del_write(input[(Index)i]);
                    this->delaytilde_02_del_step();
                }
            
                this->delaytilde_02_lastDelay = __delaytilde_02_lastDelay;
                this->delaytilde_02_ramp = __delaytilde_02_ramp;
                this->delaytilde_02_crossfadeDelay = __delaytilde_02_crossfadeDelay;
            }
            
            void dspexpr_03_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void signaladder_04_perform(
                const SampleValue * in1,
                const SampleValue * in2,
                SampleValue * out,
                Index n
            ) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out[(Index)i] = in1[(Index)i] + in2[(Index)i];
                }
            }
            
            void feedbackwriter_02_perform(const SampleValue * input, Index n) {
                auto& buffer = this->feedbacktilde_02_feedbackbuffer;
            
                for (Index i = 0; i < n; i++) {
                    buffer[(Index)i] = input[(Index)i];
                }
            }
            
            void signalforwarder_02_perform(const SampleValue * input, SampleValue * output, Index n) {
                for (Index i = 0; i < n; i++) {
                    output[(Index)i] = input[(Index)i];
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            void delaytilde_01_del_step() {
                this->delaytilde_01_del_reader++;
            
                if (this->delaytilde_01_del_reader >= (int)(this->delaytilde_01_del_buffer->getSize()))
                    this->delaytilde_01_del_reader = 0;
            }
            
            number delaytilde_01_del_read(number size, Int interp) {
                if (interp == 0) {
                    number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    long index2 = (long)(index1 + 1);
            
                    return this->linearinterp(frac, this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
                    ), this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
                    ));
                } else if (interp == 1) {
                    number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? 1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    Index index2 = (Index)(index1 + 1);
                    Index index3 = (Index)(index2 + 1);
                    Index index4 = (Index)(index3 + 1);
            
                    return this->cubicinterp(frac, this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
                    ), this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
                    ), this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_01_del_wrap))
                    ), this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_01_del_wrap))
                    ));
                } else if (interp == 2) {
                    number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? 1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    Index index2 = (Index)(index1 + 1);
                    Index index3 = (Index)(index2 + 1);
                    Index index4 = (Index)(index3 + 1);
            
                    return this->splineinterp(frac, this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
                    ), this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
                    ), this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_01_del_wrap))
                    ), this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_01_del_wrap))
                    ));
                } else if (interp == 3) {
                    number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    Index index2 = (Index)(index1 + 1);
            
                    return this->cosineinterp(frac, this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
                    ), this->delaytilde_01_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
                    ));
                }
            
                number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
                long index1 = (long)(rnbo_floor(r));
            
                return this->delaytilde_01_del_buffer->getSample(
                    0,
                    (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
                );
            }
            
            void delaytilde_01_del_write(number v) {
                this->delaytilde_01_del_writer = this->delaytilde_01_del_reader;
                this->delaytilde_01_del_buffer[(Index)this->delaytilde_01_del_writer] = v;
            }
            
            number delaytilde_01_del_next(number v, int size) {
                number effectiveSize = (size == -1 ? this->delaytilde_01_del__maxdelay : size);
                number val = this->delaytilde_01_del_read(effectiveSize, 0);
                this->delaytilde_01_del_write(v);
                this->delaytilde_01_del_step();
                return val;
            }
            
            array<Index, 2> delaytilde_01_del_calcSizeInSamples() {
                number sizeInSamples = 0;
                Index allocatedSizeInSamples = 0;
            
                {
                    sizeInSamples = this->delaytilde_01_del_evaluateSizeExpr(this->samplerate(), this->vectorsize());
                    this->delaytilde_01_del_sizemode = 0;
                }
            
                sizeInSamples = rnbo_floor(sizeInSamples);
                sizeInSamples = this->maximum(sizeInSamples, 2);
                allocatedSizeInSamples = (Index)(sizeInSamples);
                allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
                return {sizeInSamples, allocatedSizeInSamples};
            }
            
            void delaytilde_01_del_init() {
                auto result = this->delaytilde_01_del_calcSizeInSamples();
                this->delaytilde_01_del__maxdelay = result[0];
                Index requestedSizeInSamples = (Index)(result[1]);
                this->delaytilde_01_del_buffer->requestSize(requestedSizeInSamples, 1);
                this->delaytilde_01_del_wrap = requestedSizeInSamples - 1;
            }
            
            void delaytilde_01_del_clear() {
                this->delaytilde_01_del_buffer->setZero();
            }
            
            void delaytilde_01_del_reset() {
                auto result = this->delaytilde_01_del_calcSizeInSamples();
                this->delaytilde_01_del__maxdelay = result[0];
                Index allocatedSizeInSamples = (Index)(result[1]);
                this->delaytilde_01_del_buffer->setSize(allocatedSizeInSamples);
                updateDataRef(this, this->delaytilde_01_del_buffer);
                this->delaytilde_01_del_wrap = this->delaytilde_01_del_buffer->getSize() - 1;
                this->delaytilde_01_del_clear();
            
                if (this->delaytilde_01_del_reader >= this->delaytilde_01_del__maxdelay || this->delaytilde_01_del_writer >= this->delaytilde_01_del__maxdelay) {
                    this->delaytilde_01_del_reader = 0;
                    this->delaytilde_01_del_writer = 0;
                }
            }
            
            void delaytilde_01_del_dspsetup() {
                this->delaytilde_01_del_reset();
            }
            
            number delaytilde_01_del_evaluateSizeExpr(number samplerate, number vectorsize) {
                RNBO_UNUSED(vectorsize);
                return samplerate;
            }
            
            number delaytilde_01_del_size() {
                return this->delaytilde_01_del__maxdelay;
            }
            
            void delaytilde_01_dspsetup(bool force) {
                if ((bool)(this->delaytilde_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->delaytilde_01_rampInSamples = (long)(this->mstosamps(50));
                this->delaytilde_01_lastDelay = -1;
                this->delaytilde_01_setupDone = true;
                this->delaytilde_01_del_dspsetup();
            }
            
            void param_01_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_01_value;
            }
            
            void param_01_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_01_value_set(preset["value"]);
            }
            
            void param_02_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_02_value;
            }
            
            void param_02_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_02_value_set(preset["value"]);
            }
            
            void param_03_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_03_value;
            }
            
            void param_03_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_03_value_set(preset["value"]);
            }
            
            void delaytilde_02_del_step() {
                this->delaytilde_02_del_reader++;
            
                if (this->delaytilde_02_del_reader >= (int)(this->delaytilde_02_del_buffer->getSize()))
                    this->delaytilde_02_del_reader = 0;
            }
            
            number delaytilde_02_del_read(number size, Int interp) {
                if (interp == 0) {
                    number r = (int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    long index2 = (long)(index1 + 1);
            
                    return this->linearinterp(frac, this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
                    ), this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
                    ));
                } else if (interp == 1) {
                    number r = (int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? 1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    Index index2 = (Index)(index1 + 1);
                    Index index3 = (Index)(index2 + 1);
                    Index index4 = (Index)(index3 + 1);
            
                    return this->cubicinterp(frac, this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
                    ), this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
                    ), this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_02_del_wrap))
                    ), this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_02_del_wrap))
                    ));
                } else if (interp == 2) {
                    number r = (int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? 1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    Index index2 = (Index)(index1 + 1);
                    Index index3 = (Index)(index2 + 1);
                    Index index4 = (Index)(index3 + 1);
            
                    return this->splineinterp(frac, this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
                    ), this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
                    ), this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_02_del_wrap))
                    ), this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_02_del_wrap))
                    ));
                } else if (interp == 3) {
                    number r = (int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
                    long index1 = (long)(rnbo_floor(r));
                    number frac = r - index1;
                    Index index2 = (Index)(index1 + 1);
            
                    return this->cosineinterp(frac, this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
                    ), this->delaytilde_02_del_buffer->getSample(
                        0,
                        (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
                    ));
                }
            
                number r = (int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
                long index1 = (long)(rnbo_floor(r));
            
                return this->delaytilde_02_del_buffer->getSample(
                    0,
                    (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
                );
            }
            
            void delaytilde_02_del_write(number v) {
                this->delaytilde_02_del_writer = this->delaytilde_02_del_reader;
                this->delaytilde_02_del_buffer[(Index)this->delaytilde_02_del_writer] = v;
            }
            
            number delaytilde_02_del_next(number v, int size) {
                number effectiveSize = (size == -1 ? this->delaytilde_02_del__maxdelay : size);
                number val = this->delaytilde_02_del_read(effectiveSize, 0);
                this->delaytilde_02_del_write(v);
                this->delaytilde_02_del_step();
                return val;
            }
            
            array<Index, 2> delaytilde_02_del_calcSizeInSamples() {
                number sizeInSamples = 0;
                Index allocatedSizeInSamples = 0;
            
                {
                    sizeInSamples = this->delaytilde_02_del_evaluateSizeExpr(this->samplerate(), this->vectorsize());
                    this->delaytilde_02_del_sizemode = 0;
                }
            
                sizeInSamples = rnbo_floor(sizeInSamples);
                sizeInSamples = this->maximum(sizeInSamples, 2);
                allocatedSizeInSamples = (Index)(sizeInSamples);
                allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
                return {sizeInSamples, allocatedSizeInSamples};
            }
            
            void delaytilde_02_del_init() {
                auto result = this->delaytilde_02_del_calcSizeInSamples();
                this->delaytilde_02_del__maxdelay = result[0];
                Index requestedSizeInSamples = (Index)(result[1]);
                this->delaytilde_02_del_buffer->requestSize(requestedSizeInSamples, 1);
                this->delaytilde_02_del_wrap = requestedSizeInSamples - 1;
            }
            
            void delaytilde_02_del_clear() {
                this->delaytilde_02_del_buffer->setZero();
            }
            
            void delaytilde_02_del_reset() {
                auto result = this->delaytilde_02_del_calcSizeInSamples();
                this->delaytilde_02_del__maxdelay = result[0];
                Index allocatedSizeInSamples = (Index)(result[1]);
                this->delaytilde_02_del_buffer->setSize(allocatedSizeInSamples);
                updateDataRef(this, this->delaytilde_02_del_buffer);
                this->delaytilde_02_del_wrap = this->delaytilde_02_del_buffer->getSize() - 1;
                this->delaytilde_02_del_clear();
            
                if (this->delaytilde_02_del_reader >= this->delaytilde_02_del__maxdelay || this->delaytilde_02_del_writer >= this->delaytilde_02_del__maxdelay) {
                    this->delaytilde_02_del_reader = 0;
                    this->delaytilde_02_del_writer = 0;
                }
            }
            
            void delaytilde_02_del_dspsetup() {
                this->delaytilde_02_del_reset();
            }
            
            number delaytilde_02_del_evaluateSizeExpr(number samplerate, number vectorsize) {
                RNBO_UNUSED(vectorsize);
                return samplerate;
            }
            
            number delaytilde_02_del_size() {
                return this->delaytilde_02_del__maxdelay;
            }
            
            void delaytilde_02_dspsetup(bool force) {
                if ((bool)(this->delaytilde_02_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->delaytilde_02_rampInSamples = (long)(this->mstosamps(50));
                this->delaytilde_02_lastDelay = -1;
                this->delaytilde_02_setupDone = true;
                this->delaytilde_02_del_dspsetup();
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                dspexpr_01_in1 = 0;
                dspexpr_01_in2 = 0.25;
                delaytilde_01_delay = 0;
                param_01_value = 300;
                mstosamps_01_ms = 0;
                dspexpr_02_in1 = 0;
                dspexpr_02_in2 = 0.3;
                slide_tilde_01_x = 0;
                slide_tilde_01_up = 10;
                slide_tilde_01_down = 10;
                param_02_value = 0.25;
                param_03_value = 400;
                mstosamps_02_ms = 0;
                dspexpr_03_in1 = 0;
                dspexpr_03_in2 = 0.25;
                delaytilde_02_delay = 0;
                dspexpr_04_in1 = 0;
                dspexpr_04_in2 = 0.3;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                signals[0] = nullptr;
                signals[1] = nullptr;
                signals[2] = nullptr;
                signals[3] = nullptr;
                signals[4] = nullptr;
                signals[5] = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                delaytilde_01_lastDelay = -1;
                delaytilde_01_crossfadeDelay = 0;
                delaytilde_01_ramp = 0;
                delaytilde_01_rampInSamples = 0;
                delaytilde_01_del__maxdelay = 0;
                delaytilde_01_del_sizemode = 0;
                delaytilde_01_del_wrap = 0;
                delaytilde_01_del_reader = 0;
                delaytilde_01_del_writer = 0;
                delaytilde_01_setupDone = false;
                param_01_lastValue = 0;
                feedbacktilde_01_feedbackbuffer = nullptr;
                slide_tilde_01_prev = 0;
                param_02_lastValue = 0;
                param_03_lastValue = 0;
                delaytilde_02_lastDelay = -1;
                delaytilde_02_crossfadeDelay = 0;
                delaytilde_02_ramp = 0;
                delaytilde_02_rampInSamples = 0;
                delaytilde_02_del__maxdelay = 0;
                delaytilde_02_del_sizemode = 0;
                delaytilde_02_del_wrap = 0;
                delaytilde_02_del_reader = 0;
                delaytilde_02_del_writer = 0;
                delaytilde_02_setupDone = false;
                feedbacktilde_02_feedbackbuffer = nullptr;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number dspexpr_01_in1;
                number dspexpr_01_in2;
                number delaytilde_01_delay;
                number param_01_value;
                number mstosamps_01_ms;
                number dspexpr_02_in1;
                number dspexpr_02_in2;
                number slide_tilde_01_x;
                number slide_tilde_01_up;
                number slide_tilde_01_down;
                number param_02_value;
                number param_03_value;
                number mstosamps_02_ms;
                number dspexpr_03_in1;
                number dspexpr_03_in2;
                number delaytilde_02_delay;
                number dspexpr_04_in1;
                number dspexpr_04_in2;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                SampleValue * signals[6];
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number delaytilde_01_lastDelay;
                number delaytilde_01_crossfadeDelay;
                number delaytilde_01_ramp;
                long delaytilde_01_rampInSamples;
                Float64BufferRef delaytilde_01_del_buffer;
                Index delaytilde_01_del__maxdelay;
                Int delaytilde_01_del_sizemode;
                Index delaytilde_01_del_wrap;
                Int delaytilde_01_del_reader;
                Int delaytilde_01_del_writer;
                bool delaytilde_01_setupDone;
                number param_01_lastValue;
                signal feedbacktilde_01_feedbackbuffer;
                number slide_tilde_01_prev;
                number param_02_lastValue;
                number param_03_lastValue;
                number delaytilde_02_lastDelay;
                number delaytilde_02_crossfadeDelay;
                number delaytilde_02_ramp;
                long delaytilde_02_rampInSamples;
                Float64BufferRef delaytilde_02_del_buffer;
                Index delaytilde_02_del__maxdelay;
                Int delaytilde_02_del_sizemode;
                Index delaytilde_02_del_wrap;
                Int delaytilde_02_del_reader;
                Int delaytilde_02_del_writer;
                bool delaytilde_02_setupDone;
                signal feedbacktilde_02_feedbackbuffer;
                number stackprotect_count;
                DataRef delaytilde_01_del_bufferobj;
                DataRef delaytilde_02_del_bufferobj;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_45 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_48;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_45()
            {
            }
            
            ~RNBOSubpatcher_45()
            {
            }
            
            virtual RNBOSubpatcher_48* getPatcher() const {
                return static_cast<RNBOSubpatcher_48 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            inline number safediv(number num, number denom) {
                return (denom == 0.0 ? 0.0 : num / denom);
            }
            
            number maximum(number x, number y) {
                return (x < y ? y : x);
            }
            
            number mstosamps(MillisecondTime ms) {
                return ms * this->sr * 0.001;
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
                const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
            
                this->gen_01_perform(
                    in2,
                    in2,
                    this->gen_01_in3,
                    this->gen_01_in4,
                    this->gen_01_in5,
                    this->gen_01_in6,
                    this->gen_01_attack_lockout,
                    this->signals[0],
                    n
                );
            
                this->dspexpr_05_perform(in1, this->signals[0], out1, n);
                this->signalforwarder_03_perform(this->signals[0], out2, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 1; i++) {
                        this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                    }
            
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->gen_01_dspsetup(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& preset) {
                this->param_04_getPresetValue(getSubState(preset, "attack"));
                this->param_05_getPresetValue(getSubState(preset, "decay"));
                this->param_06_getPresetValue(getSubState(preset, "sustain"));
                this->param_07_getPresetValue(getSubState(preset, "release"));
            }
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
                this->updateTime(time);
            
                switch (index) {
                case 0:
                    {
                    this->param_04_value_set(v);
                    break;
                    }
                case 1:
                    {
                    this->param_05_value_set(v);
                    break;
                    }
                case 2:
                    {
                    this->param_06_value_set(v);
                    break;
                    }
                case 3:
                    {
                    this->param_07_value_set(v);
                    break;
                    }
                }
            }
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                case 0:
                    {
                    return this->param_04_value;
                    }
                case 1:
                    {
                    return this->param_05_value;
                    }
                case 2:
                    {
                    return this->param_06_value;
                    }
                case 3:
                    {
                    return this->param_07_value;
                    }
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 4;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                case 0:
                    {
                    return "attack";
                    }
                case 1:
                    {
                    return "decay";
                    }
                case 2:
                    {
                    return "sustain";
                    }
                case 3:
                    {
                    return "release";
                    }
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                case 0:
                    {
                    return "poly/p_obj-18/attack";
                    }
                case 1:
                    {
                    return "poly/p_obj-18/decay";
                    }
                case 2:
                    {
                    return "poly/p_obj-18/sustain";
                    }
                case 3:
                    {
                    return "poly/p_obj-18/release";
                    }
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
                {
                    switch (index) {
                    case 0:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 30;
                        info->min = 0;
                        info->max = 5000;
                        info->exponent = 3;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    case 1:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 200;
                        info->min = 1;
                        info->max = 5000;
                        info->exponent = 3;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    case 2:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 0.5;
                        info->min = 0;
                        info->max = 1;
                        info->exponent = 0.8;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    case 3:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 300;
                        info->min = 1;
                        info->max = 90000;
                        info->exponent = 5;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    }
                }
            }
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                case 2:
                    {
                    {
                        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                        ParameterValue normalizedValue = (value - 0) / (1 - 0);
            
                        {
                            if (normalizedValue != 0.0) {
                                normalizedValue = rnbo_exp(
                                    ((normalizedValue <= 0 ? 0 : rnbo_log(normalizedValue))) * 1. / (number)0.8
                                );
                            }
                        }
            
                        return normalizedValue;
                    }
                    }
                case 0:
                    {
                    {
                        value = (value < 0 ? 0 : (value > 5000 ? 5000 : value));
                        ParameterValue normalizedValue = (value - 0) / (5000 - 0);
            
                        {
                            if (normalizedValue != 0.0) {
                                normalizedValue = rnbo_exp(((normalizedValue <= 0 ? 0 : rnbo_log(normalizedValue))) * 1. / (number)3);
                            }
                        }
            
                        return normalizedValue;
                    }
                    }
                case 1:
                    {
                    {
                        value = (value < 1 ? 1 : (value > 5000 ? 5000 : value));
                        ParameterValue normalizedValue = (value - 1) / (5000 - 1);
            
                        {
                            if (normalizedValue != 0.0) {
                                normalizedValue = rnbo_exp(((normalizedValue <= 0 ? 0 : rnbo_log(normalizedValue))) * 1. / (number)3);
                            }
                        }
            
                        return normalizedValue;
                    }
                    }
                case 3:
                    {
                    {
                        value = (value < 1 ? 1 : (value > 90000 ? 90000 : value));
                        ParameterValue normalizedValue = (value - 1) / (90000 - 1);
            
                        {
                            if (normalizedValue != 0.0) {
                                normalizedValue = rnbo_exp(((normalizedValue <= 0 ? 0 : rnbo_log(normalizedValue))) * 1. / (number)5);
                            }
                        }
            
                        return normalizedValue;
                    }
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                case 2:
                    {
                    {
                        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                        {
                            if (value == 0.0) {
                                return 0;
                            } else {
                                return 0 + rnbo_exp(((value <= 0 ? 0 : rnbo_log(value))) * 0.8) * (1 - 0);
                            }
                        }
                    }
                    }
                case 0:
                    {
                    {
                        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                        {
                            if (value == 0.0) {
                                return 0;
                            } else {
                                return 0 + rnbo_exp(((value <= 0 ? 0 : rnbo_log(value))) * 3) * (5000 - 0);
                            }
                        }
                    }
                    }
                case 1:
                    {
                    {
                        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                        {
                            if (value == 0.0) {
                                return 1;
                            } else {
                                return 1 + rnbo_exp(((value <= 0 ? 0 : rnbo_log(value))) * 3) * (5000 - 1);
                            }
                        }
                    }
                    }
                case 3:
                    {
                    {
                        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                        {
                            if (value == 0.0) {
                                return 1;
                            } else {
                                return 1 + rnbo_exp(((value <= 0 ? 0 : rnbo_log(value))) * 5) * (90000 - 1);
                            }
                        }
                    }
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                case 0:
                    {
                    return this->param_04_value_constrain(value);
                    }
                case 1:
                    {
                    return this->param_05_value_constrain(value);
                    }
                case 2:
                    {
                    return this->param_06_value_constrain(value);
                    }
                case 3:
                    {
                    return this->param_07_value_constrain(value);
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            void param_04_value_set(number v) {
                v = this->param_04_value_constrain(v);
                this->param_04_value = v;
                this->sendParameter(0, false);
            
                if (this->param_04_value != this->param_04_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_04_lastValue = this->param_04_value;
                }
            
                this->gen_01_in3_set(v);
            }
            
            void param_05_value_set(number v) {
                v = this->param_05_value_constrain(v);
                this->param_05_value = v;
                this->sendParameter(1, false);
            
                if (this->param_05_value != this->param_05_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_05_lastValue = this->param_05_value;
                }
            
                this->gen_01_in4_set(v);
            }
            
            void param_06_value_set(number v) {
                v = this->param_06_value_constrain(v);
                this->param_06_value = v;
                this->sendParameter(2, false);
            
                if (this->param_06_value != this->param_06_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_06_lastValue = this->param_06_value;
                }
            
                this->gen_01_in5_set(v);
            }
            
            void param_07_value_set(number v) {
                v = this->param_07_value_constrain(v);
                this->param_07_value = v;
                this->sendParameter(3, false);
            
                if (this->param_07_value != this->param_07_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_07_lastValue = this->param_07_value;
                }
            
                this->gen_01_in6_set(v);
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 2;
            }
            
            Index getNumOutputChannels() const {
                return 2;
            }
            
            void initializeObjects() {
                this->gen_01_sustain_init();
                this->gen_01_attack_has_ended_init();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime());
            
                {
                    this->scheduleParamInit(0, 0);
                }
            
                {
                    this->scheduleParamInit(1, 0);
                }
            
                {
                    this->scheduleParamInit(2, 0);
                }
            
                {
                    this->scheduleParamInit(3, 0);
                }
            }
            
            void allocateDataRefs() {}
            
            static number param_04_value_constrain(number v) {
                v = (v > 5000 ? 5000 : (v < 0 ? 0 : v));
                return v;
            }
            
            void gen_01_in3_set(number v) {
                this->gen_01_in3 = v;
            }
            
            static number param_05_value_constrain(number v) {
                v = (v > 5000 ? 5000 : (v < 1 ? 1 : v));
                return v;
            }
            
            void gen_01_in4_set(number v) {
                this->gen_01_in4 = v;
            }
            
            static number param_06_value_constrain(number v) {
                v = (v > 1 ? 1 : (v < 0 ? 0 : v));
                return v;
            }
            
            void gen_01_in5_set(number v) {
                this->gen_01_in5 = v;
            }
            
            static number param_07_value_constrain(number v) {
                v = (v > 90000 ? 90000 : (v < 1 ? 1 : v));
                return v;
            }
            
            void gen_01_in6_set(number v) {
                this->gen_01_in6 = v;
            }
            
            void gen_01_perform(
                const Sample * in1,
                const Sample * in2,
                number in3,
                number in4,
                number in5,
                number in6,
                number attack_lockout,
                SampleValue * out1,
                Index n
            ) {
                RNBO_UNUSED(attack_lockout);
                auto __gen_01_sustain_value = this->gen_01_sustain_value;
                auto __gen_01_attack_has_ended_value = this->gen_01_attack_has_ended_value;
                auto min_1_0 = this->maximum(in3, 0.1);
                auto min_2_1 = this->maximum(in4, 0.1);
                number clamp_3_2 = (in5 > 1 ? 1 : (in5 < 0 ? 0 : in5));
                auto min_4_3 = this->maximum(in6, 0.1);
                number attack_iter_interval_8 = this->mstosamps(min_1_0) * 0.33333333333333;
                number release_iter_interval_9 = this->mstosamps(min_4_3) * 0.33333333333333;
                number decay_iter_interval_10 = this->mstosamps(min_2_1) * 0.33333333333333;
                number sustain_smoothing_12 = 1 - ((this->mstosamps(20) == 0. ? 0. : (number)1 / this->mstosamps(20)));
                Index i;
            
                for (i = 0; i < n; i++) {
                    number trigger_5 = this->gen_01_delta_4_next(in2[(Index)i] > 0) > 0;
                    number is_released_6 = in1[(Index)i] == 0;
                    number is_attacking_7 = ((bool)(trigger_5) || (bool)(!(bool)(__gen_01_attack_has_ended_value))) && ((bool)(!(bool)(is_released_6)) || 0);
                    number decay_iter_interval_5_11 = !(bool)(is_released_6) * decay_iter_interval_10 + is_released_6 * release_iter_interval_9;
                    __gen_01_sustain_value = clamp_3_2 + sustain_smoothing_12 * (__gen_01_sustain_value - clamp_3_2);
                    number ad_target_13 = (is_attacking_7 > 0 ? 1.0523956964913 : -0.052395696491256);
                    number asr_target_14 = ((bool)(!(bool)(is_released_6)) || (bool)(is_attacking_7) ? 1.0523956964913 : -0.052395696491256);
                    number ad_16 = this->gen_01_slide_15_next(ad_target_13, attack_iter_interval_8, decay_iter_interval_5_11);
                    number ad_6_17 = (ad_16 > 1 ? 1 : (ad_16 < 0 ? 0 : ad_16));
                    number asr_19 = this->gen_01_slide_18_next(asr_target_14, attack_iter_interval_8, release_iter_interval_9);
                    number asr_7_20 = (asr_19 > 1 ? 1 : (asr_19 < 0 ? 0 : asr_19));
                    __gen_01_attack_has_ended_value = (bool)(!(bool)(is_attacking_7)) || ad_6_17 >= 1;
                    number expr_8_21 = ad_6_17 + __gen_01_sustain_value * (asr_7_20 - ad_6_17);
                    out1[(Index)i] = expr_8_21;
                }
            
                this->gen_01_attack_has_ended_value = __gen_01_attack_has_ended_value;
                this->gen_01_sustain_value = __gen_01_sustain_value;
            }
            
            void dspexpr_05_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void signalforwarder_03_perform(const SampleValue * input, SampleValue * output, Index n) {
                for (Index i = 0; i < n; i++) {
                    output[(Index)i] = input[(Index)i];
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            number gen_01_sustain_getvalue() {
                return this->gen_01_sustain_value;
            }
            
            void gen_01_sustain_setvalue(number val) {
                this->gen_01_sustain_value = val;
            }
            
            void gen_01_sustain_reset() {
                this->gen_01_sustain_value = 0;
            }
            
            void gen_01_sustain_init() {
                this->gen_01_sustain_value = 0.5;
            }
            
            number gen_01_attack_has_ended_getvalue() {
                return this->gen_01_attack_has_ended_value;
            }
            
            void gen_01_attack_has_ended_setvalue(number val) {
                this->gen_01_attack_has_ended_value = val;
            }
            
            void gen_01_attack_has_ended_reset() {
                this->gen_01_attack_has_ended_value = 0;
            }
            
            void gen_01_attack_has_ended_init() {
                this->gen_01_attack_has_ended_value = 0;
            }
            
            number gen_01_delta_4_next(number x) {
                number temp = (number)(x - this->gen_01_delta_4_prev);
                this->gen_01_delta_4_prev = x;
                return temp;
            }
            
            void gen_01_delta_4_dspsetup() {
                this->gen_01_delta_4_reset();
            }
            
            void gen_01_delta_4_reset() {
                this->gen_01_delta_4_prev = 0;
            }
            
            number gen_01_slide_15_next(number x, number up, number down) {
                number temp = x - this->gen_01_slide_15_prev;
                auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
                auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
                this->gen_01_slide_15_prev = this->gen_01_slide_15_prev + ((x > this->gen_01_slide_15_prev ? iup : idown)) * temp;
                return this->gen_01_slide_15_prev;
            }
            
            void gen_01_slide_15_reset() {
                this->gen_01_slide_15_prev = 0;
            }
            
            number gen_01_slide_18_next(number x, number up, number down) {
                number temp = x - this->gen_01_slide_18_prev;
                auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
                auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
                this->gen_01_slide_18_prev = this->gen_01_slide_18_prev + ((x > this->gen_01_slide_18_prev ? iup : idown)) * temp;
                return this->gen_01_slide_18_prev;
            }
            
            void gen_01_slide_18_reset() {
                this->gen_01_slide_18_prev = 0;
            }
            
            void gen_01_dspsetup(bool force) {
                if ((bool)(this->gen_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->gen_01_setupDone = true;
                this->gen_01_delta_4_dspsetup();
            }
            
            void param_04_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_04_value;
            }
            
            void param_04_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_04_value_set(preset["value"]);
            }
            
            void param_05_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_05_value;
            }
            
            void param_05_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_05_value_set(preset["value"]);
            }
            
            void param_06_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_06_value;
            }
            
            void param_06_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_06_value_set(preset["value"]);
            }
            
            void param_07_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_07_value;
            }
            
            void param_07_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_07_value_set(preset["value"]);
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                dspexpr_05_in1 = 0;
                dspexpr_05_in2 = 0;
                gen_01_in1 = 0;
                gen_01_in2 = 0;
                gen_01_in3 = 0;
                gen_01_in4 = 0;
                gen_01_in5 = 0;
                gen_01_in6 = 0;
                gen_01_attack_lockout = 0;
                param_04_value = 30;
                param_05_value = 200;
                param_06_value = 0.5;
                param_07_value = 300;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                signals[0] = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                gen_01_sustain_value = 0;
                gen_01_attack_has_ended_value = 0;
                gen_01_delta_4_prev = 0;
                gen_01_slide_15_prev = 0;
                gen_01_slide_18_prev = 0;
                gen_01_setupDone = false;
                param_04_lastValue = 0;
                param_05_lastValue = 0;
                param_06_lastValue = 0;
                param_07_lastValue = 0;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number dspexpr_05_in1;
                number dspexpr_05_in2;
                number gen_01_in1;
                number gen_01_in2;
                number gen_01_in3;
                number gen_01_in4;
                number gen_01_in5;
                number gen_01_in6;
                number gen_01_attack_lockout;
                number param_04_value;
                number param_05_value;
                number param_06_value;
                number param_07_value;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                SampleValue * signals[1];
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number gen_01_sustain_value;
                number gen_01_attack_has_ended_value;
                number gen_01_delta_4_prev;
                number gen_01_slide_15_prev;
                number gen_01_slide_18_prev;
                bool gen_01_setupDone;
                number param_04_lastValue;
                number param_05_lastValue;
                number param_06_lastValue;
                number param_07_lastValue;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_46 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_48;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_46()
            {
            }
            
            ~RNBOSubpatcher_46()
            {
            }
            
            virtual RNBOSubpatcher_48* getPatcher() const {
                return static_cast<RNBOSubpatcher_48 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            number samplerate() {
                return this->sr;
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
                const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
                const SampleValue * in3 = (numInputs >= 3 && inputs[2] ? inputs[2] : this->zeroBuffer);
                this->dspexpr_07_perform(in1, in2, this->signals[0], n);
            
                this->cycle_tilde_02_perform(
                    this->signals[0],
                    this->cycle_tilde_02_phase_offset,
                    this->signals[1],
                    this->dummyBuffer,
                    n
                );
            
                this->dspexpr_09_perform(this->signals[0], in3, this->signals[2], n);
                this->dspexpr_08_perform(this->signals[1], this->signals[2], this->signals[0], n);
                this->dspexpr_06_perform(in1, this->signals[0], this->signals[2], n);
                this->cycle_tilde_01_perform(this->signals[2], this->cycle_tilde_01_phase_offset, out1, out2, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 3; i++) {
                        this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                    }
            
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->cycle_tilde_02_dspsetup(forceDSPSetup);
                this->cycle_tilde_01_dspsetup(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& ) {}
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
                this->updateTime(time);
            
                if (index == 0) {
                    this->cycle_tilde_01_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->RNBODefaultSinus);
                    this->cycle_tilde_01_bufferUpdated();
                    this->cycle_tilde_02_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->RNBODefaultSinus);
                    this->cycle_tilde_02_bufferUpdated();
                }
            }
            
            void initialize() {
                this->assign_defaults();
                this->setState();
                this->cycle_tilde_01_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->RNBODefaultSinus);
                this->cycle_tilde_02_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->RNBODefaultSinus);
            }
            
            protected:
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 3;
            }
            
            Index getNumOutputChannels() const {
                return 2;
            }
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {
                this->cycle_tilde_01_buffer->requestSize(16384, 1);
                this->cycle_tilde_01_buffer->setSampleRate(this->sr);
                this->cycle_tilde_02_buffer->requestSize(16384, 1);
                this->cycle_tilde_02_buffer->setSampleRate(this->sr);
                this->cycle_tilde_01_buffer = this->cycle_tilde_01_buffer->allocateIfNeeded();
                this->cycle_tilde_02_buffer = this->cycle_tilde_02_buffer->allocateIfNeeded();
            }
            
            void dspexpr_07_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void cycle_tilde_02_perform(
                const Sample * frequency,
                number phase_offset,
                SampleValue * out1,
                SampleValue * out2,
                Index n
            ) {
                RNBO_UNUSED(phase_offset);
                auto __cycle_tilde_02_f2i = this->cycle_tilde_02_f2i;
                auto __cycle_tilde_02_buffer = this->cycle_tilde_02_buffer;
                auto __cycle_tilde_02_phasei = this->cycle_tilde_02_phasei;
                Index i;
            
                for (i = 0; i < n; i++) {
                    {
                        uint32_t uint_phase;
            
                        {
                            {
                                uint_phase = __cycle_tilde_02_phasei;
                            }
                        }
            
                        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
                        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
                        number y0 = __cycle_tilde_02_buffer[(Index)idx];
                        number y1 = __cycle_tilde_02_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
                        number y = y0 + frac * (y1 - y0);
            
                        {
                            uint32_t pincr = (uint32_t)(uint32_trunc(frequency[(Index)i] * __cycle_tilde_02_f2i));
                            __cycle_tilde_02_phasei = uint32_add(__cycle_tilde_02_phasei, pincr);
                        }
            
                        out1[(Index)i] = y;
                        out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
                        continue;
                    }
                }
            
                this->cycle_tilde_02_phasei = __cycle_tilde_02_phasei;
            }
            
            void dspexpr_09_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void dspexpr_08_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void dspexpr_06_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void cycle_tilde_01_perform(
                const Sample * frequency,
                number phase_offset,
                SampleValue * out1,
                SampleValue * out2,
                Index n
            ) {
                RNBO_UNUSED(phase_offset);
                auto __cycle_tilde_01_f2i = this->cycle_tilde_01_f2i;
                auto __cycle_tilde_01_buffer = this->cycle_tilde_01_buffer;
                auto __cycle_tilde_01_phasei = this->cycle_tilde_01_phasei;
                Index i;
            
                for (i = 0; i < n; i++) {
                    {
                        uint32_t uint_phase;
            
                        {
                            {
                                uint_phase = __cycle_tilde_01_phasei;
                            }
                        }
            
                        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
                        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
                        number y0 = __cycle_tilde_01_buffer[(Index)idx];
                        number y1 = __cycle_tilde_01_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
                        number y = y0 + frac * (y1 - y0);
            
                        {
                            uint32_t pincr = (uint32_t)(uint32_trunc(frequency[(Index)i] * __cycle_tilde_01_f2i));
                            __cycle_tilde_01_phasei = uint32_add(__cycle_tilde_01_phasei, pincr);
                        }
            
                        out1[(Index)i] = y;
                        out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
                        continue;
                    }
                }
            
                this->cycle_tilde_01_phasei = __cycle_tilde_01_phasei;
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            number cycle_tilde_01_ph_next(number freq, number reset) {
                {
                    {
                        if (reset >= 0.)
                            this->cycle_tilde_01_ph_currentPhase = reset;
                    }
                }
            
                number pincr = freq * this->cycle_tilde_01_ph_conv;
            
                if (this->cycle_tilde_01_ph_currentPhase < 0.)
                    this->cycle_tilde_01_ph_currentPhase = 1. + this->cycle_tilde_01_ph_currentPhase;
            
                if (this->cycle_tilde_01_ph_currentPhase > 1.)
                    this->cycle_tilde_01_ph_currentPhase = this->cycle_tilde_01_ph_currentPhase - 1.;
            
                number tmp = this->cycle_tilde_01_ph_currentPhase;
                this->cycle_tilde_01_ph_currentPhase += pincr;
                return tmp;
            }
            
            void cycle_tilde_01_ph_reset() {
                this->cycle_tilde_01_ph_currentPhase = 0;
            }
            
            void cycle_tilde_01_ph_dspsetup() {
                this->cycle_tilde_01_ph_conv = (number)1 / this->sr;
            }
            
            void cycle_tilde_01_dspsetup(bool force) {
                if ((bool)(this->cycle_tilde_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->cycle_tilde_01_phasei = 0;
                this->cycle_tilde_01_f2i = (number)4294967296 / this->samplerate();
                this->cycle_tilde_01_wrap = (long)(this->cycle_tilde_01_buffer->getSize()) - 1;
                this->cycle_tilde_01_setupDone = true;
                this->cycle_tilde_01_ph_dspsetup();
            }
            
            void cycle_tilde_01_bufferUpdated() {
                this->cycle_tilde_01_wrap = (long)(this->cycle_tilde_01_buffer->getSize()) - 1;
            }
            
            number cycle_tilde_02_ph_next(number freq, number reset) {
                {
                    {
                        if (reset >= 0.)
                            this->cycle_tilde_02_ph_currentPhase = reset;
                    }
                }
            
                number pincr = freq * this->cycle_tilde_02_ph_conv;
            
                if (this->cycle_tilde_02_ph_currentPhase < 0.)
                    this->cycle_tilde_02_ph_currentPhase = 1. + this->cycle_tilde_02_ph_currentPhase;
            
                if (this->cycle_tilde_02_ph_currentPhase > 1.)
                    this->cycle_tilde_02_ph_currentPhase = this->cycle_tilde_02_ph_currentPhase - 1.;
            
                number tmp = this->cycle_tilde_02_ph_currentPhase;
                this->cycle_tilde_02_ph_currentPhase += pincr;
                return tmp;
            }
            
            void cycle_tilde_02_ph_reset() {
                this->cycle_tilde_02_ph_currentPhase = 0;
            }
            
            void cycle_tilde_02_ph_dspsetup() {
                this->cycle_tilde_02_ph_conv = (number)1 / this->sr;
            }
            
            void cycle_tilde_02_dspsetup(bool force) {
                if ((bool)(this->cycle_tilde_02_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->cycle_tilde_02_phasei = 0;
                this->cycle_tilde_02_f2i = (number)4294967296 / this->samplerate();
                this->cycle_tilde_02_wrap = (long)(this->cycle_tilde_02_buffer->getSize()) - 1;
                this->cycle_tilde_02_setupDone = true;
                this->cycle_tilde_02_ph_dspsetup();
            }
            
            void cycle_tilde_02_bufferUpdated() {
                this->cycle_tilde_02_wrap = (long)(this->cycle_tilde_02_buffer->getSize()) - 1;
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                cycle_tilde_01_frequency = 0;
                cycle_tilde_01_phase_offset = 0;
                dspexpr_06_in1 = 0;
                dspexpr_06_in2 = 0;
                dspexpr_07_in1 = 0;
                dspexpr_07_in2 = 0;
                cycle_tilde_02_frequency = 0;
                cycle_tilde_02_phase_offset = 0;
                dspexpr_08_in1 = 0;
                dspexpr_08_in2 = 0;
                dspexpr_09_in1 = 0;
                dspexpr_09_in2 = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                signals[0] = nullptr;
                signals[1] = nullptr;
                signals[2] = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                cycle_tilde_01_wrap = 0;
                cycle_tilde_01_ph_currentPhase = 0;
                cycle_tilde_01_ph_conv = 0;
                cycle_tilde_01_setupDone = false;
                cycle_tilde_02_wrap = 0;
                cycle_tilde_02_ph_currentPhase = 0;
                cycle_tilde_02_ph_conv = 0;
                cycle_tilde_02_setupDone = false;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number cycle_tilde_01_frequency;
                number cycle_tilde_01_phase_offset;
                number dspexpr_06_in1;
                number dspexpr_06_in2;
                number dspexpr_07_in1;
                number dspexpr_07_in2;
                number cycle_tilde_02_frequency;
                number cycle_tilde_02_phase_offset;
                number dspexpr_08_in1;
                number dspexpr_08_in2;
                number dspexpr_09_in1;
                number dspexpr_09_in2;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                SampleValue * signals[3];
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                Float64BufferRef cycle_tilde_01_buffer;
                long cycle_tilde_01_wrap;
                uint32_t cycle_tilde_01_phasei;
                SampleValue cycle_tilde_01_f2i;
                number cycle_tilde_01_ph_currentPhase;
                number cycle_tilde_01_ph_conv;
                bool cycle_tilde_01_setupDone;
                Float64BufferRef cycle_tilde_02_buffer;
                long cycle_tilde_02_wrap;
                uint32_t cycle_tilde_02_phasei;
                SampleValue cycle_tilde_02_f2i;
                number cycle_tilde_02_ph_currentPhase;
                number cycle_tilde_02_ph_conv;
                bool cycle_tilde_02_setupDone;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_47 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_48;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_47()
            {
            }
            
            ~RNBOSubpatcher_47()
            {
            }
            
            virtual RNBOSubpatcher_48* getPatcher() const {
                return static_cast<RNBOSubpatcher_48 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            inline number safesqrt(number num) {
                return (num > 0.0 ? rnbo_sqrt(num) : 0.0);
            }
            
            Index vectorsize() {
                return this->vs;
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
                const SampleValue * in3 = (numInputs >= 3 && inputs[2] ? inputs[2] : this->zeroBuffer);
            
                this->filtercoeff_01_perform(
                    in2,
                    this->filtercoeff_01_gain,
                    in3,
                    this->signals[0],
                    this->signals[1],
                    this->signals[2],
                    this->signals[3],
                    this->signals[4],
                    n
                );
            
                this->biquad_tilde_01_perform(
                    in1,
                    this->signals[0],
                    this->signals[1],
                    this->signals[2],
                    this->signals[3],
                    this->signals[4],
                    out1,
                    n
                );
            
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 5; i++) {
                        this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                    }
            
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->filtercoeff_01_dspsetup(forceDSPSetup);
                this->biquad_tilde_01_dspsetup(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& ) {}
            
            void processTempoEvent(MillisecondTime , Tempo ) {}
            
            void processTransportEvent(MillisecondTime , TransportState ) {}
            
            void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
            
            void onSampleRateChanged(double ) {}
            
            void processTimeSignatureEvent(MillisecondTime , int , int ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 3;
            }
            
            Index getNumOutputChannels() const {
                return 1;
            }
            
            void initializeObjects() {}
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {}
            
            void allocateDataRefs() {}
            
            void filtercoeff_01_perform(
                const Sample * frequency,
                number gain,
                const Sample * q,
                SampleValue * a0,
                SampleValue * a1,
                SampleValue * a2,
                SampleValue * b1,
                SampleValue * b2,
                Index n
            ) {
                RNBO_UNUSED(gain);
                auto __filtercoeff_01_activeResamp = this->filtercoeff_01_activeResamp;
                auto __filtercoeff_01_resamp_counter = this->filtercoeff_01_resamp_counter;
                auto __filtercoeff_01_K_EPSILON = this->filtercoeff_01_K_EPSILON;
            
                for (Index i = 0; i < n; i++) {
                    number local_q = q[(Index)i];
                    number local_gain = 1;
            
                    if (local_gain < 0)
                        local_gain = 0;
            
                    number local_frequency = frequency[(Index)i];
            
                    if (local_q < __filtercoeff_01_K_EPSILON)
                        local_q = __filtercoeff_01_K_EPSILON;
            
                    local_frequency = (local_frequency > this->sr * 0.5 ? this->sr * 0.5 : (local_frequency < 1 ? 1 : local_frequency));
                    __filtercoeff_01_resamp_counter--;
            
                    if (__filtercoeff_01_resamp_counter <= 0) {
                        __filtercoeff_01_resamp_counter = __filtercoeff_01_activeResamp;
                        this->filtercoeff_01_updateTerms(local_frequency, local_gain, local_q);
                    }
            
                    a0[(Index)i] = this->filtercoeff_01_la0;
                    a1[(Index)i] = this->filtercoeff_01_la1;
                    a2[(Index)i] = this->filtercoeff_01_la2;
                    b1[(Index)i] = this->filtercoeff_01_lb1;
                    b2[(Index)i] = this->filtercoeff_01_lb2;
                }
            
                this->filtercoeff_01_resamp_counter = __filtercoeff_01_resamp_counter;
            }
            
            void biquad_tilde_01_perform(
                const Sample * x,
                const Sample * a0,
                const Sample * a1,
                const Sample * a2,
                const Sample * b1,
                const Sample * b2,
                SampleValue * out1,
                Index n
            ) {
                auto __biquad_tilde_01_y2 = this->biquad_tilde_01_y2;
                auto __biquad_tilde_01_y1 = this->biquad_tilde_01_y1;
                auto __biquad_tilde_01_x2 = this->biquad_tilde_01_x2;
                auto __biquad_tilde_01_x1 = this->biquad_tilde_01_x1;
                Index i;
            
                for (i = 0; i < n; i++) {
                    number tmp = x[(Index)i] * a0[(Index)i] + __biquad_tilde_01_x1 * a1[(Index)i] + __biquad_tilde_01_x2 * a2[(Index)i] - (__biquad_tilde_01_y1 * b1[(Index)i] + __biquad_tilde_01_y2 * b2[(Index)i]);
                    __biquad_tilde_01_x2 = __biquad_tilde_01_x1;
                    __biquad_tilde_01_x1 = x[(Index)i];
                    __biquad_tilde_01_y2 = __biquad_tilde_01_y1;
                    __biquad_tilde_01_y1 = tmp;
                    out1[(Index)i] = tmp;
                }
            
                this->biquad_tilde_01_x1 = __biquad_tilde_01_x1;
                this->biquad_tilde_01_x2 = __biquad_tilde_01_x2;
                this->biquad_tilde_01_y1 = __biquad_tilde_01_y1;
                this->biquad_tilde_01_y2 = __biquad_tilde_01_y2;
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            void biquad_tilde_01_reset() {
                this->biquad_tilde_01_x1 = 0;
                this->biquad_tilde_01_x2 = 0;
                this->biquad_tilde_01_y1 = 0;
                this->biquad_tilde_01_y2 = 0;
            }
            
            void biquad_tilde_01_dspsetup(bool force) {
                if ((bool)(this->biquad_tilde_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->biquad_tilde_01_reset();
                this->biquad_tilde_01_setupDone = true;
            }
            
            array<number, 5> filtercoeff_01_localop_next(number frequency, number q, number gain, number type) {
                number omega = frequency * this->filtercoeff_01_localop_twopi_over_sr;
                this->filtercoeff_01_localop_cs = rnbo_cos(omega);
                this->filtercoeff_01_localop_sn = rnbo_sin(omega);
                this->filtercoeff_01_localop_one_over_gain = (gain >= 0 ? (number)1 / gain : 0.0);
                this->filtercoeff_01_localop_one_over_q = (number)1 / q;
                this->filtercoeff_01_localop_alpha = this->filtercoeff_01_localop_sn * 0.5 * this->filtercoeff_01_localop_one_over_q;
            
                switch ((int)type) {
                case 5:
                    {
                    this->filtercoeff_01_localop_A = this->safesqrt(gain);
            
                    this->filtercoeff_01_localop_beta = this->safesqrt(
                        (this->filtercoeff_01_localop_A * this->filtercoeff_01_localop_A + 1.) * this->filtercoeff_01_localop_one_over_q - (this->filtercoeff_01_localop_A - 1.) * (this->filtercoeff_01_localop_A - 1.)
                    );
            
                    this->filtercoeff_01_localop_b0 = (number)1 / (this->filtercoeff_01_localop_A + 1. + (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs + this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn);
                    break;
                    }
                case 6:
                    {
                    this->filtercoeff_01_localop_A = this->safesqrt(gain);
            
                    this->filtercoeff_01_localop_beta = this->safesqrt(
                        (this->filtercoeff_01_localop_A * this->filtercoeff_01_localop_A + 1.) * this->filtercoeff_01_localop_one_over_q - (this->filtercoeff_01_localop_A - 1.) * (this->filtercoeff_01_localop_A - 1.)
                    );
            
                    this->filtercoeff_01_localop_b0 = (number)1 / (this->filtercoeff_01_localop_A + 1. - (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs + this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn);
                    break;
                    }
                case 4:
                    {
                    this->filtercoeff_01_localop_A = this->safesqrt(gain);
                    this->filtercoeff_01_localop_one_over_a = (this->filtercoeff_01_localop_A == 0 ? 0 : (number)1 / this->filtercoeff_01_localop_A);
                    this->filtercoeff_01_localop_b0 = (number)1 / (1. + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_a);
                    break;
                    }
                case 9:
                case 10:
                case 11:
                case 13:
                case 14:
                    {
                    this->filtercoeff_01_localop_b0 = (number)1 / (1. + this->filtercoeff_01_localop_alpha);
                    this->filtercoeff_01_localop_b0g = (number)1 / (this->filtercoeff_01_localop_one_over_gain + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_gain);
                    break;
                    }
                default:
                    {
                    this->filtercoeff_01_localop_b0 = (number)1 / (1. + this->filtercoeff_01_localop_alpha);
                    break;
                    }
                }
            
                switch ((int)type) {
                case 0:
                    {
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_la2 = (1. - this->filtercoeff_01_localop_cs) * 0.5 * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la1 = (1. - this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    break;
                    }
                case 1:
                    {
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_la2 = (1. + this->filtercoeff_01_localop_cs) * 0.5 * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la1 = -(1. + this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    break;
                    }
                case 2:
                    {
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la1 = 0.;
                    this->filtercoeff_01_localop_la2 = -this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    break;
                    }
                case 7:
                    {
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_alpha * q * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la1 = 0.;
                    this->filtercoeff_01_localop_la2 = -this->filtercoeff_01_localop_alpha * q * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    break;
                    }
                case 3:
                    {
                    this->filtercoeff_01_localop_la1 = this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_la2 = this->filtercoeff_01_localop_b0;
                    break;
                    }
                case 8:
                    {
                    this->filtercoeff_01_localop_la1 = this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = this->filtercoeff_01_localop_la0 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la2 = 1.0;
                    break;
                    }
                case 4:
                    {
                    this->filtercoeff_01_localop_la0 = (1. + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_A) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la1 = this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la2 = (1. - this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_A) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_a) * this->filtercoeff_01_localop_b0;
                    break;
                    }
                case 5:
                    {
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A + 1. - (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs + this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la1 = 2. * this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A - 1 - (this->filtercoeff_01_localop_A + 1) * this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la2 = this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A + 1. - (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs - this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb1 = -2. * (this->filtercoeff_01_localop_A - 1. + (this->filtercoeff_01_localop_A + 1.) * this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (this->filtercoeff_01_localop_A + 1. + (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs - this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
                    break;
                    }
                case 6:
                    {
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A + 1. + (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs + this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la1 = -2. * this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A - 1. + (this->filtercoeff_01_localop_A + 1.) * this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la2 = this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A + 1. + (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs - this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb1 = 2. * (this->filtercoeff_01_localop_A - 1. - (this->filtercoeff_01_localop_A + 1.) * this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (this->filtercoeff_01_localop_A + 1. - (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs - this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
                    break;
                    }
                case 9:
                    {
                    this->filtercoeff_01_localop_b0g = (number)1 / (this->filtercoeff_01_localop_one_over_gain + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_gain);
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_la2 = (1. - this->filtercoeff_01_localop_cs) * 0.5 * this->filtercoeff_01_localop_b0g;
                    this->filtercoeff_01_localop_la1 = (1. - this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0g;
                    this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    break;
                    }
                case 10:
                    {
                    this->filtercoeff_01_localop_b0g = (number)1 / (this->filtercoeff_01_localop_one_over_gain + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_gain);
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_la2 = (1. + this->filtercoeff_01_localop_cs) * 0.5 * this->filtercoeff_01_localop_b0g;
                    this->filtercoeff_01_localop_la1 = -(1. + this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0g;
                    this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    break;
                    }
                case 11:
                    {
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_alpha * gain * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la1 = 0.;
                    this->filtercoeff_01_localop_la2 = -this->filtercoeff_01_localop_alpha * gain * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    break;
                    }
                case 13:
                    {
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_alpha * gain * q * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la1 = 0.;
                    this->filtercoeff_01_localop_la2 = -this->filtercoeff_01_localop_alpha * gain * q * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    break;
                    }
                case 12:
                    {
                    this->filtercoeff_01_localop_b0g = (number)1 / (this->filtercoeff_01_localop_one_over_gain + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_gain);
                    this->filtercoeff_01_localop_la1 = this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la1 *= this->filtercoeff_01_localop_b0g;
                    this->filtercoeff_01_localop_lb1 *= this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_b0g;
                    this->filtercoeff_01_localop_la2 = this->filtercoeff_01_localop_b0g;
                    break;
                    }
                case 14:
                    {
                    this->filtercoeff_01_localop_b0g = (number)1 / (this->filtercoeff_01_localop_one_over_gain + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_gain);
                    this->filtercoeff_01_localop_la0 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0g;
                    this->filtercoeff_01_localop_la1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0g;
                    this->filtercoeff_01_localop_la2 = gain;
                    this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                    this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                    break;
                    }
                case 15:
                    {
                    this->filtercoeff_01_localop_la0 = 1;
                    this->filtercoeff_01_localop_la1 = 0;
                    this->filtercoeff_01_localop_la2 = 0;
                    this->filtercoeff_01_localop_lb1 = 0;
                    this->filtercoeff_01_localop_lb2 = 0;
                    }
                default:
                    {
                    break;
                    }
                }
            
                return {
                    this->filtercoeff_01_localop_la0,
                    this->filtercoeff_01_localop_la1,
                    this->filtercoeff_01_localop_la2,
                    this->filtercoeff_01_localop_lb1,
                    this->filtercoeff_01_localop_lb2
                };
            }
            
            void filtercoeff_01_localop_dspsetup() {
                this->filtercoeff_01_localop_twopi_over_sr = (number)6.283185307179586 / this->sr;
            }
            
            void filtercoeff_01_localop_reset() {
                this->filtercoeff_01_localop_internal = true;
                this->filtercoeff_01_localop_twopi_over_sr = 0;
                this->filtercoeff_01_localop_cs = 0;
                this->filtercoeff_01_localop_sn = 0;
                this->filtercoeff_01_localop_one_over_gain = 0;
                this->filtercoeff_01_localop_one_over_q = 0;
                this->filtercoeff_01_localop_alpha = 0;
                this->filtercoeff_01_localop_beta = 0;
                this->filtercoeff_01_localop_b0 = 0;
                this->filtercoeff_01_localop_b0g = 0;
                this->filtercoeff_01_localop_A = 0;
                this->filtercoeff_01_localop_one_over_a = 0;
                this->filtercoeff_01_localop_la0 = 0;
                this->filtercoeff_01_localop_la1 = 0;
                this->filtercoeff_01_localop_la2 = 0;
                this->filtercoeff_01_localop_lb1 = 0;
                this->filtercoeff_01_localop_lb2 = 0;
            }
            
            void filtercoeff_01_updateTerms(number local_frequency, number local_gain, number local_q) {
                if ((bool)(this->filtercoeff_01_force_update) || local_frequency != this->filtercoeff_01_last_frequency || local_q != this->filtercoeff_01_last_q || local_gain != this->filtercoeff_01_last_gain || this->filtercoeff_01_type != this->filtercoeff_01_last_type) {
                    array<number, 5> tmp = this->filtercoeff_01_localop_next(local_frequency, local_q, local_gain, this->filtercoeff_01_type);
                    this->filtercoeff_01_la0 = tmp[0];
                    this->filtercoeff_01_la1 = tmp[1];
                    this->filtercoeff_01_la2 = tmp[2];
                    this->filtercoeff_01_lb1 = tmp[3];
                    this->filtercoeff_01_lb2 = tmp[4];
                    this->filtercoeff_01_last_frequency = local_frequency;
                    this->filtercoeff_01_last_q = local_q;
                    this->filtercoeff_01_last_gain = local_gain;
                    this->filtercoeff_01_last_type = this->filtercoeff_01_type;
                    this->filtercoeff_01_force_update = false;
                }
            }
            
            void filtercoeff_01_dspsetup(bool force) {
                if ((bool)(this->filtercoeff_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                {
                    this->filtercoeff_01_activeResamp = this->vectorsize();
                }
            
                this->filtercoeff_01_resamp_counter = 0;
                this->filtercoeff_01_la0 = 0.;
                this->filtercoeff_01_la1 = 0.;
                this->filtercoeff_01_la2 = 0.;
                this->filtercoeff_01_lb1 = 0.;
                this->filtercoeff_01_lb2 = 0.;
                this->filtercoeff_01_last_frequency = -1.;
                this->filtercoeff_01_last_q = -1.;
                this->filtercoeff_01_last_gain = -1.;
                this->filtercoeff_01_last_type = this->filtercoeff_01_type;
                this->filtercoeff_01_force_update = true;
                this->filtercoeff_01_setupDone = true;
                this->filtercoeff_01_localop_dspsetup();
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                biquad_tilde_01_x = 0;
                biquad_tilde_01_a0 = 0;
                biquad_tilde_01_a1 = 0;
                biquad_tilde_01_a2 = 0;
                biquad_tilde_01_b1 = 0;
                biquad_tilde_01_b2 = 0;
                filtercoeff_01_frequency = 1000;
                filtercoeff_01_gain = 1;
                filtercoeff_01_q = 1;
                filtercoeff_01_type = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                signals[0] = nullptr;
                signals[1] = nullptr;
                signals[2] = nullptr;
                signals[3] = nullptr;
                signals[4] = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                biquad_tilde_01_x1 = 0;
                biquad_tilde_01_x2 = 0;
                biquad_tilde_01_y1 = 0;
                biquad_tilde_01_y2 = 0;
                biquad_tilde_01_setupDone = false;
                filtercoeff_01_K_EPSILON = 1e-9;
                filtercoeff_01_localop_internal = true;
                filtercoeff_01_setupDone = false;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number biquad_tilde_01_x;
                number biquad_tilde_01_a0;
                number biquad_tilde_01_a1;
                number biquad_tilde_01_a2;
                number biquad_tilde_01_b1;
                number biquad_tilde_01_b2;
                number filtercoeff_01_frequency;
                number filtercoeff_01_gain;
                number filtercoeff_01_q;
                Int filtercoeff_01_type;
                MillisecondTime _currentTime;
                SampleIndex audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                SampleValue * signals[5];
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number biquad_tilde_01_x1;
                number biquad_tilde_01_x2;
                number biquad_tilde_01_y1;
                number biquad_tilde_01_y2;
                bool biquad_tilde_01_setupDone;
                number filtercoeff_01_resamp_counter;
                number filtercoeff_01_activeResamp;
                number filtercoeff_01_K_EPSILON;
                number filtercoeff_01_la0;
                number filtercoeff_01_la1;
                number filtercoeff_01_la2;
                number filtercoeff_01_lb1;
                number filtercoeff_01_lb2;
                number filtercoeff_01_last_frequency;
                number filtercoeff_01_last_q;
                number filtercoeff_01_last_gain;
                Int filtercoeff_01_last_type;
                bool filtercoeff_01_force_update;
                bool filtercoeff_01_localop_internal;
                number filtercoeff_01_localop_twopi_over_sr;
                number filtercoeff_01_localop_cs;
                number filtercoeff_01_localop_sn;
                number filtercoeff_01_localop_one_over_gain;
                number filtercoeff_01_localop_one_over_q;
                number filtercoeff_01_localop_alpha;
                number filtercoeff_01_localop_beta;
                number filtercoeff_01_localop_b0;
                number filtercoeff_01_localop_b0g;
                number filtercoeff_01_localop_A;
                number filtercoeff_01_localop_one_over_a;
                number filtercoeff_01_localop_la0;
                number filtercoeff_01_localop_la1;
                number filtercoeff_01_localop_la2;
                number filtercoeff_01_localop_lb1;
                number filtercoeff_01_localop_lb2;
                bool filtercoeff_01_setupDone;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    RNBOSubpatcher_48()
    {
    }
    
    ~RNBOSubpatcher_48()
    {
        delete this->p_01;
        delete this->p_02;
        delete this->p_03;
        delete this->p_04;
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
    }
    
    inline number linearinterp(number frac, number x, number y) {
        return x + (y - x) * frac;
    }
    
    inline number safediv(number num, number denom) {
        return (denom == 0.0 ? 0.0 : num / denom);
    }
    
    number maximum(number x, number y) {
        return (x < y ? y : x);
    }
    
    Index getNumMidiInputPorts() const {
        return 1;
    }
    
    void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
        this->updateTime(time);
        this->notein_01_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    }
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        RNBO_UNUSED(numInputs);
        RNBO_UNUSED(inputs);
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    
        if (this->getIsMuted())
            return;
    
        this->mtof_tilde_01_perform(this->mtof_tilde_01_midivalue, this->signals[0], n);
    
        this->slide_tilde_02_perform(
            this->slide_tilde_02_x,
            this->slide_tilde_02_up,
            this->slide_tilde_02_down,
            this->signals[1],
            n
        );
    
        this->slide_tilde_03_perform(
            this->slide_tilde_03_x,
            this->slide_tilde_03_up,
            this->slide_tilde_03_down,
            this->signals[2],
            n
        );
    
        this->slide_tilde_04_perform(
            this->slide_tilde_04_x,
            this->slide_tilde_04_up,
            this->slide_tilde_04_down,
            this->signals[3],
            n
        );
    
        this->p_03_perform(
            this->signals[0],
            this->signals[1],
            this->signals[3],
            this->signals[4],
            this->dummyBuffer,
            n
        );
    
        this->ip_01_perform(this->signals[3], n);
        this->ip_02_perform(this->signals[1], n);
        this->p_02_perform(this->signals[4], this->signals[1], this->signals[0], this->dummyBuffer, n);
        this->p_04_perform(this->signals[0], this->signals[2], this->signals[3], this->signals[1], n);
        this->p_01_perform(this->signals[1], this->signals[3], this->signals[2], n);
        this->signaladder_01_perform(this->signals[3], out1, out1, n);
        this->signaladder_02_perform(this->signals[2], out2, out2, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 5; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->ip_01_sigbuf = resizeSignal(this->ip_01_sigbuf, this->maxvs, maxBlockSize);
            this->ip_02_sigbuf = resizeSignal(this->ip_02_sigbuf, this->maxvs, maxBlockSize);
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->ip_01_dspsetup(forceDSPSetup);
        this->ip_02_dspsetup(forceDSPSetup);
        this->p_01->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_02->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_03->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_04->prepareToProcess(sampleRate, maxBlockSize, force);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    void setVoiceIndex(Index index)  {
        this->_voiceIndex = index;
        this->p_01->setVoiceIndex(index);
        this->p_02->setVoiceIndex(index);
        this->p_03->setVoiceIndex(index);
        this->p_04->setVoiceIndex(index);
    }
    
    void setNoteNumber(Int noteNumber)  {
        this->_noteNumber = noteNumber;
        this->p_01->setNoteNumber(noteNumber);
        this->p_02->setNoteNumber(noteNumber);
        this->p_03->setNoteNumber(noteNumber);
        this->p_04->setNoteNumber(noteNumber);
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {
        this->p_01 = new RNBOSubpatcher_44();
        this->p_01->setEngineAndPatcher(this->getEngine(), this);
        this->p_01->initialize();
        this->p_01->setParameterOffset(this->getParameterOffset(this->p_01));
        this->p_02 = new RNBOSubpatcher_45();
        this->p_02->setEngineAndPatcher(this->getEngine(), this);
        this->p_02->initialize();
        this->p_02->setParameterOffset(this->getParameterOffset(this->p_02));
        this->p_03 = new RNBOSubpatcher_46();
        this->p_03->setEngineAndPatcher(this->getEngine(), this);
        this->p_03->initialize();
        this->p_03->setParameterOffset(this->getParameterOffset(this->p_03));
        this->p_04 = new RNBOSubpatcher_47();
        this->p_04->setEngineAndPatcher(this->getEngine(), this);
        this->p_04->initialize();
        this->p_04->setParameterOffset(this->getParameterOffset(this->p_04));
    }
    
    void getPreset(PatcherStateInterface& preset) {
        this->p_01->getPreset(getSubState(getSubState(preset, "__sps"), "stereo_delay"));
        this->p_02->getPreset(getSubState(getSubState(preset, "__sps"), "p_obj-18"));
        this->p_03->getPreset(getSubState(getSubState(preset, "__sps"), "osc.fm"));
        this->p_04->getPreset(getSubState(getSubState(preset, "__sps"), "filter.lp"));
    }
    
    void processTempoEvent(MillisecondTime time, Tempo tempo) {
        this->updateTime(time);
        this->p_01->processTempoEvent(time, tempo);
        this->p_02->processTempoEvent(time, tempo);
        this->p_03->processTempoEvent(time, tempo);
        this->p_04->processTempoEvent(time, tempo);
    }
    
    void processTransportEvent(MillisecondTime time, TransportState state) {
        this->updateTime(time);
        this->p_01->processTransportEvent(time, state);
        this->p_02->processTransportEvent(time, state);
        this->p_03->processTransportEvent(time, state);
        this->p_04->processTransportEvent(time, state);
    }
    
    void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
        this->updateTime(time);
        this->p_01->processBeatTimeEvent(time, beattime);
        this->p_02->processBeatTimeEvent(time, beattime);
        this->p_03->processBeatTimeEvent(time, beattime);
        this->p_04->processBeatTimeEvent(time, beattime);
    }
    
    void onSampleRateChanged(double ) {}
    
    void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
        this->updateTime(time);
        this->p_01->processTimeSignatureEvent(time, numerator, denominator);
        this->p_02->processTimeSignatureEvent(time, numerator, denominator);
        this->p_03->processTimeSignatureEvent(time, numerator, denominator);
        this->p_04->processTimeSignatureEvent(time, numerator, denominator);
    }
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        this->updateTime(time);
    
        switch (index) {
        case 0:
            {
            this->param_08_value_set(v);
            break;
            }
        case 1:
            {
            this->param_09_value_set(v);
            break;
            }
        case 2:
            {
            this->param_10_value_set(v);
            break;
            }
        default:
            {
            index -= 3;
    
            if (index < this->p_01->getNumParameters())
                this->p_01->setParameterValue(index, v, time);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                this->p_02->setParameterValue(index, v, time);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                this->p_03->setParameterValue(index, v, time);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                this->p_04->setParameterValue(index, v, time);
    
            break;
            }
        }
    }
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        case 0:
            {
            return this->param_08_value;
            }
        case 1:
            {
            return this->param_09_value;
            }
        case 2:
            {
            return this->param_10_value;
            }
        default:
            {
            index -= 3;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterValue(index);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterValue(index);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterValue(index);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->getParameterValue(index);
    
            return 0;
            }
        }
    }
    
    ParameterValue getPolyParameterValue(PatcherInterface** voices, ParameterIndex index)  {
        switch (index) {
        default:
            {
            return voices[0]->getParameterValue(index);
            }
        }
    }
    
    void setPolyParameterValue(
        PatcherInterface** voices,
        ParameterIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        switch (index) {
        default:
            {
            for (Index i = 0; i < 10; i++)
                voices[i]->setParameterValue(index, value, time);
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 3 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters();
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "harmonicity";
            }
        case 1:
            {
            return "filter";
            }
        case 2:
            {
            return "mod_index";
            }
        default:
            {
            index -= 3;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterName(index);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterName(index);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterName(index);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->getParameterName(index);
    
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "poly/harmonicity";
            }
        case 1:
            {
            return "poly/filter";
            }
        case 2:
            {
            return "poly/mod_index";
            }
        default:
            {
            index -= 3;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterId(index);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterId(index);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterId(index);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->getParameterId(index);
    
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
        {
            switch (index) {
            case 0:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0.1;
                info->min = 1;
                info->max = 10;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 1:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 12000;
                info->min = 20;
                info->max = 20000;
                info->exponent = 3;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 2:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 1;
                info->min = 0.1;
                info->max = 10;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            default:
                {
                index -= 3;
    
                if (index < this->p_01->getNumParameters())
                    this->p_01->getParameterInfo(index, info);
    
                index -= this->p_01->getNumParameters();
    
                if (index < this->p_02->getNumParameters())
                    this->p_02->getParameterInfo(index, info);
    
                index -= this->p_02->getNumParameters();
    
                if (index < this->p_03->getNumParameters())
                    this->p_03->getParameterInfo(index, info);
    
                index -= this->p_03->getNumParameters();
    
                if (index < this->p_04->getNumParameters())
                    this->p_04->getParameterInfo(index, info);
    
                break;
                }
            }
        }
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        if (this->_voiceIndex == 1)
            this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void sendPolyParameter(ParameterIndex index, Index voiceIndex, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset + voiceIndex - 1, ignoreValue);
    }
    
    ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
        if (subpatcher == this->p_01)
            return 3;
    
        if (subpatcher == this->p_02)
            return 3 + this->p_01->getNumParameters();
    
        if (subpatcher == this->p_03)
            return 3 + this->p_01->getNumParameters() + this->p_02->getNumParameters();
    
        if (subpatcher == this->p_04)
            return 3 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters();
    
        return 0;
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
            {
            {
                value = (value < 1 ? 1 : (value > 10 ? 10 : value));
                ParameterValue normalizedValue = (value - 1) / (10 - 1);
                return normalizedValue;
            }
            }
        case 1:
            {
            {
                value = (value < 20 ? 20 : (value > 20000 ? 20000 : value));
                ParameterValue normalizedValue = (value - 20) / (20000 - 20);
    
                {
                    if (normalizedValue != 0.0) {
                        normalizedValue = rnbo_exp(((normalizedValue <= 0 ? 0 : rnbo_log(normalizedValue))) * 1. / (number)3);
                    }
                }
    
                return normalizedValue;
            }
            }
        case 2:
            {
            {
                value = (value < 0.1 ? 0.1 : (value > 10 ? 10 : value));
                ParameterValue normalizedValue = (value - 0.1) / (10 - 0.1);
                return normalizedValue;
            }
            }
        default:
            {
            index -= 3;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->convertToNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        case 0:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
                {
                    return 1 + value * (10 - 1);
                }
            }
            }
        case 1:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
                {
                    if (value == 0.0) {
                        return 20;
                    } else {
                        return 20 + rnbo_exp(((value <= 0 ? 0 : rnbo_log(value))) * 3) * (20000 - 20);
                    }
                }
            }
            }
        case 2:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
                {
                    return 0.1 + value * (10 - 0.1);
                }
            }
            }
        default:
            {
            index -= 3;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->convertFromNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
            {
            return this->param_08_value_constrain(value);
            }
        case 1:
            {
            return this->param_09_value_constrain(value);
            }
        case 2:
            {
            return this->param_10_value_constrain(value);
            }
        default:
            {
            index -= 3;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->constrainParameterValue(index, value);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->constrainParameterValue(index, value);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->constrainParameterValue(index, value);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->constrainParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_01->processNumMessage(tag, objectId, time, payload);
        this->p_02->processNumMessage(tag, objectId, time, payload);
        this->p_03->processNumMessage(tag, objectId, time, payload);
        this->p_04->processNumMessage(tag, objectId, time, payload);
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_01->processListMessage(tag, objectId, time, payload);
        this->p_02->processListMessage(tag, objectId, time, payload);
        this->p_03->processListMessage(tag, objectId, time, payload);
        this->p_04->processListMessage(tag, objectId, time, payload);
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_01->processBangMessage(tag, objectId, time);
        this->p_02->processBangMessage(tag, objectId, time);
        this->p_03->processBangMessage(tag, objectId, time);
        this->p_04->processBangMessage(tag, objectId, time);
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
    
        }
    
        auto subpatchResult_0 = this->p_01->resolveTag(tag);
    
        if (subpatchResult_0)
            return subpatchResult_0;
    
        auto subpatchResult_1 = this->p_02->resolveTag(tag);
    
        if (subpatchResult_1)
            return subpatchResult_1;
    
        auto subpatchResult_2 = this->p_03->resolveTag(tag);
    
        if (subpatchResult_2)
            return subpatchResult_2;
    
        auto subpatchResult_3 = this->p_04->resolveTag(tag);
    
        if (subpatchResult_3)
            return subpatchResult_3;
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->updateTime(time);
    
        if (index == 1) {
            this->mtof_tilde_01_innerMtoF_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultMtofLookupTable256);
        }
    
        this->p_01->processDataViewUpdate(index, time);
        this->p_02->processDataViewUpdate(index, time);
        this->p_03->processDataViewUpdate(index, time);
        this->p_04->processDataViewUpdate(index, time);
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
        this->mtof_tilde_01_innerMtoF_buffer = new Float64Buffer(this->getPatcher()->RNBODefaultMtofLookupTable256);
    }
    
    protected:
    
    void param_08_value_set(number v) {
        v = this->param_08_value_constrain(v);
        this->param_08_value = v;
        this->sendParameter(0, false);
    
        if (this->param_08_value != this->param_08_lastValue) {
            this->getEngine()->presetTouched();
            this->param_08_lastValue = this->param_08_value;
        }
    
        this->slide_tilde_02_x_set(v);
    }
    
    void param_09_value_set(number v) {
        v = this->param_09_value_constrain(v);
        this->param_09_value = v;
        this->sendParameter(1, false);
    
        if (this->param_09_value != this->param_09_lastValue) {
            this->getEngine()->presetTouched();
            this->param_09_lastValue = this->param_09_value;
        }
    
        this->slide_tilde_03_x_set(v);
    }
    
    void param_10_value_set(number v) {
        v = this->param_10_value_constrain(v);
        this->param_10_value = v;
        this->sendParameter(2, false);
    
        if (this->param_10_value != this->param_10_lastValue) {
            this->getEngine()->presetTouched();
            this->param_10_lastValue = this->param_10_value;
        }
    
        this->slide_tilde_04_x_set(v);
    }
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 0;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {
        this->mtof_tilde_01_innerScala_init();
        this->mtof_tilde_01_init();
        this->ip_01_init();
        this->ip_02_init();
        this->p_01->initializeObjects();
        this->p_02->initializeObjects();
        this->p_03->initializeObjects();
        this->p_04->initializeObjects();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
        this->p_01->startup();
        this->p_02->startup();
        this->p_03->startup();
        this->p_04->startup();
    }
    
    void allocateDataRefs() {
        this->p_01->allocateDataRefs();
        this->p_02->allocateDataRefs();
        this->p_03->allocateDataRefs();
        this->p_04->allocateDataRefs();
        this->mtof_tilde_01_innerMtoF_buffer->requestSize(65536, 1);
        this->mtof_tilde_01_innerMtoF_buffer->setSampleRate(this->sr);
        this->mtof_tilde_01_innerMtoF_buffer = this->mtof_tilde_01_innerMtoF_buffer->allocateIfNeeded();
    }
    
    static number param_08_value_constrain(number v) {
        v = (v > 10 ? 10 : (v < 1 ? 1 : v));
        return v;
    }
    
    void slide_tilde_02_x_set(number v) {
        this->slide_tilde_02_x = v;
    }
    
    static number param_09_value_constrain(number v) {
        v = (v > 20000 ? 20000 : (v < 20 ? 20 : v));
        return v;
    }
    
    void slide_tilde_03_x_set(number v) {
        this->slide_tilde_03_x = v;
    }
    
    static number param_10_value_constrain(number v) {
        v = (v > 10 ? 10 : (v < 0.1 ? 0.1 : v));
        return v;
    }
    
    void slide_tilde_04_x_set(number v) {
        this->slide_tilde_04_x = v;
    }
    
    void notein_01_outchannel_set(number ) {}
    
    void notein_01_releasevelocity_set(number ) {}
    
    void ip_02_value_set(number v) {
        this->ip_02_value = v;
        this->ip_02_fillSigBuf();
        this->ip_02_lastValue = v;
    }
    
    void expr_01_out1_set(number v) {
        this->expr_01_out1 = v;
        this->ip_02_value_set(this->expr_01_out1);
    }
    
    void expr_01_in1_set(number in1) {
        this->expr_01_in1 = in1;
        this->expr_01_out1_set(this->expr_01_in1 > this->expr_01_in2);//#map:>_obj-2:1
    }
    
    void notein_01_velocity_set(number v) {
        this->expr_01_in1_set(v);
    }
    
    void mtof_tilde_01_midivalue_set(number v) {
        this->mtof_tilde_01_midivalue = v;
    }
    
    void notein_01_notenumber_set(number v) {
        this->mtof_tilde_01_midivalue_set(v);
    }
    
    void notein_01_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
        RNBO_UNUSED(length);
        RNBO_UNUSED(port);
    
        if (channel == this->notein_01_channel || this->notein_01_channel == 0) {
            if (status == 144 || status == 128) {
                this->notein_01_outchannel_set(channel);
    
                if (status == 128) {
                    this->notein_01_releasevelocity_set(data[2]);
                    this->notein_01_velocity_set(0);
                } else {
                    this->notein_01_releasevelocity_set(0);
                    this->notein_01_velocity_set(data[2]);
                }
    
                this->notein_01_notenumber_set(data[1]);
            }
        }
    }
    
    void midiouthelper_midiout_set(number ) {}
    
    void mtof_tilde_01_perform(number midivalue, SampleValue * out, Index n) {
        auto __mtof_tilde_01_base = this->mtof_tilde_01_base;
    
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = this->mtof_tilde_01_innerMtoF_next(midivalue, __mtof_tilde_01_base);
        }
    }
    
    void slide_tilde_02_perform(number x, number up, number down, SampleValue * out1, Index n) {
        RNBO_UNUSED(down);
        RNBO_UNUSED(up);
        auto __slide_tilde_02_prev = this->slide_tilde_02_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(40)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(40)));
        Index i;
    
        for (i = 0; i < n; i++) {
            number temp = x - __slide_tilde_02_prev;
            __slide_tilde_02_prev = __slide_tilde_02_prev + ((x > __slide_tilde_02_prev ? iup : idown)) * temp;
            out1[(Index)i] = __slide_tilde_02_prev;
        }
    
        this->slide_tilde_02_prev = __slide_tilde_02_prev;
    }
    
    void slide_tilde_03_perform(number x, number up, number down, SampleValue * out1, Index n) {
        RNBO_UNUSED(down);
        RNBO_UNUSED(up);
        auto __slide_tilde_03_prev = this->slide_tilde_03_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(40)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(40)));
        Index i;
    
        for (i = 0; i < n; i++) {
            number temp = x - __slide_tilde_03_prev;
            __slide_tilde_03_prev = __slide_tilde_03_prev + ((x > __slide_tilde_03_prev ? iup : idown)) * temp;
            out1[(Index)i] = __slide_tilde_03_prev;
        }
    
        this->slide_tilde_03_prev = __slide_tilde_03_prev;
    }
    
    void slide_tilde_04_perform(number x, number up, number down, SampleValue * out1, Index n) {
        RNBO_UNUSED(down);
        RNBO_UNUSED(up);
        auto __slide_tilde_04_prev = this->slide_tilde_04_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(40)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(40)));
        Index i;
    
        for (i = 0; i < n; i++) {
            number temp = x - __slide_tilde_04_prev;
            __slide_tilde_04_prev = __slide_tilde_04_prev + ((x > __slide_tilde_04_prev ? iup : idown)) * temp;
            out1[(Index)i] = __slide_tilde_04_prev;
        }
    
        this->slide_tilde_04_prev = __slide_tilde_04_prev;
    }
    
    void p_03_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        const SampleValue * in3,
        SampleValue * out1,
        SampleValue * out2,
        Index n
    ) {
        ConstSampleArray<3> ins = {in1, in2, in3};
        SampleArray<2> outs = {out1, out2};
        this->p_03->process(ins, 3, outs, 2, n);
    }
    
    void ip_01_perform(SampleValue * out, Index n) {
        auto __ip_01_lastValue = this->ip_01_lastValue;
        auto __ip_01_lastIndex = this->ip_01_lastIndex;
    
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = ((SampleIndex)(i) >= __ip_01_lastIndex ? __ip_01_lastValue : this->ip_01_sigbuf[(Index)i]);
        }
    
        __ip_01_lastIndex = 0;
        this->ip_01_lastIndex = __ip_01_lastIndex;
    }
    
    void ip_02_perform(SampleValue * out, Index n) {
        auto __ip_02_lastValue = this->ip_02_lastValue;
        auto __ip_02_lastIndex = this->ip_02_lastIndex;
    
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = ((SampleIndex)(i) >= __ip_02_lastIndex ? __ip_02_lastValue : this->ip_02_sigbuf[(Index)i]);
        }
    
        __ip_02_lastIndex = 0;
        this->ip_02_lastIndex = __ip_02_lastIndex;
    }
    
    void p_02_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out1,
        SampleValue * out2,
        Index n
    ) {
        ConstSampleArray<2> ins = {in1, in2};
        SampleArray<2> outs = {out1, out2};
        this->p_02->process(ins, 2, outs, 2, n);
    }
    
    void p_04_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        const SampleValue * in3,
        SampleValue * out1,
        Index n
    ) {
        ConstSampleArray<3> ins = {in1, in2, in3};
        SampleArray<1> outs = {out1};
        this->p_04->process(ins, 3, outs, 1, n);
    }
    
    void p_01_perform(const SampleValue * in1, SampleValue * out1, SampleValue * out2, Index n) {
        // subpatcher: stereo_delay
        ConstSampleArray<1> ins = {in1};
    
        SampleArray<2> outs = {out1, out2};
        this->p_01->process(ins, 1, outs, 2, n);
    }
    
    void signaladder_01_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void signaladder_02_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    number mtof_tilde_01_innerMtoF_next(number midivalue, number tuning) {
        if (midivalue == this->mtof_tilde_01_innerMtoF_lastInValue && tuning == this->mtof_tilde_01_innerMtoF_lastTuning)
            return this->mtof_tilde_01_innerMtoF_lastOutValue;
    
        this->mtof_tilde_01_innerMtoF_lastInValue = midivalue;
        this->mtof_tilde_01_innerMtoF_lastTuning = tuning;
        number result = 0;
    
        {
            result = rnbo_exp(.057762265 * (midivalue - 69.0));
        }
    
        this->mtof_tilde_01_innerMtoF_lastOutValue = tuning * result;
        return this->mtof_tilde_01_innerMtoF_lastOutValue;
    }
    
    void mtof_tilde_01_innerMtoF_reset() {
        this->mtof_tilde_01_innerMtoF_lastInValue = 0;
        this->mtof_tilde_01_innerMtoF_lastOutValue = 0;
        this->mtof_tilde_01_innerMtoF_lastTuning = 0;
    }
    
    void mtof_tilde_01_innerScala_mid(int v) {
        this->mtof_tilde_01_innerScala_kbmMid = v;
        this->mtof_tilde_01_innerScala_updateRefFreq();
    }
    
    void mtof_tilde_01_innerScala_ref(int v) {
        this->mtof_tilde_01_innerScala_kbmRefNum = v;
        this->mtof_tilde_01_innerScala_updateRefFreq();
    }
    
    void mtof_tilde_01_innerScala_base(number v) {
        this->mtof_tilde_01_innerScala_kbmRefFreq = v;
        this->mtof_tilde_01_innerScala_updateRefFreq();
    }
    
    void mtof_tilde_01_innerScala_init() {
        list sclValid = {
            12,
            100,
            0,
            200,
            0,
            300,
            0,
            400,
            0,
            500,
            0,
            600,
            0,
            700,
            0,
            800,
            0,
            900,
            0,
            1000,
            0,
            1100,
            0,
            2,
            1
        };
    
        this->mtof_tilde_01_innerScala_updateScale(sclValid);
    }
    
    void mtof_tilde_01_innerScala_update(list scale, list map) {
        if (scale->length > 0) {
            this->mtof_tilde_01_innerScala_updateScale(scale);
        }
    
        if (map->length > 0) {
            this->mtof_tilde_01_innerScala_updateMap(map);
        }
    }
    
    number mtof_tilde_01_innerScala_mtof(number note) {
        if ((bool)(this->mtof_tilde_01_innerScala_lastValid) && this->mtof_tilde_01_innerScala_lastNote == note) {
            return this->mtof_tilde_01_innerScala_lastFreq;
        }
    
        array<int, 2> degoct = this->mtof_tilde_01_innerScala_applyKBM(note);
        number out = 0;
    
        if (degoct[1] > 0) {
            out = this->mtof_tilde_01_innerScala_applySCL(degoct[0], fract(note), this->mtof_tilde_01_innerScala_refFreq);
        }
    
        this->mtof_tilde_01_innerScala_updateLast(note, out);
        return out;
    }
    
    number mtof_tilde_01_innerScala_ftom(number hz) {
        if (hz <= 0.0) {
            return 0.0;
        }
    
        if ((bool)(this->mtof_tilde_01_innerScala_lastValid) && this->mtof_tilde_01_innerScala_lastFreq == hz) {
            return this->mtof_tilde_01_innerScala_lastNote;
        }
    
        array<number, 2> df = this->mtof_tilde_01_innerScala_hztodeg(hz);
        int degree = (int)(df[0]);
        number frac = df[1];
        number out = 0;
    
        if (this->mtof_tilde_01_innerScala_kbmSize == 0) {
            out = this->mtof_tilde_01_innerScala_kbmMid + degree;
        } else {
            array<int, 2> octdeg = this->mtof_tilde_01_innerScala_octdegree(degree, this->mtof_tilde_01_innerScala_kbmOctaveDegree);
            number oct = (number)(octdeg[0]);
            int index = (int)(octdeg[1]);
            Index entry = 0;
    
            for (Index i = 0; i < this->mtof_tilde_01_innerScala_kbmMapSize; i++) {
                if (index == this->mtof_tilde_01_innerScala_kbmValid[(Index)(i + this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET)]) {
                    entry = i;
                    break;
                }
            }
    
            out = oct * this->mtof_tilde_01_innerScala_kbmSize + entry + this->mtof_tilde_01_innerScala_kbmMid;
        }
    
        out = out + frac;
        this->mtof_tilde_01_innerScala_updateLast(out, hz);
        return this->mtof_tilde_01_innerScala_lastNote;
    }
    
    int mtof_tilde_01_innerScala_updateScale(list scl) {
        if (scl->length < 1) {
            return 0;
        }
    
        number sclDataEntries = scl[0] * 2 + 1;
    
        if (sclDataEntries <= scl->length) {
            this->mtof_tilde_01_innerScala_lastValid = false;
            this->mtof_tilde_01_innerScala_sclExpMul = {};
            number last = 1;
    
            for (Index i = 1; i < sclDataEntries; i += 2) {
                const number c = (const number)(scl[(Index)(i + 0)]);
                const number d = (const number)(scl[(Index)(i + 1)]);
    
                if (d <= 0) {
                    last = c / (number)1200;
                } else {
                    last = rnbo_log2(c / d);
                }
    
                this->mtof_tilde_01_innerScala_sclExpMul->push(last);
            }
    
            this->mtof_tilde_01_innerScala_sclOctaveMul = last;
            this->mtof_tilde_01_innerScala_sclEntryCount = (int)(this->mtof_tilde_01_innerScala_sclExpMul->length);
    
            if (scl->length >= sclDataEntries + 3) {
                this->mtof_tilde_01_innerScala_kbmMid = (int)(scl[(Index)(sclDataEntries + 2)]);
                this->mtof_tilde_01_innerScala_kbmRefNum = (int)(scl[(Index)(sclDataEntries + 1)]);
                this->mtof_tilde_01_innerScala_kbmRefFreq = scl[(Index)(sclDataEntries + 0)];
                this->mtof_tilde_01_innerScala_kbmSize = (int)(0);
            }
    
            this->mtof_tilde_01_innerScala_updateRefFreq();
            return 1;
        }
    
        return 0;
    }
    
    int mtof_tilde_01_innerScala_updateMap(list kbm) {
        if (kbm->length == 1 && kbm[0] == 0.0) {
            kbm = {0.0, 0.0, 0.0, 60.0, 69.0, 440.0};
        }
    
        if (kbm->length >= 6 && kbm[0] >= 0.0) {
            this->mtof_tilde_01_innerScala_lastValid = false;
            Index size = (Index)(kbm[0]);
            int octave = 12;
    
            if (kbm->length > 6) {
                octave = (int)(kbm[6]);
            }
    
            if (size > 0 && kbm->length < this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET) {
                return 0;
            }
    
            this->mtof_tilde_01_innerScala_kbmSize = (int)(size);
            this->mtof_tilde_01_innerScala_kbmMin = (int)(kbm[1]);
            this->mtof_tilde_01_innerScala_kbmMax = (int)(kbm[2]);
            this->mtof_tilde_01_innerScala_kbmMid = (int)(kbm[3]);
            this->mtof_tilde_01_innerScala_kbmRefNum = (int)(kbm[4]);
            this->mtof_tilde_01_innerScala_kbmRefFreq = kbm[5];
            this->mtof_tilde_01_innerScala_kbmOctaveDegree = octave;
            this->mtof_tilde_01_innerScala_kbmValid = kbm;
            this->mtof_tilde_01_innerScala_kbmMapSize = (kbm->length - this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET > kbm->length ? kbm->length : (kbm->length - this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET < 0 ? 0 : kbm->length - this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET));
            this->mtof_tilde_01_innerScala_updateRefFreq();
            return 1;
        }
    
        return 0;
    }
    
    void mtof_tilde_01_innerScala_updateLast(number note, number freq) {
        this->mtof_tilde_01_innerScala_lastValid = true;
        this->mtof_tilde_01_innerScala_lastNote = note;
        this->mtof_tilde_01_innerScala_lastFreq = freq;
    }
    
    array<number, 2> mtof_tilde_01_innerScala_hztodeg(number hz) {
        number hza = rnbo_abs(hz);
    
        number octave = rnbo_floor(
            rnbo_log2(hza / this->mtof_tilde_01_innerScala_refFreq) / this->mtof_tilde_01_innerScala_sclOctaveMul
        );
    
        int i = 0;
        number frac = 0;
        number n = 0;
    
        for (; i < this->mtof_tilde_01_innerScala_sclEntryCount; i++) {
            number c = this->mtof_tilde_01_innerScala_applySCLOctIndex(octave, i + 0, 0.0, this->mtof_tilde_01_innerScala_refFreq);
            n = this->mtof_tilde_01_innerScala_applySCLOctIndex(octave, i + 1, 0.0, this->mtof_tilde_01_innerScala_refFreq);
    
            if (c <= hza && hza < n) {
                if (c != hza) {
                    frac = rnbo_log2(hza / c) / rnbo_log2(n / c);
                }
    
                break;
            }
        }
    
        if (i == this->mtof_tilde_01_innerScala_sclEntryCount && n != hza) {
            number c = n;
            n = this->mtof_tilde_01_innerScala_applySCLOctIndex(octave + 1, 0, 0.0, this->mtof_tilde_01_innerScala_refFreq);
            frac = rnbo_log2(hza / c) / rnbo_log2(n / c);
        }
    
        number deg = i + octave * this->mtof_tilde_01_innerScala_sclEntryCount;
    
        {
            deg = rnbo_fround((deg + frac) * 1 / (number)1) * 1;
            frac = 0.0;
        }
    
        return {deg, frac};
    }
    
    array<int, 2> mtof_tilde_01_innerScala_octdegree(int degree, int count) {
        int octave = 0;
        int index = 0;
    
        if (degree < 0) {
            octave = -(1 + (-1 - degree) / count);
            index = -degree % count;
    
            if (index > 0) {
                index = count - index;
            }
        } else {
            octave = degree / count;
            index = degree % count;
        }
    
        return {octave, index};
    }
    
    array<int, 2> mtof_tilde_01_innerScala_applyKBM(number note) {
        if ((this->mtof_tilde_01_innerScala_kbmMin == this->mtof_tilde_01_innerScala_kbmMax && this->mtof_tilde_01_innerScala_kbmMax == 0) || (note >= this->mtof_tilde_01_innerScala_kbmMin && note <= this->mtof_tilde_01_innerScala_kbmMax)) {
            int degree = (int)(rnbo_floor(note - this->mtof_tilde_01_innerScala_kbmMid));
    
            if (this->mtof_tilde_01_innerScala_kbmSize == 0) {
                return {degree, 1};
            }
    
            array<int, 2> octdeg = this->mtof_tilde_01_innerScala_octdegree(degree, this->mtof_tilde_01_innerScala_kbmSize);
            int octave = (int)(octdeg[0]);
            Index index = (Index)(octdeg[1]);
    
            if (this->mtof_tilde_01_innerScala_kbmMapSize > index) {
                degree = (int)(this->mtof_tilde_01_innerScala_kbmValid[(Index)(this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET + index)]);
    
                if (degree >= 0) {
                    return {degree + octave * this->mtof_tilde_01_innerScala_kbmOctaveDegree, 1};
                }
            }
        }
    
        return {-1, 0};
    }
    
    number mtof_tilde_01_innerScala_applySCL(int degree, number frac, number refFreq) {
        array<int, 2> octdeg = this->mtof_tilde_01_innerScala_octdegree(degree, this->mtof_tilde_01_innerScala_sclEntryCount);
        return this->mtof_tilde_01_innerScala_applySCLOctIndex(octdeg[0], octdeg[1], frac, refFreq);
    }
    
    number mtof_tilde_01_innerScala_applySCLOctIndex(number octave, int index, number frac, number refFreq) {
        number p = 0;
    
        if (index > 0) {
            p = this->mtof_tilde_01_innerScala_sclExpMul[(Index)(index - 1)];
        }
    
        if (frac > 0) {
            p = this->linearinterp(frac, p, this->mtof_tilde_01_innerScala_sclExpMul[(Index)index]);
        } else if (frac < 0) {
            p = this->linearinterp(-frac, this->mtof_tilde_01_innerScala_sclExpMul[(Index)index], p);
        }
    
        return refFreq * rnbo_pow(2, p + octave * this->mtof_tilde_01_innerScala_sclOctaveMul);
    }
    
    void mtof_tilde_01_innerScala_updateRefFreq() {
        this->mtof_tilde_01_innerScala_lastValid = false;
        int refOffset = (int)(this->mtof_tilde_01_innerScala_kbmRefNum - this->mtof_tilde_01_innerScala_kbmMid);
    
        if (refOffset == 0) {
            this->mtof_tilde_01_innerScala_refFreq = this->mtof_tilde_01_innerScala_kbmRefFreq;
        } else {
            int base = (int)(this->mtof_tilde_01_innerScala_kbmSize);
    
            if (base < 1) {
                base = this->mtof_tilde_01_innerScala_sclEntryCount;
            }
    
            array<int, 2> octdeg = this->mtof_tilde_01_innerScala_octdegree(refOffset, base);
            number oct = (number)(octdeg[0]);
            int index = (int)(octdeg[1]);
    
            if (base > 0) {
                oct = oct + rnbo_floor(index / base);
                index = index % base;
            }
    
            if (index >= 0 && index < this->mtof_tilde_01_innerScala_kbmSize) {
                if (index < this->mtof_tilde_01_innerScala_kbmMapSize) {
                    index = (int)(this->mtof_tilde_01_innerScala_kbmValid[(Index)((Index)(index) + this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET)]);
                } else {
                    index = -1;
                }
            }
    
            if (index < 0 || index > this->mtof_tilde_01_innerScala_sclExpMul->length)
                {} else {
                number p = 0;
    
                if (index > 0) {
                    p = this->mtof_tilde_01_innerScala_sclExpMul[(Index)(index - 1)];
                }
    
                this->mtof_tilde_01_innerScala_refFreq = this->mtof_tilde_01_innerScala_kbmRefFreq / rnbo_pow(2, p + oct * this->mtof_tilde_01_innerScala_sclOctaveMul);
            }
        }
    }
    
    void mtof_tilde_01_innerScala_reset() {
        this->mtof_tilde_01_innerScala_internal = true;
        this->mtof_tilde_01_innerScala_lastValid = false;
        this->mtof_tilde_01_innerScala_lastNote = 0;
        this->mtof_tilde_01_innerScala_lastFreq = 0;
        this->mtof_tilde_01_innerScala_sclEntryCount = 0;
        this->mtof_tilde_01_innerScala_sclOctaveMul = 1;
        this->mtof_tilde_01_innerScala_sclExpMul = {};
        this->mtof_tilde_01_innerScala_kbmValid = {0, 0, 0, 60, 69, 440};
        this->mtof_tilde_01_innerScala_kbmMid = 60;
        this->mtof_tilde_01_innerScala_kbmRefNum = 69;
        this->mtof_tilde_01_innerScala_kbmRefFreq = 440;
        this->mtof_tilde_01_innerScala_kbmSize = 0;
        this->mtof_tilde_01_innerScala_kbmMin = 0;
        this->mtof_tilde_01_innerScala_kbmMax = 0;
        this->mtof_tilde_01_innerScala_kbmOctaveDegree = 12;
        this->mtof_tilde_01_innerScala_kbmMapSize = 0;
        this->mtof_tilde_01_innerScala_refFreq = 261.63;
    }
    
    void mtof_tilde_01_init() {
        this->mtof_tilde_01_innerScala_update(this->mtof_tilde_01_scale, this->mtof_tilde_01_map);
    }
    
    void param_08_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_08_value;
    }
    
    void param_08_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_08_value_set(preset["value"]);
    }
    
    void param_09_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_09_value;
    }
    
    void param_09_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_09_value_set(preset["value"]);
    }
    
    void param_10_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_10_value;
    }
    
    void param_10_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_10_value_set(preset["value"]);
    }
    
    void ip_01_init() {
        this->ip_01_lastValue = this->ip_01_value;
    }
    
    void ip_01_dspsetup(bool force) {
        if ((bool)(this->ip_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->ip_01_lastIndex = 0;
        this->ip_01_setupDone = true;
    }
    
    void ip_02_init() {
        this->ip_02_lastValue = this->ip_02_value;
    }
    
    void ip_02_fillSigBuf() {
        if ((bool)(this->ip_02_sigbuf)) {
            SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);
    
            if (k >= (SampleIndex)(this->vs))
                k = (SampleIndex)(this->vs) - 1;
    
            for (SampleIndex i = (SampleIndex)(this->ip_02_lastIndex); i < k; i++) {
                if (this->ip_02_resetCount > 0) {
                    this->ip_02_sigbuf[(Index)i] = 1;
                    this->ip_02_resetCount--;
                } else {
                    this->ip_02_sigbuf[(Index)i] = this->ip_02_lastValue;
                }
            }
    
            this->ip_02_lastIndex = k;
        }
    }
    
    void ip_02_dspsetup(bool force) {
        if ((bool)(this->ip_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->ip_02_lastIndex = 0;
        this->ip_02_setupDone = true;
    }
    
    void midiouthelper_sendMidi(number v) {
        this->midiouthelper_midiout_set(v);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        p_01_target = 0;
        p_02_target = 0;
        p_03_target = 0;
        p_04_target = 0;
        notein_01_channel = 0;
        mtof_tilde_01_midivalue = 0;
        mtof_tilde_01_base = 440;
        slide_tilde_02_x = 0;
        slide_tilde_02_up = 40;
        slide_tilde_02_down = 40;
        param_08_value = 0.1;
        slide_tilde_03_x = 0;
        slide_tilde_03_up = 40;
        slide_tilde_03_down = 40;
        param_09_value = 12000;
        slide_tilde_04_x = 0;
        slide_tilde_04_up = 40;
        slide_tilde_04_down = 40;
        param_10_value = 1;
        ip_01_value = 4;
        ip_01_impulse = 0;
        ip_02_value = 0;
        ip_02_impulse = 0;
        expr_01_in1 = 0;
        expr_01_in2 = 0;
        expr_01_out1 = 0;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        signals[3] = nullptr;
        signals[4] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        notein_01_status = 0;
        notein_01_byte1 = -1;
        notein_01_inchan = 0;
        mtof_tilde_01_innerMtoF_lastInValue = 0;
        mtof_tilde_01_innerMtoF_lastOutValue = 0;
        mtof_tilde_01_innerMtoF_lastTuning = 0;
        mtof_tilde_01_innerScala_internal = true;
        mtof_tilde_01_innerScala_lastValid = false;
        mtof_tilde_01_innerScala_lastNote = 0;
        mtof_tilde_01_innerScala_lastFreq = 0;
        mtof_tilde_01_innerScala_sclEntryCount = 0;
        mtof_tilde_01_innerScala_sclOctaveMul = 1;
        mtof_tilde_01_innerScala_kbmValid = { 0, 0, 0, 60, 69, 440 };
        mtof_tilde_01_innerScala_kbmMid = 60;
        mtof_tilde_01_innerScala_kbmRefNum = 69;
        mtof_tilde_01_innerScala_kbmRefFreq = 440;
        mtof_tilde_01_innerScala_kbmSize = 0;
        mtof_tilde_01_innerScala_kbmMin = 0;
        mtof_tilde_01_innerScala_kbmMax = 0;
        mtof_tilde_01_innerScala_kbmOctaveDegree = 12;
        mtof_tilde_01_innerScala_kbmMapSize = 0;
        mtof_tilde_01_innerScala_refFreq = 261.63;
        slide_tilde_02_prev = 0;
        param_08_lastValue = 0;
        slide_tilde_03_prev = 0;
        param_09_lastValue = 0;
        slide_tilde_04_prev = 0;
        param_10_lastValue = 0;
        ip_01_lastIndex = 0;
        ip_01_lastValue = 0;
        ip_01_resetCount = 0;
        ip_01_sigbuf = nullptr;
        ip_01_setupDone = false;
        ip_02_lastIndex = 0;
        ip_02_lastValue = 0;
        ip_02_resetCount = 0;
        ip_02_sigbuf = nullptr;
        ip_02_setupDone = false;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number p_01_target;
        number p_02_target;
        number p_03_target;
        number p_04_target;
        number notein_01_channel;
        number mtof_tilde_01_midivalue;
        list mtof_tilde_01_scale;
        list mtof_tilde_01_map;
        number mtof_tilde_01_base;
        number slide_tilde_02_x;
        number slide_tilde_02_up;
        number slide_tilde_02_down;
        number param_08_value;
        number slide_tilde_03_x;
        number slide_tilde_03_up;
        number slide_tilde_03_down;
        number param_09_value;
        number slide_tilde_04_x;
        number slide_tilde_04_up;
        number slide_tilde_04_down;
        number param_10_value;
        number ip_01_value;
        number ip_01_impulse;
        number ip_02_value;
        number ip_02_impulse;
        number expr_01_in1;
        number expr_01_in2;
        number expr_01_out1;
        MillisecondTime _currentTime;
        SampleIndex audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[5];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        int notein_01_status;
        int notein_01_byte1;
        int notein_01_inchan;
        number mtof_tilde_01_innerMtoF_lastInValue;
        number mtof_tilde_01_innerMtoF_lastOutValue;
        number mtof_tilde_01_innerMtoF_lastTuning;
        Float64BufferRef mtof_tilde_01_innerMtoF_buffer;
        bool mtof_tilde_01_innerScala_internal;
        const Index mtof_tilde_01_innerScala_KBM_MAP_OFFSET = 7;
        bool mtof_tilde_01_innerScala_lastValid;
        number mtof_tilde_01_innerScala_lastNote;
        number mtof_tilde_01_innerScala_lastFreq;
        int mtof_tilde_01_innerScala_sclEntryCount;
        number mtof_tilde_01_innerScala_sclOctaveMul;
        list mtof_tilde_01_innerScala_sclExpMul;
        list mtof_tilde_01_innerScala_kbmValid;
        int mtof_tilde_01_innerScala_kbmMid;
        int mtof_tilde_01_innerScala_kbmRefNum;
        number mtof_tilde_01_innerScala_kbmRefFreq;
        int mtof_tilde_01_innerScala_kbmSize;
        int mtof_tilde_01_innerScala_kbmMin;
        int mtof_tilde_01_innerScala_kbmMax;
        int mtof_tilde_01_innerScala_kbmOctaveDegree;
        Index mtof_tilde_01_innerScala_kbmMapSize;
        number mtof_tilde_01_innerScala_refFreq;
        number slide_tilde_02_prev;
        number param_08_lastValue;
        number slide_tilde_03_prev;
        number param_09_lastValue;
        number slide_tilde_04_prev;
        number param_10_lastValue;
        SampleIndex ip_01_lastIndex;
        number ip_01_lastValue;
        SampleIndex ip_01_resetCount;
        signal ip_01_sigbuf;
        bool ip_01_setupDone;
        SampleIndex ip_02_lastIndex;
        number ip_02_lastValue;
        SampleIndex ip_02_resetCount;
        signal ip_02_sigbuf;
        bool ip_02_setupDone;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
        RNBOSubpatcher_44* p_01;
        RNBOSubpatcher_45* p_02;
        RNBOSubpatcher_46* p_03;
        RNBOSubpatcher_47* p_04;
    
};

rnbomatic()
{
}

~rnbomatic()
{
    for (int i = 0; i < 10; i++) {
        delete poly[i];
    }
}

rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
}

template <typename T> void listquicksort(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template <typename T> Int listpartition(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    number x = arr[(Index)h];
    Int i = (Int)(l - 1);

    for (Int j = (Int)(l); j <= h - 1; j++) {
        bool asc = (bool)((bool)(ascending) && arr[(Index)j] <= x);
        bool desc = (bool)((bool)(!(bool)(ascending)) && arr[(Index)j] >= x);

        if ((bool)(asc) || (bool)(desc)) {
            i++;
            this->listswapelements(arr, i, j);
            this->listswapelements(sortindices, i, j);
        }
    }

    i++;
    this->listswapelements(arr, i, h);
    this->listswapelements(sortindices, i, h);
    return i;
}

template <typename T> void listswapelements(T& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

MillisecondTime currenttime() {
    return this->_currentTime;
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

number tempo() {
    return this->getTopLevelPatcher()->globaltransport_getTempo(this->currenttime());
}

number mstobeats(number ms) {
    return ms * this->tempo() * 0.008 / (number)480;
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

Index getNumMidiInputPorts() const {
    return 1;
}

void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
    this->updateTime(time);
    this->midiin_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
}

Index getNumMidiOutputPorts() const {
    return 1;
}

void process(
    const SampleValue * const* inputs,
    Index numInputs,
    SampleValue * const* outputs,
    Index numOutputs,
    Index n
) {
    RNBO_UNUSED(numInputs);
    RNBO_UNUSED(inputs);
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime());
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    this->poly_perform(out1, out2, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        this->globaltransport_tempo = resizeSignal(this->globaltransport_tempo, this->maxvs, maxBlockSize);
        this->globaltransport_state = resizeSignal(this->globaltransport_state, this->maxvs, maxBlockSize);
        this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
        this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
        this->didAllocateSignals = true;
    }

    const bool sampleRateChanged = sampleRate != this->sr;
    const bool maxvsChanged = maxBlockSize != this->maxvs;
    const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;

    if (sampleRateChanged || maxvsChanged) {
        this->vs = maxBlockSize;
        this->maxvs = maxBlockSize;
        this->sr = sampleRate;
        this->invsr = 1 / sampleRate;
    }

    this->globaltransport_dspsetup(forceDSPSetup);

    for (Index i = 0; i < 10; i++) {
        this->poly[i]->prepareToProcess(sampleRate, maxBlockSize, force);
    }

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

void setProbingTarget(MessageTag id) {
    switch (id) {
    default:
        {
        this->setProbingIndex(-1);
        break;
        }
    }
}

void setProbingIndex(ProbingIndex ) {}

Index getProbingChannels(MessageTag outletId) const {
    RNBO_UNUSED(outletId);
    return 0;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    case 0:
        {
        return addressOf(this->RNBODefaultSinus);
        break;
        }
    case 1:
        {
        return addressOf(this->RNBODefaultMtofLookupTable256);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 2;
}

void fillRNBODefaultSinus(DataRef& ref) {
    Float64BufferRef buffer;
    buffer = new Float64Buffer(ref);
    number bufsize = buffer->getSize();

    for (Index i = 0; i < bufsize; i++) {
        buffer[i] = rnbo_cos(i * 3.14159265358979323846 * 2. / bufsize);
    }
}

void fillRNBODefaultMtofLookupTable256(DataRef& ref) {
    Float64BufferRef buffer;
    buffer = new Float64Buffer(ref);
    number bufsize = buffer->getSize();

    for (Index i = 0; i < bufsize; i++) {
        number midivalue = -256. + (number)512. / (bufsize - 1) * i;
        buffer[i] = rnbo_exp(.057762265 * (midivalue - 69.0));
    }
}

void fillDataRef(DataRefIndex index, DataRef& ref) {
    switch (index) {
    case 0:
        {
        this->fillRNBODefaultSinus(ref);
        break;
        }
    case 1:
        {
        this->fillRNBODefaultMtofLookupTable256(ref);
        break;
        }
    }
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    for (Index i = 0; i < 10; i++) {
        this->poly[i]->processDataViewUpdate(index, time);
    }
}

void initialize() {
    this->RNBODefaultSinus = initDataRef("RNBODefaultSinus", true, nullptr, "buffer~");
    this->RNBODefaultMtofLookupTable256 = initDataRef("RNBODefaultMtofLookupTable256", true, nullptr, "buffer~");
    this->assign_defaults();
    this->setState();
    this->RNBODefaultSinus->setIndex(0);
    this->RNBODefaultMtofLookupTable256->setIndex(1);
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

Index getPatcherSerial() const {
    return 0;
}

void getState(PatcherStateInterface& ) {}

void setState() {
    for (Index i = 0; i < 10; i++) {
        this->poly[(Index)i] = new RNBOSubpatcher_48();
        this->poly[(Index)i]->setEngineAndPatcher(this->getEngine(), this);
        this->poly[(Index)i]->initialize();
        this->poly[(Index)i]->setParameterOffset(this->getParameterOffset(this->poly[0]));
        this->poly[(Index)i]->setVoiceIndex(i + 1);
    }
}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
    this->param_11_getPresetValue(getSubState(preset, "harmonicity"));
    this->param_12_getPresetValue(getSubState(preset, "filter"));
    this->param_13_getPresetValue(getSubState(preset, "mod_index"));

    for (Index i = 0; i < 10; i++)
        this->poly[i]->getPreset(getSubStateAt(getSubState(preset, "__sps"), "poly", i));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_11_setPresetValue(getSubState(preset, "harmonicity"));
    this->param_12_setPresetValue(getSubState(preset, "filter"));
    this->param_13_setPresetValue(getSubState(preset, "mod_index"));

    for (Index i1 = 0; i1 < 10; i1++) this->poly[i1]->p_01->param_01_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "stereo_delay"), "left_delay")
    );

    for (Index i1 = 0; i1 < 10; i1++) this->poly[i1]->p_01->param_02_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "stereo_delay"), "fb")
    );

    for (Index i1 = 0; i1 < 10; i1++) this->poly[i1]->p_01->param_03_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "stereo_delay"), "right_delay")
    );

    for (Index i1 = 0; i1 < 10; i1++) this->poly[i1]->p_02->param_04_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "p_obj-18"), "attack")
    );

    for (Index i1 = 0; i1 < 10; i1++) this->poly[i1]->p_02->param_05_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "p_obj-18"), "decay")
    );

    for (Index i1 = 0; i1 < 10; i1++) this->poly[i1]->p_02->param_06_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "p_obj-18"), "sustain")
    );

    for (Index i1 = 0; i1 < 10; i1++) this->poly[i1]->p_02->param_07_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "p_obj-18"), "release")
    );
}

void processTempoEvent(MillisecondTime time, Tempo tempo) {
    this->updateTime(time);

    if (this->globaltransport_setTempo(this->_currentTime, tempo, false)) {
        for (Index i = 0; i < 10; i++) {
            this->poly[i]->processTempoEvent(time, tempo);
        }
    }
}

void processTransportEvent(MillisecondTime time, TransportState state) {
    this->updateTime(time);

    if (this->globaltransport_setState(this->_currentTime, state, false)) {
        for (Index i = 0; i < 10; i++) {
            this->poly[i]->processTransportEvent(time, state);
        }
    }
}

void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
    this->updateTime(time);

    if (this->globaltransport_setBeatTime(this->_currentTime, beattime, false)) {
        for (Index i = 0; i < 10; i++) {
            this->poly[i]->processBeatTimeEvent(time, beattime);
        }
    }
}

void onSampleRateChanged(double ) {}

void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
    this->updateTime(time);

    if (this->globaltransport_setTimeSignature(this->_currentTime, numerator, denominator, false)) {
        for (Index i = 0; i < 10; i++) {
            this->poly[i]->processTimeSignatureEvent(time, numerator, denominator);
        }
    }
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time);

    switch (index) {
    case 0:
        {
        this->param_11_value_set(v);
        break;
        }
    case 1:
        {
        this->param_12_value_set(v);
        break;
        }
    case 2:
        {
        this->param_13_value_set(v);
        break;
        }
    default:
        {
        index -= 3;

        if (index < this->poly[0]->getNumParameters())
            this->poly[0]->setPolyParameterValue((PatcherInterface**)this->poly, index, v, time);

        break;
        }
    }
}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
    this->setParameterValue(index, this->getParameterValue(index), time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    case 0:
        {
        return this->param_11_value;
        }
    case 1:
        {
        return this->param_12_value;
        }
    case 2:
        {
        return this->param_13_value;
        }
    default:
        {
        index -= 3;

        if (index < this->poly[0]->getNumParameters())
            return this->poly[0]->getPolyParameterValue((PatcherInterface**)this->poly, index);

        return 0;
        }
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 3 + this->poly[0]->getNumParameters();
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "harmonicity";
        }
    case 1:
        {
        return "filter";
        }
    case 2:
        {
        return "mod_index";
        }
    default:
        {
        index -= 3;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->getParameterName(index);
            }
        }

        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "harmonicity";
        }
    case 1:
        {
        return "filter";
        }
    case 2:
        {
        return "mod_index";
        }
    default:
        {
        index -= 3;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->getParameterId(index);
            }
        }

        return "bogus";
        }
    }
}

void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
    {
        switch (index) {
        case 0:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.1;
            info->min = 1;
            info->max = 10;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 1:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 12000;
            info->min = 20;
            info->max = 20000;
            info->exponent = 3;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 2:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0.1;
            info->max = 10;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        default:
            {
            index -= 3;

            if (index < this->poly[0]->getNumParameters()) {
                for (Index i = 0; i < 10; i++) {
                    this->poly[i]->getParameterInfo(index, info);
                }
            }

            break;
            }
        }
    }
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
    if (subpatcher == this->poly[0])
        return 3;

    return 0;
}

ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
    if (steps == 1) {
        if (normalizedValue > 0) {
            normalizedValue = 1.;
        }
    } else {
        ParameterValue oneStep = (number)1. / (steps - 1);
        ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
        normalizedValue = numberOfSteps * oneStep;
    }

    return normalizedValue;
}

ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        {
            value = (value < 1 ? 1 : (value > 10 ? 10 : value));
            ParameterValue normalizedValue = (value - 1) / (10 - 1);
            return normalizedValue;
        }
        }
    case 1:
        {
        {
            value = (value < 20 ? 20 : (value > 20000 ? 20000 : value));
            ParameterValue normalizedValue = (value - 20) / (20000 - 20);

            {
                if (normalizedValue != 0.0) {
                    normalizedValue = rnbo_exp(((normalizedValue <= 0 ? 0 : rnbo_log(normalizedValue))) * 1. / (number)3);
                }
            }

            return normalizedValue;
        }
        }
    case 2:
        {
        {
            value = (value < 0.1 ? 0.1 : (value > 10 ? 10 : value));
            ParameterValue normalizedValue = (value - 0.1) / (10 - 0.1);
            return normalizedValue;
        }
        }
    default:
        {
        index -= 3;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->convertToNormalizedParameterValue(index, value);
            }
        }

        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 0:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 1 + value * (10 - 1);
            }
        }
        }
    case 1:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                if (value == 0.0) {
                    return 20;
                } else {
                    return 20 + rnbo_exp(((value <= 0 ? 0 : rnbo_log(value))) * 3) * (20000 - 20);
                }
            }
        }
        }
    case 2:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0.1 + value * (10 - 0.1);
            }
        }
        }
    default:
        {
        index -= 3;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->convertFromNormalizedParameterValue(index, value);
            }
        }

        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        return this->param_11_value_constrain(value);
        }
    case 1:
        {
        return this->param_12_value_constrain(value);
        }
    case 2:
        {
        return this->param_13_value_constrain(value);
        }
    default:
        {
        index -= 3;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->constrainParameterValue(index, value);
            }
        }

        return value;
        }
    }
}

void scheduleParamInit(ParameterIndex index, Index order) {
    this->paramInitIndices->push(index);
    this->paramInitOrder->push(order);
}

void processParamInitEvents() {
    this->listquicksort(
        this->paramInitOrder,
        this->paramInitIndices,
        0,
        (int)(this->paramInitOrder->length - 1),
        true
    );

    for (Index i = 0; i < this->paramInitOrder->length; i++) {
        this->getEngine()->scheduleParameterBang(this->paramInitIndices[i], 0);
    }
}

void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}

void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}

void processOutletEvent(
    EngineLink* sender,
    OutletIndex index,
    ParameterValue value,
    MillisecondTime time
) {
    this->updateTime(time);
    this->processOutletAtCurrentTime(sender, index, value);
}

void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);

    for (Index i = 0; i < 10; i++) {
        this->poly[i]->processNumMessage(tag, objectId, time, payload);
    }
}

void processListMessage(
    MessageTag tag,
    MessageTag objectId,
    MillisecondTime time,
    const list& payload
) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);

    for (Index i = 0; i < 10; i++) {
        this->poly[i]->processListMessage(tag, objectId, time, payload);
    }
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);

    for (Index i = 0; i < 10; i++) {
        this->poly[i]->processBangMessage(tag, objectId, time);
    }
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {

    }

    auto subpatchResult_0 = this->poly[0]->resolveTag(tag);

    if (subpatchResult_0)
        return subpatchResult_0;

    return "";
}

MessageIndex getNumMessages() const {
    return 0;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {

    }

    return NullMessageInfo;
}

protected:

void param_11_value_set(number v) {
    v = this->param_11_value_constrain(v);
    this->param_11_value = v;
    this->sendParameter(0, false);

    if (this->param_11_value != this->param_11_lastValue) {
        this->getEngine()->presetTouched();
        this->param_11_lastValue = this->param_11_value;
    }

    this->poly_harmonicity_set(v);
}

void param_12_value_set(number v) {
    v = this->param_12_value_constrain(v);
    this->param_12_value = v;
    this->sendParameter(1, false);

    if (this->param_12_value != this->param_12_lastValue) {
        this->getEngine()->presetTouched();
        this->param_12_lastValue = this->param_12_value;
    }

    this->poly_filter_set(v);
}

void param_13_value_set(number v) {
    v = this->param_13_value_constrain(v);
    this->param_13_value = v;
    this->sendParameter(2, false);

    if (this->param_13_value != this->param_13_lastValue) {
        this->getEngine()->presetTouched();
        this->param_13_lastValue = this->param_13_value;
    }

    this->poly_mod_index_set(v);
}

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

Index getNumInputChannels() const {
    return 0;
}

Index getNumOutputChannels() const {
    return 2;
}

void allocateDataRefs() {
    for (Index i = 0; i < 10; i++) {
        this->poly[i]->allocateDataRefs();
    }

    if (this->RNBODefaultSinus->hasRequestedSize()) {
        if (this->RNBODefaultSinus->wantsFill())
            this->fillRNBODefaultSinus(this->RNBODefaultSinus);

        this->getEngine()->sendDataRefUpdated(0);
    }

    if (this->RNBODefaultMtofLookupTable256->hasRequestedSize()) {
        if (this->RNBODefaultMtofLookupTable256->wantsFill())
            this->fillRNBODefaultMtofLookupTable256(this->RNBODefaultMtofLookupTable256);

        this->getEngine()->sendDataRefUpdated(1);
    }
}

void initializeObjects() {
    this->midinotecontroller_01_init();

    for (Index i = 0; i < 10; i++) {
        this->poly[i]->initializeObjects();
    }
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());

    for (Index i = 0; i < 10; i++) {
        this->poly[i]->startup();
    }

    {
        this->scheduleParamInit(0, 0);
    }

    {
        this->scheduleParamInit(1, 0);
    }

    {
        this->scheduleParamInit(2, 0);
    }

    this->processParamInitEvents();
}

static number param_11_value_constrain(number v) {
    v = (v > 10 ? 10 : (v < 1 ? 1 : v));
    return v;
}

void poly_harmonicity_set(number v) {
    for (number i = 0; i < 10; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(0, v, this->_currentTime);
        }
    }
}

static number param_12_value_constrain(number v) {
    v = (v > 20000 ? 20000 : (v < 20 ? 20 : v));
    return v;
}

void poly_filter_set(number v) {
    for (number i = 0; i < 10; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(1, v, this->_currentTime);
        }
    }
}

static number param_13_value_constrain(number v) {
    v = (v > 10 ? 10 : (v < 0.1 ? 0.1 : v));
    return v;
}

void poly_mod_index_set(number v) {
    for (number i = 0; i < 10; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(2, v, this->_currentTime);
        }
    }
}

void midinotecontroller_01_currenttarget_set(number v) {
    this->midinotecontroller_01_currenttarget = v;
}

void poly_target_set(number v) {
    this->poly_target = v;
    this->midinotecontroller_01_currenttarget_set(v);
}

void midinotecontroller_01_target_set(number v) {
    this->poly_target_set(v);
}

void poly_midiininternal_set(number v) {
    Index sendlen = 0;
    this->poly_currentStatus = parseMidi(this->poly_currentStatus, (int)(v), this->poly_mididata[0]);

    switch ((int)this->poly_currentStatus) {
    case MIDI_StatusByteReceived:
        {
        this->poly_mididata[0] = (uint8_t)(v);
        this->poly_mididata[1] = 0;
        break;
        }
    case MIDI_SecondByteReceived:
    case MIDI_ProgramChange:
    case MIDI_ChannelPressure:
        {
        this->poly_mididata[1] = (uint8_t)(v);

        if (this->poly_currentStatus == MIDI_ProgramChange || this->poly_currentStatus == MIDI_ChannelPressure) {
            sendlen = 2;
        }

        break;
        }
    case MIDI_NoteOff:
    case MIDI_NoteOn:
    case MIDI_Aftertouch:
    case MIDI_CC:
    case MIDI_PitchBend:
    default:
        {
        this->poly_mididata[2] = (uint8_t)(v);
        sendlen = 3;
        break;
        }
    }

    if (sendlen > 0) {
        number i;

        if (this->poly_target > 0 && this->poly_target <= 10) {
            i = this->poly_target - 1;
            this->poly[(Index)i]->processMidiEvent(_currentTime, 0, this->poly_mididata, sendlen);
        } else if (this->poly_target == 0) {
            for (i = 0; i < 10; i++) {
                this->poly[(Index)i]->processMidiEvent(_currentTime, 0, this->poly_mididata, sendlen);
            }
        }
    }
}

void midinotecontroller_01_midiout_set(number v) {
    this->poly_midiininternal_set(v);
}

void poly_noteNumber_set(number v) {
    if (this->poly_target > 0) {
        this->poly[(Index)(this->poly_target - 1)]->setNoteNumber((int)(v));
    }
}

void midinotecontroller_01_noteNumber_set(number v) {
    this->poly_noteNumber_set(v);
}

void midinotecontroller_01_voicestatus_set(const list& v) {
    if (v[1] == 1) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(v[0]);
        this->midinotecontroller_01_noteNumber_set(0);
        this->midinotecontroller_01_target_set(currentTarget);
    }
}

void poly_voicestatus_set(const list& v) {
    this->midinotecontroller_01_voicestatus_set(v);
}

void poly_activevoices_set(number ) {}

void poly_mute_set(const list& v) {
    Index voiceNumber = (Index)(v[0]);
    Index muteState = (Index)(v[1]);

    if (voiceNumber == 0) {
        for (Index i = 0; i < 10; i++) {
            this->poly[(Index)i]->setIsMuted(muteState);
        }
    } else {
        Index subpatcherIndex = voiceNumber - 1;

        if (subpatcherIndex >= 0 && subpatcherIndex < 10) {
            this->poly[(Index)subpatcherIndex]->setIsMuted(muteState);
        }
    }

    list tmp = {v[0], v[1]};
    this->poly_voicestatus_set(tmp);
    this->poly_activevoices_set(this->poly_calcActiveVoices());
}

void midinotecontroller_01_mute_set(const list& v) {
    this->poly_mute_set(v);
}

void midinotecontroller_01_midiin_set(number v) {
    this->midinotecontroller_01_midiin = v;
    int val = (int)(v);

    this->midinotecontroller_01_currentStatus = parseMidi(
        this->midinotecontroller_01_currentStatus,
        (int)(v),
        this->midinotecontroller_01_status
    );

    switch ((int)this->midinotecontroller_01_currentStatus) {
    case MIDI_StatusByteReceived:
        {
        {
            this->midinotecontroller_01_status = val;
            this->midinotecontroller_01_byte1 = -1;
            break;
        }
        }
    case MIDI_SecondByteReceived:
        {
        this->midinotecontroller_01_byte1 = val;
        break;
        }
    case MIDI_NoteOn:
        {
        {
            bool sendnoteoff = true;
            number target = 1;
            number oldest = this->midinotecontroller_01_voice_lastontime[0];
            number target_state = this->midinotecontroller_01_voice_state[0];

            for (Index i = 0; i < 10; i++) {
                number candidate_state = this->midinotecontroller_01_voice_state[(Index)i];

                if (this->midinotecontroller_01_voice_notenumber[(Index)i] == this->midinotecontroller_01_byte1 && candidate_state == MIDI_NoteState_On) {
                    sendnoteoff = false;
                    target = i + 1;
                    break;
                }

                if (i > 0) {
                    if (candidate_state != MIDI_NoteState_On || target_state == MIDI_NoteState_On) {
                        number candidate_ontime = this->midinotecontroller_01_voice_lastontime[(Index)i];

                        if (candidate_ontime < oldest || (target_state == MIDI_NoteState_On && candidate_state != MIDI_NoteState_On)) {
                            target = i + 1;
                            oldest = candidate_ontime;
                            target_state = candidate_state;
                        }
                    }
                }
            }

            if ((bool)(sendnoteoff))
                this->midinotecontroller_01_sendnoteoff((int)(target));

            int i = (int)(target - 1);
            this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_On;
            this->midinotecontroller_01_voice_lastontime[(Index)i] = this->currenttime();
            this->midinotecontroller_01_voice_notenumber[(Index)i] = this->midinotecontroller_01_byte1;
            this->midinotecontroller_01_voice_channel[(Index)i] = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);

            for (Index j = 0; j < 128; j++) {
                if (this->midinotecontroller_01_notesdown[(Index)j] == 0) {
                    this->midinotecontroller_01_notesdown[(Index)j] = this->midinotecontroller_01_voice_notenumber[(Index)i];
                    break;
                }
            }

            this->midinotecontroller_01_note_lastvelocity[(Index)this->midinotecontroller_01_voice_notenumber[(Index)i]] = val;
            this->midinotecontroller_01_sendpitchbend((int)(i));
            this->midinotecontroller_01_sendpressure((int)(i));
            this->midinotecontroller_01_sendtimbre((int)(i));
            this->midinotecontroller_01_muteval[0] = target;
            this->midinotecontroller_01_muteval[1] = 0;
            this->midinotecontroller_01_mute_set(this->midinotecontroller_01_muteval);
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(target);
            this->midinotecontroller_01_noteNumber_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);

            this->midinotecontroller_01_midiout_set(
                (BinOpInt)((BinOpInt)MIDI_NoteOnMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)i])
            );

            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
            this->midinotecontroller_01_midiout_set(val);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
        }
    case MIDI_NoteOff:
        {
        {
            number target = 0;
            number notenumber = this->midinotecontroller_01_byte1;
            number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);

            for (Index i = 0; i < 10; i++) {
                if (this->midinotecontroller_01_voice_notenumber[(Index)i] == notenumber && this->midinotecontroller_01_voice_channel[(Index)i] == channel && this->midinotecontroller_01_voice_state[(Index)i] == MIDI_NoteState_On) {
                    target = i + 1;
                    break;
                }
            }

            if (target > 0) {
                int i = (int)(target - 1);
                Index j = (Index)(channel);
                bool ignoresustainchannel = true;

                if ((bool)(this->midinotecontroller_01_channel_sustain[((bool)(ignoresustainchannel) ? 0 : j)])) {
                    this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Sustained;
                } else {
                    number currentTarget = this->midinotecontroller_01_currenttarget;
                    this->midinotecontroller_01_target_set(target);
                    this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
                    this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
                    this->midinotecontroller_01_midiout_set(v);
                    this->midinotecontroller_01_target_set(currentTarget);

                    if (this->midinotecontroller_01_currentStatus == MIDI_NoteOff) {
                        this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
                    }
                }
            } else
                {}

            bool found = false;

            for (Index i = 0; i < 128; i++) {
                if (this->midinotecontroller_01_notesdown[(Index)i] == 0) {
                    break;
                } else if (this->midinotecontroller_01_notesdown[(Index)i] == notenumber) {
                    found = true;
                }

                if ((bool)(found)) {
                    this->midinotecontroller_01_notesdown[(Index)i] = this->midinotecontroller_01_notesdown[(Index)(i + 1)];
                }
            }

            break;
        }
        }
    case MIDI_Aftertouch:
        {
        {
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(0);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
            this->midinotecontroller_01_midiout_set(v);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
        }
    case MIDI_CC:
        {
        {
            bool sendToAllVoices = true;

            switch ((int)this->midinotecontroller_01_byte1) {
            case MIDI_CC_Sustain:
                {
                {
                    bool pedaldown = (bool)((val >= 64 ? true : false));
                    number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);
                    Index j = (Index)(channel);
                    bool ignoresustainchannel = true;
                    this->midinotecontroller_01_channel_sustain[((bool)(ignoresustainchannel) ? 0 : j)] = pedaldown;

                    if ((bool)(!(bool)(pedaldown))) {
                        for (Index i = 0; i < 10; i++) {
                            if (((bool)(ignoresustainchannel) || this->midinotecontroller_01_voice_channel[(Index)i] == channel) && this->midinotecontroller_01_voice_state[(Index)i] == MIDI_NoteState_Sustained) {
                                number currentTarget = this->midinotecontroller_01_currenttarget;
                                this->midinotecontroller_01_target_set(i + 1);
                                this->midinotecontroller_01_midiout_set((BinOpInt)((BinOpInt)MIDI_NoteOffMask | (BinOpInt)j));
                                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
                                this->midinotecontroller_01_midiout_set(64);
                                this->midinotecontroller_01_target_set(currentTarget);
                                this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
                            }
                        }
                    }

                    break;
                }
                }
            case MIDI_CC_TimbreMSB:
                {
                {
                    number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);
                    int k = (int)(v);
                    number timbre = (BinOpInt)(((BinOpInt)((BinOpInt)k & (BinOpInt)0x7F)) << imod_nocast((UBinOpInt)7, 32));
                    this->midinotecontroller_01_channel_timbre[(Index)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F)] = timbre;

                    for (Index i = 0; i < 10; i++) {
                        if (this->midinotecontroller_01_voice_channel[(Index)i] == channel && this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off) {
                            this->midinotecontroller_01_sendtimbre(i);
                        }
                    }

                    sendToAllVoices = false;
                    break;
                }
                }
            case MIDI_CC_TimbreLSB:
                {
                {
                    break;
                }
                }
            case MIDI_CC_AllNotesOff:
                {
                {
                    this->midinotecontroller_01_sendallnotesoff();
                    break;
                }
                }
            }

            if ((bool)(sendToAllVoices)) {
                number currentTarget = this->midinotecontroller_01_currenttarget;
                this->midinotecontroller_01_target_set(0);
                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
                this->midinotecontroller_01_midiout_set(v);
                this->midinotecontroller_01_target_set(currentTarget);
            }

            break;
        }
        }
    case MIDI_ProgramChange:
        {
        {
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(0);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
        }
    case MIDI_ChannelPressure:
        {
        {
            number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);

            for (number i = 0; i < 10; i++) {
                if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off && this->midinotecontroller_01_voice_channel[(Index)i] == channel) {
                    int k = (int)(channel);
                    this->midinotecontroller_01_channel_pressure[(Index)k] = v;
                    this->midinotecontroller_01_sendpressure(i);
                }
            }

            break;
        }
        }
    case MIDI_PitchBend:
        {
        {
            number bendamount = (BinOpInt)((BinOpInt)this->midinotecontroller_01_byte1 | (BinOpInt)((BinOpInt)val << imod_nocast((UBinOpInt)7, 32)));
            int channel = (int)((BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F));
            this->midinotecontroller_01_channel_pitchbend[(Index)channel] = bendamount;

            for (Index i = 0; i < 10; i++) {
                if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off && this->midinotecontroller_01_voice_channel[(Index)i] == channel) {
                    this->midinotecontroller_01_sendpitchbend(i);
                }
            }

            break;
        }
        }
    }
}

void poly_midiin_set(number v) {
    this->poly_midiin = v;
    this->midinotecontroller_01_midiin_set(v);
}

void midiin_midiout_set(number v) {
    this->poly_midiin_set(v);
}

void midiin_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(port);
    RNBO_UNUSED(channel);
    RNBO_UNUSED(status);
    Index i;

    for (i = 0; i < length; i++) {
        this->midiin_midiout_set(data[i]);
    }
}

void poly_perform(SampleValue * out1, SampleValue * out2, Index n) {
    SampleArray<2> outs = {out1, out2};

    for (number chan = 0; chan < 2; chan++)
        zeroSignal(outs[(Index)chan], n);

    for (Index i = 0; i < 10; i++)
        this->poly[(Index)i]->process(nullptr, 0, outs, 2, n);
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void param_11_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_11_value;
}

void param_11_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_11_value_set(preset["value"]);
}

void param_12_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_12_value;
}

void param_12_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_12_value_set(preset["value"]);
}

void param_13_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_13_value;
}

void param_13_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_13_value_set(preset["value"]);
}

number poly_calcActiveVoices() {
    {
        number activeVoices = 0;

        for (Index i = 0; i < 10; i++) {
            if ((bool)(!(bool)(this->poly[(Index)i]->getIsMuted())))
                activeVoices++;
        }

        return activeVoices;
    }
}

void midinotecontroller_01_init() {
    for (Index i = 0; i < 16; i++) {
        this->midinotecontroller_01_channel_pitchbend[(Index)i] = 0x2000;
    }

    for (Index i = 0; i < 10; i++) {
        this->midinotecontroller_01_voice_lastontime[(Index)i] = -1;
    }
}

void midinotecontroller_01_sendnoteoff(int target) {
    int i = (int)(target - 1);

    if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(target);

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((BinOpInt)MIDI_NoteOffMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)i])
        );

        this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
        this->midinotecontroller_01_midiout_set(64);
        this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
        this->midinotecontroller_01_target_set(currentTarget);
    }
}

void midinotecontroller_01_sendpitchbend(int v) {
    if (v >= 0 && v < 10) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(v + 1);
        int totalbendamount = (int)(this->midinotecontroller_01_channel_pitchbend[(Index)this->midinotecontroller_01_voice_channel[(Index)v]]);

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((BinOpInt)MIDI_PitchBendMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
        );

        this->midinotecontroller_01_midiout_set((BinOpInt)((BinOpInt)totalbendamount & (BinOpInt)0x7F));

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((BinOpInt)((BinOpInt)totalbendamount >> imod_nocast((UBinOpInt)imod_nocast((UBinOpInt)7, 32), 32)) & (BinOpInt)0x7F)
        );

        this->midinotecontroller_01_target_set(currentTarget);
    }
}

void midinotecontroller_01_sendpressure(int v) {
    number currentTarget = this->midinotecontroller_01_currenttarget;
    this->midinotecontroller_01_target_set(v + 1);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)MIDI_ChannelPressureMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(
        this->midinotecontroller_01_channel_pressure[(Index)this->midinotecontroller_01_voice_channel[(Index)v]]
    );

    this->midinotecontroller_01_target_set(currentTarget);
}

void midinotecontroller_01_sendtimbre(int v) {
    number currentTarget = this->midinotecontroller_01_currenttarget;
    this->midinotecontroller_01_target_set(v + 1);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)MIDI_CCMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(MIDI_CC_TimbreLSB);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)this->midinotecontroller_01_channel_timbre[(Index)this->midinotecontroller_01_voice_channel[(Index)v]] & (BinOpInt)0x7F)
    );

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)MIDI_CCMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(MIDI_CC_TimbreMSB);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)((BinOpInt)this->midinotecontroller_01_channel_timbre[(Index)this->midinotecontroller_01_voice_channel[(Index)v]] >> imod_nocast((UBinOpInt)7, 32)) & (BinOpInt)0x7F)
    );

    this->midinotecontroller_01_target_set(currentTarget);
}

void midinotecontroller_01_sendallnotesoff() {
    for (Index i = 1; i <= 10; i++) {
        this->midinotecontroller_01_sendnoteoff(i);
    }
}

Index globaltransport_getSampleOffset(MillisecondTime time) {
    return this->mstosamps(this->maximum(0, time - this->getEngine()->getCurrentTime()));
}

number globaltransport_getTempoAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < this->vs ? this->globaltransport_tempo[(Index)sampleOffset] : this->globaltransport_lastTempo);
}

number globaltransport_getStateAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < this->vs ? this->globaltransport_state[(Index)sampleOffset] : this->globaltransport_lastState);
}

number globaltransport_getState(MillisecondTime time) {
    return this->globaltransport_getStateAtSample(this->globaltransport_getSampleOffset(time));
}

number globaltransport_getBeatTime(MillisecondTime time) {
    number i = 2;

    while (i < this->globaltransport_beatTimeChanges->length && this->globaltransport_beatTimeChanges[(Index)(i + 1)] <= time) {
        i += 2;
    }

    i -= 2;
    number beatTimeBase = this->globaltransport_beatTimeChanges[(Index)i];

    if (this->globaltransport_getState(time) == 0)
        return beatTimeBase;

    number beatTimeBaseMsTime = this->globaltransport_beatTimeChanges[(Index)(i + 1)];
    number diff = time - beatTimeBaseMsTime;
    return beatTimeBase + this->mstobeats(diff);
}

bool globaltransport_setTempo(MillisecondTime time, number tempo, bool notify) {
    if ((bool)(notify)) {
        this->processTempoEvent(time, tempo);
        this->globaltransport_notify = true;
    } else {
        Index offset = (Index)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getTempoAtSample(offset) != tempo) {
            this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
            this->globaltransport_beatTimeChanges->push(time);
            fillSignal(this->globaltransport_tempo, this->vs, tempo, offset);
            this->globaltransport_lastTempo = tempo;
            this->globaltransport_tempoNeedsReset = true;
            return true;
        }
    }

    return false;
}

number globaltransport_getTempo(MillisecondTime time) {
    return this->globaltransport_getTempoAtSample(this->globaltransport_getSampleOffset(time));
}

bool globaltransport_setState(MillisecondTime time, number state, bool notify) {
    if ((bool)(notify)) {
        this->processTransportEvent(time, TransportState(state));
        this->globaltransport_notify = true;
    } else {
        Index offset = (Index)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getStateAtSample(offset) != state) {
            fillSignal(this->globaltransport_state, this->vs, state, offset);
            this->globaltransport_lastState = TransportState(state);
            this->globaltransport_stateNeedsReset = true;

            if (state == 0) {
                this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
                this->globaltransport_beatTimeChanges->push(time);
            }

            return true;
        }
    }

    return false;
}

bool globaltransport_setBeatTime(MillisecondTime time, number beattime, bool notify) {
    if ((bool)(notify)) {
        this->processBeatTimeEvent(time, beattime);
        this->globaltransport_notify = true;
        return false;
    } else {
        bool beatTimeHasChanged = false;
        float oldBeatTime = (float)(this->globaltransport_getBeatTime(time));
        float newBeatTime = (float)(beattime);

        if (oldBeatTime != newBeatTime) {
            beatTimeHasChanged = true;
        }

        this->globaltransport_beatTimeChanges->push(beattime);
        this->globaltransport_beatTimeChanges->push(time);
        return beatTimeHasChanged;
    }
}

number globaltransport_getBeatTimeAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getBeatTime(this->getEngine()->getCurrentTime() + msOffset);
}

array<number, 2> globaltransport_getTimeSignature(MillisecondTime time) {
    number i = 3;

    while (i < this->globaltransport_timeSignatureChanges->length && this->globaltransport_timeSignatureChanges[(Index)(i + 2)] <= time) {
        i += 3;
    }

    i -= 3;

    return {
        this->globaltransport_timeSignatureChanges[(Index)i],
        this->globaltransport_timeSignatureChanges[(Index)(i + 1)]
    };
}

array<number, 2> globaltransport_getTimeSignatureAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getTimeSignature(this->getEngine()->getCurrentTime() + msOffset);
}

bool globaltransport_setTimeSignature(MillisecondTime time, number numerator, number denominator, bool notify) {
    if ((bool)(notify)) {
        this->processTimeSignatureEvent(time, (int)(numerator), (int)(denominator));
        this->globaltransport_notify = true;
    } else {
        array<number, 2> currentSig = this->globaltransport_getTimeSignature(time);

        if (currentSig[0] != numerator || currentSig[1] != denominator) {
            this->globaltransport_timeSignatureChanges->push(numerator);
            this->globaltransport_timeSignatureChanges->push(denominator);
            this->globaltransport_timeSignatureChanges->push(time);
            return true;
        }
    }

    return false;
}

void globaltransport_advance() {
    if ((bool)(this->globaltransport_tempoNeedsReset)) {
        fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
        this->globaltransport_tempoNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTempoEvent(this->globaltransport_lastTempo);
        }
    }

    if ((bool)(this->globaltransport_stateNeedsReset)) {
        fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
        this->globaltransport_stateNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTransportEvent(TransportState(this->globaltransport_lastState));
        }
    }

    if (this->globaltransport_beatTimeChanges->length > 2) {
        this->globaltransport_beatTimeChanges[0] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 2)];
        this->globaltransport_beatTimeChanges[1] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 1)];
        this->globaltransport_beatTimeChanges->length = 2;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendBeatTimeEvent(this->globaltransport_beatTimeChanges[0]);
        }
    }

    if (this->globaltransport_timeSignatureChanges->length > 3) {
        this->globaltransport_timeSignatureChanges[0] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 3)];
        this->globaltransport_timeSignatureChanges[1] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 2)];
        this->globaltransport_timeSignatureChanges[2] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 1)];
        this->globaltransport_timeSignatureChanges->length = 3;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTimeSignatureEvent(
                (int)(this->globaltransport_timeSignatureChanges[0]),
                (int)(this->globaltransport_timeSignatureChanges[1])
            );
        }
    }

    this->globaltransport_notify = false;
}

void globaltransport_dspsetup(bool force) {
    if ((bool)(this->globaltransport_setupDone) && (bool)(!(bool)(force)))
        return;

    fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
    this->globaltransport_tempoNeedsReset = false;
    fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
    this->globaltransport_stateNeedsReset = false;
    this->globaltransport_setupDone = true;
}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

void updateTime(MillisecondTime time) {
    this->_currentTime = time;
    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));

    if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;

    if (this->sampleOffsetIntoNextAudioBuffer < 0)
        this->sampleOffsetIntoNextAudioBuffer = 0;
}

void assign_defaults()
{
    midiin_port = 0;
    midiout_port = 0;
    param_11_value = 0.1;
    param_12_value = 12000;
    param_13_value = 1;
    poly_target = 0;
    poly_midiin = 0;
    midinotecontroller_01_currenttarget = 0;
    midinotecontroller_01_midiin = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    midiout_currentStatus = -1;
    midiout_status = -1;
    midiout_byte1 = -1;
    param_11_lastValue = 0;
    param_12_lastValue = 0;
    param_13_lastValue = 0;
    poly_currentStatus = -1;
    poly_mididata[0] = 0;
    poly_mididata[1] = 0;
    poly_mididata[2] = 0;
    midinotecontroller_01_currentStatus = -1;
    midinotecontroller_01_status = -1;
    midinotecontroller_01_byte1 = -1;
    midinotecontroller_01_zone_masterchannel = 1;
    midinotecontroller_01_zone_numnotechannels = 15;
    midinotecontroller_01_zone_masterpitchbendrange = 2;
    midinotecontroller_01_zone_pernotepitchbendrange = 48;
    midinotecontroller_01_muteval = { 0, 0 };
    globaltransport_tempo = nullptr;
    globaltransport_tempoNeedsReset = false;
    globaltransport_lastTempo = 120;
    globaltransport_state = nullptr;
    globaltransport_stateNeedsReset = false;
    globaltransport_lastState = 0;
    globaltransport_beatTimeChanges = { 0, 0 };
    globaltransport_timeSignatureChanges = { 4, 4, 0 };
    globaltransport_notify = false;
    globaltransport_setupDone = false;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

// member variables

    number midiin_port;
    number midiout_port;
    number param_11_value;
    number param_12_value;
    number param_13_value;
    number poly_target;
    number poly_midiin;
    number midinotecontroller_01_currenttarget;
    number midinotecontroller_01_midiin;
    MillisecondTime _currentTime;
    SampleIndex audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    int midiout_currentStatus;
    int midiout_status;
    int midiout_byte1;
    list midiout_sysex;
    number param_11_lastValue;
    number param_12_lastValue;
    number param_13_lastValue;
    int poly_currentStatus;
    uint8_t poly_mididata[3];
    int midinotecontroller_01_currentStatus;
    int midinotecontroller_01_status;
    int midinotecontroller_01_byte1;
    int midinotecontroller_01_zone_masterchannel;
    int midinotecontroller_01_zone_numnotechannels;
    int midinotecontroller_01_zone_masterpitchbendrange;
    int midinotecontroller_01_zone_pernotepitchbendrange;
    number midinotecontroller_01_channel_pitchbend[16] = { };
    number midinotecontroller_01_channel_pressure[16] = { };
    number midinotecontroller_01_channel_timbre[16] = { };
    Int midinotecontroller_01_channel_sustain[16] = { };
    number midinotecontroller_01_voice_lastontime[10] = { };
    number midinotecontroller_01_voice_notenumber[10] = { };
    number midinotecontroller_01_voice_channel[10] = { };
    number midinotecontroller_01_voice_state[10] = { };
    number midinotecontroller_01_notesdown[129] = { };
    number midinotecontroller_01_note_lastvelocity[128] = { };
    list midinotecontroller_01_muteval;
    signal globaltransport_tempo;
    bool globaltransport_tempoNeedsReset;
    number globaltransport_lastTempo;
    signal globaltransport_state;
    bool globaltransport_stateNeedsReset;
    number globaltransport_lastState;
    list globaltransport_beatTimeChanges;
    list globaltransport_timeSignatureChanges;
    bool globaltransport_notify;
    bool globaltransport_setupDone;
    number stackprotect_count;
    DataRef RNBODefaultSinus;
    DataRef RNBODefaultMtofLookupTable256;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    RNBOSubpatcher_48* poly[10];

};

PatcherInterface* creaternbomatic()
{
    return new rnbomatic();
}

#ifndef RNBO_NO_PATCHERFACTORY

extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction(PlatformInterface* platformInterface)
#else

extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction(PlatformInterface* platformInterface)
#endif

{
    Platform::set(platformInterface);
    return creaternbomatic;
}

} // end RNBO namespace

