//
//  AudioEngine.swift
//  RNBO_AVAudioEngine
//
//  Created by Alex Nadzharov on 13.02.2023.
//

import AVFoundation

extension RNBOAudioEngine {
    /// AVAudioUnit-node van de RNBO Audio Unit
    func getAVAudioUnitNode() -> AVAudioUnit? {
        return avAudioUnit
    }
}

class RNBOAudioEngine {
    private let engine = AVAudioEngine()
    private var avAudioUnit: AVAudioUnit?
    private let playerNode = AVAudioPlayerNode()
    private let audioFile: AVAudioFile?
    private let distortionEffect: AVAudioUnitDistortion
    private let inputMixer: AVAudioMixerNode
    private let microphoneVolumeMixer: AVAudioMixerNode

    private func initInput() {
        let input = engine.inputNode
        // let format = input.inputFormat(forBus: 0)
        let format = avAudioUnit!.inputFormat(forBus: 0)

        if format.channelCount > 0 {
            if input.outputFormat(forBus: 0).sampleRate == format.sampleRate {
                engine.connect(input, to: microphoneVolumeMixer, format: format)
                engine.connect(microphoneVolumeMixer, to: inputMixer, format: format)
                engine.connect(inputMixer, to: avAudioUnit!, format: format)
            } else {
                print("Could not connect input node: sample rate mismatch")
            }
        }
    }
    
    func setMicrophoneAmplitude(_ amp: Float) {
        microphoneVolumeMixer.outputVolume = amp
    }

    init() {
        inputMixer = AVAudioMixerNode()
        microphoneVolumeMixer = AVAudioMixerNode()

        #if os(iOS)
            do {
                try AVAudioSession.sharedInstance().setCategory(.playAndRecord, options: [.defaultToSpeaker, .allowBluetoothA2DP, .mixWithOthers, .allowAirPlay])
                try AVAudioSession.sharedInstance().setActive(true)
            } catch {
                print("Audio session error: \(error.localizedDescription)")
            }
        #endif

        distortionEffect = AVAudioUnitDistortion()
        distortionEffect.loadFactoryPreset(.multiEcho1)

        if let audioFileURL = Bundle.main.url(forResource: "Synth", withExtension: "aif") {
            do {
                audioFile = try AVAudioFile(forReading: audioFileURL)
            } catch {
                print("Error initializing audio file: \(error)")
                audioFile = nil
            }
        } else {
            print("Audio file not found")
            audioFile = nil
        }

        let type = kAudioUnitType_Effect
        let subType: OSType = 0x71717171
        let manufacturer: OSType = 0x70707070

        let description = AudioComponentDescription(
            componentType: type,
            componentSubType: subType,
            componentManufacturer: manufacturer,
            componentFlags: 0,
            componentFlagsMask: 0
        )

        AUAudioUnit.registerSubclass(RNBOAudioUnit.self, as: description, name: "RNBOAudioUnit", version: 1)

        AVAudioUnit.instantiate(with: description, options: .loadOutOfProcess) { avAudioUnit, error in
            guard let avAudioUnit = avAudioUnit, error == nil else {
                print("Error instantiating AVAudioUnit: \(error!.localizedDescription)")
                return
            }

            self.avAudioUnit = avAudioUnit

            DispatchQueue.main.async {
                self.setupAudioChain()
            }
        }
    }

    private func setupAudioChain() {
        guard let avAudioUnit = avAudioUnit else {
            print("avAudioUnit not ready!")
            return
        }
//        engine.attach(distortionEffect)
        engine.attach(inputMixer)
        engine.attach(microphoneVolumeMixer)
        engine.attach(playerNode)
        engine.attach(avAudioUnit)

        microphoneVolumeMixer.outputVolume = 0.0

        let input = engine.inputNode
        let inputFormat = input.outputFormat(forBus: 0)
        let audioUnitInputFormat = avAudioUnit.inputFormat(forBus: 0)

        // Match input node sample rate to audio unit's input sample rate
        if inputFormat.sampleRate != audioUnitInputFormat.sampleRate {
            print("Input node sample rate: \(inputFormat.sampleRate)")
            print("AudioUnit sample rate: \(audioUnitInputFormat.sampleRate)")

            // Fix mismatch by converting formats via mixers
            engine.connect(input, to: microphoneVolumeMixer, format: inputFormat)
            engine.connect(microphoneVolumeMixer, to: inputMixer, format: inputFormat)

            // Use mixer to match sample rate
            engine.connect(inputMixer, to: avAudioUnit, format: audioUnitInputFormat)
        } else {
            // Direct connection if rates match
            engine.connect(input, to: microphoneVolumeMixer, format: inputFormat)
            engine.connect(microphoneVolumeMixer, to: inputMixer, format: inputFormat)
            engine.connect(inputMixer, to: avAudioUnit, format: inputFormat)
        }

        // Player node chain (optional, for audio file playback)
        if let audioFile = audioFile {
            let playerFormat = audioFile.processingFormat
            engine.connect(playerNode, to: inputMixer, format: playerFormat)
        }

        // Audio Unit to main mixer
        let audioUnitOutputFormat = avAudioUnit.outputFormat(forBus: 0)
        engine.connect(avAudioUnit, to: engine.mainMixerNode, format: audioUnitOutputFormat)

        // Main mixer to output node
        let outputFormat = engine.outputNode.inputFormat(forBus: 0)
        engine.connect(engine.mainMixerNode, to: engine.outputNode, format: outputFormat)

        engine.prepare()

        // must be called only when app is didBecomeActive
        // play()
        do {
            try engine.start()
            print("Audio Engine started successfully.")
        } catch {
            print("Error starting audio engine: \(error.localizedDescription)")
        }
    }


    func getAudioUnit() -> RNBOAudioUnit {
        return avAudioUnit!.auAudioUnit as! RNBOAudioUnit
    }

    func playAudioFile() {
        playerNode.stop()
        guard let audioFile = audioFile else {
            return
        }

        playerNode.rate = 1
        playerNode.scheduleFile(audioFile, at: nil) {
            print("Audio playback finished")
        }

        playerNode.play()
    }

    func pauseAudioFile() {
        playerNode.pause()
    }
}
